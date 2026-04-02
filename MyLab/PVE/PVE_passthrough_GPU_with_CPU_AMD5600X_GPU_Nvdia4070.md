AMD 5600X 与 RTX 4070 独显在 PVE 中的直通配置

# 1. BIOS 基础设置（必需）
启用虚拟化支持
- 启用 SVM Mode（AMD CPU 虚拟化）和 IOMMU（AMD-Vi）。
- 禁用 CSM：强制使用 UEFI 模式，以避免传统 BIOS 干扰。
- 禁用 Resizable BAR/Smart Access Memory：以避免 NVIDIA 显卡在虚拟机中触发 Code 43 错误。
- 启用 Above 4G Decoding：解决大内存地址访问问题。

# 2. PVE 主机配置
## 2.1. 修改 GRUB 内核参数
编辑 /etc/default/grub，在 GRUB_CMDLINE_LINUX_DEFAULT 行添加：
```bash
vi /etc/default/grub

# 修改 GRUB_CMDLINE_LINUX_DEFAULT 内核参数
GRUB_CMDLINE_LINUX_DEFAULT="quiet amd_iommu=on iommu=pt initcall_blacklist=sysfb_init pcie_acs_override=downstream,multifunction vfio_iommu_type1.allow_unsafe_interrupts=1 kvm.ignore_msrs=1"
# GRUB_CMDLINE_LINUX_DEFAULT="quiet amd_iommu=on iommu=pt initcall_blacklist=sysfb_init pcie_acs_override=downstream,multifunction drm.debug=0 kvm_amd.nested=1 kvm.ignore_msrs=1 kvm.report_ignored_msrs=0 pci=assign-busses  vfio_iommu_type1.allow_unsafe_interrupts=1"

grep GRUB_CMDLINE_LINUX_DEFAULT /etc/default/grub
```
内核参数说明：
- amd_iommu=on：启用 IOMMU。
- iommu=pt：将 IOMMU 设置为直通模式（pass through）。
- 若无核显，则额外添加 initcall_blacklist=sysfb_init，其主要作用是禁止 framebuffer 加载显卡驱动，避免占用显卡导致直通失败。
- pcie_acs_override=downstream,multifunction：强制内核拆分 IOMMU 分组，确保显卡独立分组。

### 2.1.1. 查询独显 PCI ID
```bash
lspci -nn | grep -i "nvidia"
```
回显示例（下方独显 PCI ID 前缀为 08:00）：
08:00.0 VGA compatible controller [0300]: NVIDIA Corporation AD104 [GeForce RTX 4070] [10de:2786] (rev a1)
08:00.1 Audio device [0403]: NVIDIA Corporation AD104 High Definition Audio Controller [10de:22bc] (rev a1)

### 2.1.2. 验证 IOMMU 分组
```bash
dmesg | grep -e AMD-Vi -e IOMMU
```
输出应含 "AMD-Vi: IOMMU enabled"，输出中有 "DMAR: IOMMU enabled" 或者 "AMD-Vi: AMD IOMMUv2 loaded and initialized" 表示开启成功。
回显示例：
root@pve:~# dmesg | grep -e AMD-Vi -e IOMMU
[    0.000000] Warning: PCIe ACS overrides enabled; This may allow non-IOMMU protected peer-to-peer DMA
[    0.032766] AMD-Vi: Unknown option - 'on'
[    0.092149] AMD-Vi: Using global IVHD EFR:0x0, EFR2:0x0
[    0.531895] pci 0000:00:00.2: AMD-Vi: IOMMU performance counters supported
[    0.532970] AMD-Vi: Extended features (0x58f77ef22294a5a, 0x0): PPR NX GT IA PC GA_vAPIC
[    0.532976] AMD-Vi: Interrupt remapping enabled
[    0.534256] perf/amd_iommu: Detected AMD IOMMU #0 (2 banks, 4 counters/bank).
root@pve:~#

### 2.1.3. 验证 IOMMU 独显独立分组
独显 PCI ID 前缀为 08:00。
```bash
find /sys/kernel/iommu_groups -type l | grep "08:00"
```
回显示例：
root@pve:~# find /sys/kernel/iommu_groups -type l | grep "08:00"
/sys/kernel/iommu_groups/25/devices/0000:08:00.0
/sys/kernel/iommu_groups/26/devices/0000:08:00.1
root@pve:~#

