From debian:bullseye

# #更新apt-get源 使用 tsinghua 的源
# RUN mv /etc/apt/sources.list /etc/apt/sources.list.bak && \
#     echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye main contrib non-free" > /etc/apt/sources.list && \
#     echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-updates main contrib non-free" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-backports main contrib non-free" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian-security bullseye-security main contrib non-free" >> /etc/apt/sources.list

# #更新apt-get源 使用 阿里云 的源
# RUN mv /etc/apt/sources.list /etc/apt/sources.list.bak && \
#     echo "deb https://mirrors.aliyun.com/debian/ bullseye main non-free contrib" > /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ bullseye main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian-security/ bullseye-security main" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian-security/ bullseye-security main" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian/ bullseye-updates main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ bullseye-updates main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian/ bullseye-backports main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ bullseye-backports main non-free contrib" >> /etc/apt/sources.list

# RUN cp /etc/apt/sources.list.d/raspi.list /etc/apt/sources.list.d/raspi.list.bak && \
#     echo "deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ bullseye main" > /etc/apt/sources.list.d/raspi.list

# Update sorce list
RUN apt-get update
# RUN apt-get upgrade
RUN apt-get clean

# Solve Linux 8 hours earlier than host
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

# Set the working directory to /root/
WORKDIR /root/

RUN mkdir -p /app/files

# Copy the current directory contents into the container at /app
COPY ["./files", "/app/files"]
COPY ["./files/pip.conf", "/etc/pip.conf"]

# Install usefull applications
RUN apt-get install -y --force-yes \
    sudo vim git systemd openssh-server supervisor rsyslog \
    # gcc \
    g++ \
    tar
    # git \
    # python3-pip \
    # tmux \
    # wget \
    # curl \
    # net-tools \
    # iptables \
    # tcpdump \
    # openssh-server \
    # openssh-client

# Initialization SSH
RUN mv /etc/ssh/sshd_config /etc/ssh/sshd_config_bak
COPY ["./files/sshd_config", "/etc/ssh/sshd_config"]
RUN mkdir -p /var/run/sshd
# RUN ssh-keygen -y -t rsa -f /etc/ssh/ssh_host_rsa_key -N ''

# Supervisord
COPY ["./files/start.sh", "/root/"]
COPY ["./files/supervisord.conf", "/etc/supervisor/conf.d/supervisord.conf"]
RUN mkdir -p /var/log/supervisor

# Make port 22 available to the world outside this container
# EXPOSE 22

# Clean up apt
# Remove /var/lib/apt/lists/*, could be obsoleted for derived images
# RUN apt-get clean -y; apt-get autoclean -y; apt-get autoremove -y
# RUN rm -rf /var/lib/apt/lists/*
RUN apt-get autoremove -y

# Make port 22 80 available to the world outside this container
EXPOSE 22 

# set root passwd
RUN echo "root:e" | chpasswd

# Run a program that never exits
ENTRYPOINT ["/usr/bin/supervisord"]
