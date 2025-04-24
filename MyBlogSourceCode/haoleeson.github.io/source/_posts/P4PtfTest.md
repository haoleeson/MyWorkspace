layout: post
title: P4 PTF 测试简介
date: 2024/4/24 00:41:45
updated: 2024/4/24 00:41:45
comments: true
tags:
- SDE
- Network
- Barefoot
- P4
categories:
- 技术

---

P4 PTF 作为 Barefoot P4 开发工具链中的重要一部分，可用于自动化测试基于Barefoot提供标准交换机功能的P4 SDE程序自定义开发后的基础功能，如交换机基础二三层功能测试、及自定义数据面功能，本文记录 P4 PTF 测试的常用测试方法。

<!-- more -->

# 1. 创建模拟器容器
```shell
# build 镜像
docker build -t sde_build_image_simple:v9.3.2 . --no-cache
docker build -t sde_build_image_simple:v9.9.0 . --no-cache

# 创建容器 9.9.0（独立网络）
docker run -dit --name bf_sde_9_9_0_simulation --privileged \
    -v /sys/bus/pci/devices:/sys/bus/pci/devices \
    -v /sys/kernel/mm/hugepages:/sys/kernel/mm/hugepages \
    -v /sys/devices/system/node:/sys/devices/system/node \
    -v /usr/share/zoneinfo:/usr/share/zoneinfo:ro \
    -v /etc/localtime:/etc/localtime:ro \
    -w /sde/ \
    -p 10990:22 -p 3000:3000 sde_build_image_simple:v9.9.0 bash

# 创建容器 9.3.2（独立网络）
docker run -dit --name bf_sde_9_3_2_simulation --privileged \
    -v /sys/bus/pci/devices:/sys/bus/pci/devices \
    -v /sys/kernel/mm/hugepages:/sys/kernel/mm/hugepages \
    -v /sys/devices/system/node:/sys/devices/system/node \
    -v /usr/share/zoneinfo:/usr/share/zoneinfo:ro \
    -v /etc/localtime:/etc/localtime:ro \
    -v /home/lihao.213/code/bf-sde-9.3.2-upgrade-sai:/root/bf-sde-9.3.2-upgrade-sai:rw \
    -w /sde/ \
    -p 10932:22 -p 4000:4000 sde_build_image_simple:v9.3.2 bash

# 创建容器 9.3.2（独立网络）
docker run -dit --name ptf_sde_9_3_2 --privileged \
    -v /sys/bus/pci/devices:/sys/bus/pci/devices \
    -v /sys/kernel/mm/hugepages:/sys/kernel/mm/hugepages \
    -v /sys/devices/system/node:/sys/devices/system/node \
    -v /usr/share/zoneinfo:/usr/share/zoneinfo:ro \
    -v /etc/localtime:/etc/localtime:ro \
    -v /home/lihao.213/code/bf-sde-9.3.2-upgrade-sai-with-ptf-updating:/root/bf-sde-9.3.2-upgrade-sai:rw \
    -v /home/lihao.213/my_scripts:/root/my_scripts:rw \
    -w /root/ \
    -p 11932:22 -p 4100:4100 sde_build_image_simple:v9.3.2 bash

# 进入容器
docker exec -it bf_sde_9_9_0_simulation bash
docker exec -it bf_sde_9_3_2_simulation bash

# 注：运行模拟器前要先将 bf-sde/install/lib 中的 libpltfm_mgr.so 文件删除或重命名
```

# 2. 创建可远程 ssh 登录的容器 9.9.0（独立网络）
```shell
HOST_CODE_DIR='/home/lihao.213/code/bf-sde-9.9.0-igw-xlt' && \
CONTAIN_CODE_DIR='/root/bf-sde-9.9.0-igw-xlt' && \
docker run -dit --name bf_sde_9_9_0_simulation --privileged \
    -v /sys/bus/pci/devices:/sys/bus/pci/devices \
    -v /sys/kernel/mm/hugepages:/sys/kernel/mm/hugepages \
    -v /usr/share/zoneinfo:/usr/share/zoneinfo:ro \
    -v /etc/localtime:/etc/localtime:ro \
    -v ${HOST_CODE_DIR}:${CONTAIN_CODE_DIR}:rw \
    -w /root \
    -p 10990:22 -p 3000:3000 sde_build_image_simple:v9.9.0 bash

docker exec -it bf_sde_9_9_0_simulation bash
# 安装 ssh
apt-get install -y --force-yes ssh
# 配置 /etc/ssh/sshd_config 修改 Port 口，允许
vi /etc/ssh/sshd_config
# 运行 sshd
sudo /etc/init.d/ssh start
# 重启 ssh 服务
service ssh restart
# 删除 root 密码
passwd -d root
# 验证登录
exit
ssh -p 10990 root@localhost
```


