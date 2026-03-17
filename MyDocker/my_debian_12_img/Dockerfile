From debian:bookworm

# Set the working directory to /root/
WORKDIR /root/

# Copy files directory to container /app/files
RUN mkdir -p /app/files/
COPY ["./files", "/app/files"]

#更新apt-get源 使用 ustc 的源
RUN echo "deb https://mirrors.ustc.edu.cn/debian/ bookworm main contrib non-free non-free-firmware" > /etc/apt/sources.list \
    && echo "# deb-src https://mirrors.ustc.edu.cn/debian/ bookworm main contrib non-free non-free-firmware" >> /etc/apt/sources.list \
    && echo "deb https://mirrors.ustc.edu.cn/debian/ bookworm-updates main contrib non-free non-free-firmware" >> /etc/apt/sources.list \
    && echo "# deb-src https://mirrors.ustc.edu.cn/debian/ bookworm-updates main contrib non-free non-free-firmware" >> /etc/apt/sources.list \
    && echo "deb https://mirrors.ustc.edu.cn/debian/ bookworm-backports main contrib non-free non-free-firmware" >> /etc/apt/sources.list \
    && echo "# deb-src https://mirrors.ustc.edu.cn/debian/ bookworm-backports main contrib non-free non-free-firmware" >> /etc/apt/sources.list \
    && echo "deb https://mirrors.ustc.edu.cn/debian-security bookworm-security main contrib non-free non-free-firmware" >> /etc/apt/sources.list \
    && echo "# deb-src https://mirrors.ustc.edu.cn/debian-security bookworm-security main contrib non-free non-free-firmware" >> /etc/apt/sources.list \

    # && cp /etc/apt/sources.list.d/raspi.list /etc/apt/sources.list.d/raspi.list.bak \
    # && echo "deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ bookworm main" > /etc/apt/sources.list.d/raspi.list \

# Update sorce list
    && apt-get update \
    && cp /app/files/pip.conf /etc/pip.conf \

# Solve Linux 8 hours earlier than host
    && ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime \

# Install usefull applications
    && apt-get install -y --force-yes \
    sudo vim git systemd openssh-server supervisor rsyslog \
    # C
    gcc g++ cpp \
    # tool
    tar zip unzip expect tmux zsh \
    # python
    python3 python3-pip \
    # net
    curl wget net-tools ethtool iptables iproute2 tcpdump \

# Initialization SSH
    && mv /etc/ssh/sshd_config /etc/ssh/sshd_config_bak \
    && cp /app/files/sshd_config /etc/ssh/sshd_config \
    && mkdir -p /var/run/sshd \
    # && ssh-keygen -y -t rsa -f /etc/ssh/ssh_host_rsa_key -N '' \

# Supervisord
    && cp /app/files/start.sh /root/start.sh \
    && cp /app/files/supervisord.conf /etc/supervisor/conf.d/supervisord.conf \
    && mkdir -p /var/log/supervisor \


# Clean up apt
# Remove /var/lib/apt/lists/*, could be obsoleted for derived images
# RUN apt-get clean -y; apt-get autoclean -y; apt-get autoremove -y
# RUN rm -rf /var/lib/apt/lists/*
    && apt-get autoremove -y \
    && apt-get clean

# set root passwd
    # echo "root:e" | chpasswd

# Make port 22 80 available to the world outside this container
EXPOSE 22
EXPOSE 80

# Run a program that never exits
ENTRYPOINT ["/usr/bin/supervisord"]
