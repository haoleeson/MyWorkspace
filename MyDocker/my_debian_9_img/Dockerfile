From debian:stretch

#更新apt-get源 使用 阿里云 的源
# RUN mv /etc/apt/sources.list /etc/apt/sources.list.bak && \
#     echo "deb https://mirrors.aliyun.com/debian/ stretch main non-free contrib" > /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ stretch main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian-security stretch/updates main" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian-security stretch/updates main" >> /etc/apt/sources.list && \
#     echo "deb https://mirrors.aliyun.com/debian/ stretch-updates main non-free contrib" >> /etc/apt/sources.list && \
#     echo "deb-src https://mirrors.aliyun.com/debian/ stretch-updates main non-free contrib" >> /etc/apt/sources.list && \
#     echo "#deb https://mirrors.aliyun.com/debian/ stretch-backports main non-free contrib" >> /etc/apt/sources.list && \
#     echo "#deb-src https://mirrors.aliyun.com/debian/ stretch-backports main non-free contrib" >> /etc/apt/sources.list

# RUN cp /etc/apt/sources.list.d/raspi.list /etc/apt/sources.list.d/raspi.list.bak && \
#     echo "deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ stretch main" > /etc/apt/sources.list.d/raspi.list

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
    sudo vim git systemd openssh-server supervisor gcc g++ cpp tar zip unzip expect tmux rsyslog zsh \
    python-pip python3 python3-pip python-setuptools python-dev python-cffi python-scapy python-ply \
    # compare
    autoconf bridge-utils libtool make automake cmake build-essential libbz2-dev libc6-dev libelf-dev libgmp10 \ 
    bison libevent-dev libssl-dev libusb-1.0-0-dev libcurl4-gnutls-dev libnl-route-3-dev libxml-simple-perl libjudy-dev \
    libgc-dev libpcap-dev libglib2.0-dev libgoogle-perftools-dev doxygen cscope flex aspell aspell-en pkg-config \
    # net
    curl wget net-tools ethtool iptables iproute2 iputils-ping tcpdump \
    # SONiC dependenceies
    libpq-dev libxml2-dev libxslt1-dev libldap2-dev libsasl2-dev libffi-dev \
    # others
    zlib1g-dev xz-utils dh-make libssl1.0.2 python-crcmod python-jsonschema \
    libboost-dev libboost-test-dev libboost-thread-dev libboost-system-dev \
    apt-transport-https ca-certificates ca-certificates-java \
    default-jdk default-jre default-jre-headless

# Install python lib
RUN pip install crc16 crcmod doxypy ipaddress jsl jsonschema==2.6.0 packaging ply simplejson

# Install SONiC dependency lib
# RUN pip install -U --default-timeout=100 paramiko>=2.11.0 Jinja2==2.10 j2cli
# RUN pip3 install -U --default-timeout=100 nose setuptools
# RUN python3 -m pip install mockredispy>=2.9.3
# SONiC libsairedis dependenceies
# RUN pip3 install -U redis==2.10.6 natsort pytest-runner pytest==3.0.5 python_arptable>=0.0.1 psutil>=4.0 pyyaml
# RUN pip install -U redis==2.10.6

# Initialization SSH
RUN mv /etc/ssh/sshd_config /etc/ssh/sshd_config_bak
COPY ["./files/sshd_config", "/etc/ssh/sshd_config"]
RUN mkdir -p /var/run/sshd
# RUN ssh-keygen -y -t rsa -f /etc/ssh/ssh_host_rsa_key -N ''

# Setting oh-my-zsh (GnuTLS recv error (-110): The TLS connection was non-properly terminated.)
# RUN /usr/bin/curl -L https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh | sh
## RUN git clone git://github.com/robbyrussell/oh-my-zsh.git /root/.oh-my-zsh
# CMD ["/bin/cp", "/root/.zshrc", "/root/.zshrc_bak"]
# CMD ["/bin/cp", "/root/.oh-my-zsh/templates/zshrc.zsh-template", "/root/.zshrc"]
# RUN /bin/sed -i 's/ZSH_THEME="robbyrussell"/ZSH_THEME="ys"/g' /root/.zshrc
# CMD ["/usr/bin/chsh", "-s", "/bin/zsh"]

# Supervisord
COPY ["./files/start.sh", "/root/"]
COPY ["./files/supervisord.conf", "/etc/supervisor/conf.d/supervisord.conf"]
RUN mkdir -p /var/log/supervisor


# Clean up apt
# Remove /var/lib/apt/lists/*, could be obsoleted for derived images
# RUN apt-get clean -y; apt-get autoclean -y; apt-get autoremove -y
# RUN rm -rf /var/lib/apt/lists/*
RUN apt-get autoremove -y

# Make port 22 80 available to the world outside this container
EXPOSE 22 
EXPOSE 80

# set root passwd
RUN echo "root:e" | chpasswd

# Run a program that never exits
ENTRYPOINT ["/usr/bin/supervisord"]