# 3. 编译
## 3.1. 环境装备
```shell
# BF_SDE_9_9_0 代码
cd /sde/bf-sde-9.9.0
# BF_SDE_9_3_2 代码
cd /sde/bf-sde-9.3.2

# 配置 BF-SDE 环境变量
cd /sde/bf-sde-9.9.0; source /etc/profile && source $SDE/scripts/set_sde.bash

# 安装依赖 （首次需要，下方「首次编译」也会执行这部分代码 ）
cd $SDE/p4studio
./install-p4studio-dependencies.sh
./p4studio dependencies install
```

## 3.2. 开始编译
```shell
cd $SDE/p4studio
BUILD_PROFILES_FILE="$SDE/p4studio/profiles/switch-p4-16-sai15-xlt.yaml"

# 首次编译全量编译
./p4studio profile apply $BUILD_PROFILES_FILE

# 非首次编译（可跳过依赖安装）
./p4studio profile apply $BUILD_PROFILES_FILE --skip-dependencies --skip-system-check
```

## 3.3. 只编译修改的内容
```shell
cd build
make install x1_tofino
```

# 4. 开始 PTF 测试
## 4.1. 设置环境
```shell
### 9.3.2
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
### 9.9.0
# cd /sde/bf-sde-9.9.0 && source $SDE/scripts/set_sde.bash

### 9.13.0
cd /sde/bf-sde-9.13.0 && source ../set_sde.bash
```
## 4.2. 窗口 1.  启动 Tofino Model
```shell
sudo $SDE_INSTALL/bin/veth_teardown.sh 128
sudo $SDE_INSTALL/bin/veth_setup.sh 128

# origin sde-9.3.2 | sde-9.13 success
./run_tofino_model.sh -p switch -c $SDE_INSTALL/share/p4/targets/tofino/switch-sai-cpu-veth.conf -f pkgsrc/switch-p4-16/ptf/ports.json

# sde-9.3 (sai1.10)
./run_tofino_model_sai110.sh --arch tofino -p switch -c $SDE_INSTALL/share/p4/targets/tofino/switch-sai-cpu-veth.conf -f pkgsrc/switch-p4-16/ptf/ports.json

# for XLT sde-9.9
# ./run_tofino_model.sh -p switch -f pkgsrc/switch-p4-16/ptf/ports_xlt.json
./run_tofino_model.sh -p switch -f pkgsrc/switch-p4-16/ptf/ports_xlt.json -c scripts/switch-sai-xlt.conf --int-port-loop 0x2
```

## 4.3. 窗口 2.  启动 switchd
```shell
# origin sde-9.3.2 | sde-9.13 success
./run_switchd.sh -c $SDE_INSTALL/share/p4/targets/tofino/switch-sai-cpu-veth.conf

# sde-9.3 (sai1.10)
./run_switchd_sai110.sh --arch tofino -p switch -c $SDE_INSTALL/share/p4/targets/tofino/switch-sai-cpu-veth.conf

# for XLT sde-9.9
./run_switchd.sh -p switch -c $SDE/scripts/switch-sai-xlt.conf
```

## 4.4. 窗口 3.  启动 PTF Test