## 2.2. 验证 IRQ 冲突问题已解决（IRQ remapping）
需要在 PVE 内核中添加 pcie_acs_override=downstream，或降级至 5.15 内核（6.x 内核与 Win10 LTSC 存在兼容问题）。
```bash
dmesg | grep 'remapping'
```
回显示例：
root@pve:~# dmesg | grep 'remapping'
[    0.258101] x2apic: IRQ remapping doesn't support X2APIC mode
[    0.532976] AMD-Vi: Interrupt remapping enabled
root@pve:~#

修复方法：
```bash
echo "options vfio_iommu_type1 allow_unsafe_interrupts=1" > /etc/modprobe.d/iommu_unsafe_interrupts.conf

cat /etc/modprobe.d/iommu_unsafe_interrupts.conf
```

## 2.3. 屏蔽 PVE 宿主机的 NVIDIA 驱动
```bash
vi /etc/modprobe.d/blacklist.conf
```
添加以下屏蔽驱动指令：
```bash
blacklist snd_hda_intel
blacklist nouveau
blacklist nvidia
blacklist nvidiafb
blacklist nvidia_drm
cat /etc/modprobe.d/blacklist.conf
```

## 2.4. 将显卡绑定到 VFIO 驱动
上文查询得独显 PCI ID 为 08:00.0 和 08:00.1。

### 2.4.1. 配置 VFIO 加载优先级
查看需要直通的设备当前使用的驱动。
检查是否有 'in use' 的驱动，若有，则需要在下方 vfio.conf 中添加如 'softdep snd_hda_intel pre: vfio-pci' 的配置，下方示例中未出现。
如上文 08:00.1 被 snd_hda_intel 使用，则需将 VFIO 驱动置于 snd_hda_intel 之前加载。
```bash
cat << EOF >> /etc/modprobe.d/01-vfio-pci.conf
softdep nouveau pre: vfio-pci
softdep snd_hda_intel pre: vfio-pci
EOF

cat /etc/modprobe.d/01-vfio-pci.conf
```

### 2.4.2. 获取要直通的设备标识（vendor_id:device_id）
```bash
lspci -k | grep -A10 VGA

lspci -n -s "08:00" | awk '{print $3}'

获取到的设备标识为（以逗号分隔）：10de:2786,10de:22bc
```

### 2.4.3. 创建 /etc/modprobe.d/vfio.conf
设备标识为（以逗号分隔）：10de:2786,10de:22bc。
```bash
cat << EOF >> /etc/modprobe.d/vfio.conf 
options vfio-pci ids=10de:2786,10de:22bc disable_vga=1
options vfio-pci disable_idle_d3=1
EOF

# check
cat /etc/modprobe.d/vfio.conf
```

说明：
- vfio-pci ids= 后填入 GPU 和声卡 ID（如 08:00.0,08:00.1）。
- disable_idle_d3=1：防止休眠复位失败。

### 2.4.4. 使系统加载 VFIO 驱动
```bash
cat << EOF >> /etc/modules 
vfio
vfio_iommu_type1
vfio_pci
vfio_virqfd
EOF

grep vfio /etc/modules

update-initramfs -u -k all

reboot
```

# 3. 虚拟机设置
## 3.1. 创建 Windows 10 虚拟机
- **机型**：`q35`（UEFI 兼容性最佳）。
- **BIOS**：`OVMF`（UEFI 固件），需添加 `EFI 磁盘`。
- **CPU 类型**：`host`，勾选 `NUMA` 和 `热插拔`（提高性能）。
- **显示**：初始设置为 `无`（避免冲突）。

选择机型为 q35，BIOS 设置为 OVMF (UEFI)，CPU 类型选择 host。

添加 VirtIO-Win 驱动以优化磁盘和网络性能。

## 3.2. 直通 NVIDIA 4070
1. 添加 PCI 设备：
   - 选择 GPU 设备（如 `0b:00.0`）和声卡（如 `0b:00.1`）。
   - **勾选选项**：
     ✅ `PCI-Express` ✅ `主 GPU` ✅ `ROM-BAR`
2. 解决 Code 43 错误：
创建 `/etc/modprobe.d/kvm.conf`：
```bash
options kvm ignore_msrs=1 report_ignored_msrs=0
```

在虚拟机配置中追加参数（编辑 `/etc/pve/qemu-server/VMID.conf`）：

```bash
vi /etc/pve/qemu-server/102.conf
```

```ini
args: -cpu 'host,+kvm_pv_unhalt,+kvm_pv_eoi,hv_vendor_id=proxmox'
```

