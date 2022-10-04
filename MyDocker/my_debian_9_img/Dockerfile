From debian:stretch

#更新apt-get源 使用 阿里云 的源
RUN mv /etc/apt/sources.list /etc/apt/sources.list.bak && \
    echo "deb https://mirrors.aliyun.com/debian/ stretch main non-free contrib" > /etc/apt/sources.list && \
    echo "deb-src https://mirrors.aliyun.com/debian/ stretch main non-free contrib" >> /etc/apt/sources.list && \
    echo "deb https://mirrors.aliyun.com/debian-security stretch/updates main" >> /etc/apt/sources.list && \
    echo "deb-src https://mirrors.aliyun.com/debian-security stretch/updates main" >> /etc/apt/sources.list && \
    echo "deb https://mirrors.aliyun.com/debian/ stretch-updates main non-free contrib" >> /etc/apt/sources.list && \
    echo "deb-src https://mirrors.aliyun.com/debian/ stretch-updates main non-free contrib" >> /etc/apt/sources.list && \
    echo "#deb https://mirrors.aliyun.com/debian/ stretch-backports main non-free contrib" >> /etc/apt/sources.list && \
    echo "#deb-src https://mirrors.aliyun.com/debian/ stretch-backports main non-free contrib" >> /etc/apt/sources.list

# RUN cp /etc/apt/sources.list.d/raspi.list /etc/apt/sources.list.d/raspi.list.bak && \
#     echo "deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ stretch main" > /etc/apt/sources.list.d/raspi.list

# Set the working directory to /app
WORKDIR /app

RUN mkdir -p /app/files

# Copy the current directory contents into the container at /app
COPY ["./files", "/app/files"]

# Solve Linux 8 hours earlier than host
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

# Update sorce list
RUN apt update
# RUN apt upgrade

# Install usefull applications
RUN apt-get install -y \
        vim \
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

RUN apt autoremove

# RUN /etc/init.d/ssh start

# Initialization SSH
# RUN ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N ''
# RUN service sshd start
# RUN chkconfig sshd on
# RUN mkdir -p /var/run/sshd

# Make port 22 available to the world outside this container
# EXPOSE 22

# Clean up apt
# Remove /var/lib/apt/lists/*, could be obsoleted for derived images
# RUN apt-get clean -y; apt-get autoclean -y; apt-get autoremove -y
# RUN rm -rf /var/lib/apt/lists/*

# Change hostname
ENV IMAGE_NAME="myDebian9"
RUN /bin/echo "$IMAGE_NAME" > /etc/hostname

CMD ["/bin/echo", "hello Docker $IMAGE_NAME"]

CMD ["/bin/ls", "-l", "/app/files"]

CMD ["/bin/bash", "/app/files/sayHello.sh", "5"]

# Run a program that never exits
CMD ["/bin/bash", "/app/files/nevers_stop.sh"]