```shell
# origin sde-9.3.2 success
# 测试项  sail2  sail3.L3IPv4EcmpLpmTest  sail3.L3IPv4LpmTest  saivxlan
# SINGLE_TEST='sail2'                 # orig sai 15 all pass
# SINGLE_TEST='sail3'                 # orig sai 15 all pass
# SINGLE_TEST='saimirror'             # orig sai 15 all pass
# SINGLE_TEST='saiqos'                # orig sai 15 all pass
# SINGLE_TEST='saiqueue'              # orig sai 15 all pass
# SINGLE_TEST='soniccopp'             # orig sai 15 all pass
SINGLE_TEST='saihostif.LLDPTest'    # orig sai 15 error
SINGLE_TEST='saihostif.DHCPTest'    # orig sai 15 error
# SINGLE_TEST='saiacl'                # orig sai 15 part pass some error
SINGLE_TEST='saidtel'               # orig sai 15 error
SINGLE_TEST='saitunnel'             # orig sai 15 error

./run_p4_tests.sh -p switch -t pkgsrc/switch-p4-16/ptf/sai15/ -f pkgsrc/switch-p4-16/ptf/ports.json --test-params "port_map_file='pkgsrc/switch-p4-16/ptf/sai15/default_interface_to_front_map.ini'"  -s $SINGLE_TEST

# 测试其他程序
# ./run_p4_tests.sh -p tna_checksum
# ./run_p4_tests.sh -p tna_checksum -s Ipv4TranslateUpdTest


# sde-9.3 (sai1.10)
# pip install termcolor pysubnettree # 安装依赖
SINGLE_TEST='sail2'
SINGLE_TEST='sail3'
./run_p4_tests_sai110.sh --arch tofino -p switch -t pkgsrc/switch-p4-16/ptf/sai/ -f pkgsrc/switch-p4-16/ptf/ports.json --test-params "port_map_file='pkgsrc/switch-p4-16/ptf/sai/default_interface_to_front_map.ini'" --target asic-model -s $SINGLE_TEST


# sde_9_13_0
SINGLE_TEST='sail3.L3IPv4HostTest'
./run_p4_tests.sh -p switch -t pkgsrc/switch-p4-16/ptf/sai/ -f pkgsrc/switch-p4-16/ptf/ports.json --test-params "port_map_file='pkgsrc/switch-p4-16/ptf/sai/default_interface_to_front_map.ini'" -s $SINGLE_TEST


# for xgw
./run_p4_tests.sh -p switch -t pkgsrc/switch-p4-16/ptf/sai15/ -f pkgsrc/switch-p4-16/ptf/ports_multipipe.json --test-params "port_map_file='pkgsrc/switch-p4-16/ptf/sai15/multipipe_interface_to_front_map.ini'" -s xgw_test_all

# for XLT
SINGLE_TEST='sail3.L3IPv6HostTest'
./run_p4_tests.sh -p switch -t pkgsrc/switch-p4-16/ptf/sai15/ -f pkgsrc/switch-p4-16/ptf/ports_xlt.json --test-params "port_map_file='pkgsrc/switch-p4-16/ptf/sai15/xlt_interface_to_front_map_t.ini'"  -s $SINGLE_TEST
```

### 4.4.1. 备注：hostif 测试时需额外启动 ptf_nn
测试 hostif 时，需额外起一个 shell 窗口运行 ptf_nn

#### 4.4.1.1. 安装 nnpy 组件
安装 nnpy 及其依赖组件 nanomsg
```shell
# install nanomsg
cd /usr/local/include
git clone https://github.com/nanomsg/nanomsg.git
cd nanomsg/

mkdir build
cd build
cmake ..
cmake --build .
ctest .
sudo cmake --build . --target install
# (if on Linux)
sudo ldconfig

# install nnpy
sudo pip install --default-timeout=100 nnpy -i https://pypi.tuna.tsinghua.edu.cn/simple
# check nnpy installed success
python pkgsrc/ptf-modules/ptf/ptf_nn/check-nnpy.py
```

#### 4.4.1.2. 测试验证 nnpy
```shell
# Win1: Start the first PTF agent (PTF host)
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
## Create the required 2 veth pairs (veth0-veth1 and veth2-veth3)
bash $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/veth_setup.sh
sudo python $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/ptf_nn_agent.py --device-socket 0@tcp://127.0.0.1:10001 -i 0-1@veth0

# Win2: Start the second PTF agent (remote host)
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
sudo python $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/ptf_nn_agent.py --device-socket 1@tcp://127.0.0.1:10002 -i 1-1@veth3

# Win3: Start the dummy "test switch" (connected to the PTF host through veth0-veth1 and to the remote host through veth2-veth3.)
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
sudo python $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/ptf_nn_test_bridge.py -ifrom veth1 -ito veth2

# Win4: Run the PTF test
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
sudo python2 $SDE/pkgsrc/ptf-modules/ptf/ptf --test-dir $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/ptf_nn_test --device-socket 0-{0-64}@tcp://127.0.0.1:10001 --device-socket 1-{0-64}@tcp://127.0.0.1:10002 --platform nn
```