## 3.3. USB 控制器直通
请勿直通整个 USB 控制器（存在 Bug 可能导致 Windows 10 虚拟机启动失败），建议在 PVE 网页端硬件设置中直通当前插入的单个 USB 端口。
```bash
lspci | grep USB  # 例：03:00.0 USB controller [0c03]: ASMedia ASM2142
lspci | grep USB
02:00.0 USB controller: Advanced Micro Devices, Inc. [AMD] 500 Series Chipset USB 3.1 XHCI Controller
0a:00.3 USB controller: Advanced Micro Devices, Inc. [AMD] Matisse USB 3.0 Host Controller
```

# 4. 宿主机优化（可选）
启用内存大页：降低地址转换损耗。
```bash
echo 'vm.nr_hugepages=8192' > /etc/sysctl.conf

grep nr_hugepages /etc/sysctl.conf
```

# 5. 关闭虚拟机 BIOS 安全
- 首次启动 Windows 10 虚拟机时，在 PVE 页面点击 '启动' 按钮后，立即按 ESC 键进入虚拟机 BIOS，
- 进入 Boot Manager - Secure Boot Configuration，禁用 Attempt Secure Boot，然后按 F10 保存，并选择 Reset 退出。

# 6. Windows 10 虚拟机优化
## 6.1. 屏蔽 Hyper-V（必需）
在 Windows 中禁用 Hyper-V 相关功能：
```powershell
bcdedit /set hypervisorlaunchtype off
```

## 6.2. 使用 VirtIO 驱动
使用 VirtIO 驱动 ISO 以提供存储和网络驱动。

## 6.3. 安装显卡驱动
下载 [NVIDIA 官方驱动](https://www.nvidia.com/drivers)

## 6.4. 进入 Windows 10 后，禁用 Windows 自动更新：
在设置 - 更新和安全中暂停更新。

启用远程桌面连接，安装网卡驱动等，然后关闭计算机。禁用网卡默认断开选项。

# 7. 其他注意事项
- NVIDIA 驱动限制：需要在虚拟机 XML 中添加 hidden=on 参数以规避 Code 43 错误。
- 不同 IOMMU 组内的设备直通互不影响，可在直通页面选择 all functions，否则切勿选择 all functions，以免相关设备在主机上无法使用。
- PCI 直通页面中 ROM-BAR 选项的作用是将 VBIOS 暴露给虚拟机，相当于手动指定 romfile。对于核显，可能需要从主板 BIOS 文件中提取 VBIOS，并使用 romfile 参数传递。
- 部分 AMD 平台存在 reset bug，需要使用第三方补丁：vendor_reset。
- 部分 AMD 核显也存在 reset bug，上述补丁无效，需采用其他方法，后续说明。
- 内核命令行中的参数，多余项不会影响，只要无错误即可。

> 操作全程参考：[PVE 官方直通文档](https://pve.proxmox.com/wiki/Pci_passthrough)  
> 注意：若遇 AMD 平台 Reset Bug（如黑屏无输出），需安装 `vendor-reset` 内核补丁。

## 7.1. 故障排除表
| 问题现象               | 解决方案                                                                 |
|----------------------------|-----------------------------------------------------------------------------|
| 虚拟机启动黑屏             | 检查是否勾选 `主 GPU`，并将 PVE 控制台显示设置为 `无`。     |
| NVIDIA 驱动报错 Code 43    | 确认已添加 `ignore_msrs=1` 和 `hv_vendor_id` 参数。 |
| USB 设备无法识别           | 直通整个 USB 控制器而非单个设备，避免热插拔失效。   |
| 虚拟机卡在 AER 错误        | 在 GRUB 添加 `pci=noaer` 屏蔽日志。                             |
| 性能低于预期               | 关闭虚拟机 C-states（BIOS 中设置），分配更多 CPU 核心。        |

---

## 7.2. 最终检查清单
1. ✅ BIOS 中启用 `SVM`/`IOMMU`，禁用 `CSM` 和 `Resizable BAR`。
2. ✅ GRUB 参数包含 `amd_iommu=on`、`initcall_blacklist=sysfb_init`。
3. ✅ NVIDIA 驱动已屏蔽，VFIO 已绑定正确的 GPU 和声卡 ID。
4. ✅ 虚拟机使用 `OVMF`，显卡已勾选 `主 GPU` 和 `PCI-Express`。
5. ✅ 已添加 `ignore_msrs=1` 和 `hv_vendor_id` 参数以防 Code 43。  
