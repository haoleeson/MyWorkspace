From debian:buster

# #更新apt-get源 使用 阿里云 的源
# RUN mv /etc/apt/sources.list /etc/apt/sources.list.bak && \
#     echo "deb https://mirrors.aliyun.com/debian/ buster main non-free contrib" > /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ buster main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian-security buster/updates main" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian-security buster/updates main" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian/ buster-updates main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ buster-updates main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian/ buster-backports main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ buster-backports main non-free contrib" >> /etc/apt/sources.list

# RUN cp /etc/apt/sources.list.d/raspi.list /etc/apt/sources.list.d/raspi.list.bak && \
#     echo "deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ buster main" > /etc/apt/sources.list.d/raspi.list

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
        gcc \
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


# Install shell_integration
    curl -sL https://iterm2.com/shell_integration/install_shell_integration.sh -o /root/install_shell_integration.sh && \
    bash /root/install_shell_integration.sh 2&>1 && \
    if [ -f /root/.iterm2_shell_integration.bash ]; then \
        rm -rf /root/install_shell_integration.sh; \
        echo "# iterm2 config" >> /root/.bashrc; \
        echo "ITERM_ENABLE_SHELL_INTEGRATION_WITH_TMUX=yes" >> /root/.bashrc; \
        echo "source /root/.iterm2_shell_integration.bash" >> /root/.bashrc; \
    fi; \

# alias
    echo "# alias" >> /root/.bashrc; \
    echo "alias ll=\"ls -l --color=auto \"" >> /root/.bashrc; \
    echo "alias myspeak='f(){ echo befor \"\$@\" after;  unset -f f; }; f'" >> /root/.bashrc; \

# modify vimrc
    cp /etc/vim/vimrc /root/.vimrc && \
    echo "set termencoding=utf-8" >> /root/.vimrc && \
    echo "set encoding=utf-8" >> /root/.vimrc && \
    echo "set fileencodings=utf-8" >> /root/.vimrc && \
    echo "set clipboard=unnamedplus" >> /root/.vimrc; \

# Clean up apt
    # Remove /var/lib/apt/lists/*, could be obsoleted for derived images
    # apt-get clean -y; apt-get autoclean -y; apt-get autoremove -y; \
    # rm -rf /var/lib/apt/lists/* ; \
    apt-get autoremove -y

# Make port 22 available to the world outside this container
EXPOSE 22

# set root passwd
RUN echo "root:e" | chpasswd

# Run a program that never exits
ENTRYPOINT ["/usr/bin/supervisord"]