#### 4.4.1.3. 测试 hostif
```shell
# win1: start Tofino Model
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
sudo $SDE_INSTALL/bin/veth_teardown.sh 128
sudo $SDE_INSTALL/bin/veth_setup.sh 128
./run_tofino_model.sh -p switch -c $SDE_INSTALL/share/p4/targets/tofino/switch-sai-cpu-veth.conf -f pkgsrc/switch-p4-16/ptf/ports.json

# win2: start switchd
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
./run_switchd.sh -c $SDE_INSTALL/share/p4/targets/tofino/switch-sai-cpu-veth.conf


# win3: start the PTF agent 1 (PTF local host)
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
## Create the required 2 veth pairs (veth0-veth1 and veth2-veth3)
bash $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/veth_setup.sh
sudo python $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/ptf_nn_agent.py --device-socket 0@tcp://127.0.0.1:10001 -i 0-1@veth0

# win4: start the PTF agent 2 (PTF remote host)
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
sudo python $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/ptf_nn_agent.py --device-socket 1@tcp://127.0.0.1:10002 -i 1-1@veth3

# win5: Start the dummy "test switch" (connected to the PTF host through veth0-veth1 and to the remote host through veth2-veth3.)
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
sudo python $SDE/pkgsrc/switch-p4-16/submodules/SAI15/test/ptf/ptf_nn/ptf_nn_test_bridge.py -ifrom veth1 -ito veth2

# win6: Run the saihostif PTF test
cd /sde/bf-sde-9.3.2 && source ../set_sde.bash
# add python path
PYTHON_VER=$(python --version 2>&1 | awk {'print $2'} | awk -F"." {'print $1"."$2'})
export PYTHONPATH=$SDE_INSTALL/lib/python$PYTHON_VER/site-packages/p4testutils:$SDE_INSTALL/lib/python$PYTHON_VER/site-packages/tofinopd/:$SDE_INSTALL/lib/python$PYTHON_VER/site-packages/tofino:$SDE_INSTALL/lib/python$PYTHON_VER/site-packages/:$PYTHONPATH

# SINGLE_TEST='saihostif.LLDPTest'
# SINGLE_TEST='saihostif.CoppStatTest'
SINGLE_TEST='saihostif'
sudo env "PATH=$PATH" "PYTHONPATH=$PYTHONPATH" "GEN_XML_OUTPUT=$GEN_XML_OUTPUT" python2 \
    $SDE/pkgsrc/ptf-modules/ptf/ptf \
    --test-dir $SDE/pkgsrc/switch-p4-16/ptf/sai15 $SINGLE_TEST \
    --qlen=10000 --platform nn \
    -t "server='localhost';test_port=1;port_map_file='$SDE/pkgsrc/switch-p4-16/ptf/sai15/default_interface_to_front_map.ini';verbose=True;" \
    --device-socket 0-1@tcp://127.0.0.1:10001 --device-socket 1-1@tcp://127.0.0.1:10002
```



## 4.5. 窗口 4. （仅 XLT 需要）设置回环口
```shell
python3 $SDE/pkgsrc/data-path-test/loopbackport.py
```

## 4.6. 开始 Tna_digest 测试
```shell
# 窗口 1. 启动 Tofino Model
./run_tofino_model.sh -p tna_digest
# 窗口 2. 启动 switchd
./run_switchd.sh -p tna_digest
# 窗口 3. 启动 Tna_digest 测试
# 9.3.2 【 some failed： L3EcmpLagTestMini, L3EcmpLagTest, L3EcmpSeedTest, L3IPv6EcmpLpmTest, L3VlanNeighborMacUpdateTest】
./run_p4_tests.sh -p tna_digest -t pkgsrc/p4-examples/p4_16_programs/tna_digest/ -s test
```


~~~~