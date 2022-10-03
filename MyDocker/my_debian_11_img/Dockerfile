From debian:bullseye

#更新apt-get源 使用163的源
RUN mv /etc/apt/sources.list /etc/apt/sources.list.bak && \
    echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye main contrib non-free" >/etc/apt/sources.list && \
    echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-updates main contrib non-free" >>/etc/apt/sources.list && \
    echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bullseye-backports main contrib non-free" >>/etc/apt/sources.list && \
    echo "deb https://mirrors.tuna.tsinghua.edu.cn/debian-security bullseye-security main contrib non-free" >>/etc/apt/sources.list

# Update sorce list
RUN apt-get update

# Set the working directory to /app
WORKDIR /app

RUN mkdir -p /app/files

# Copy the current directory contents into the container at /app
COPY ["./files", "/app/files"]

# Solve Linux 8 hours earlier than host
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

# Change hostname
echo 'myDebian11' > /etc/hostname

# Install usefull applications
RUN apt-get install -y \
        vim \
        gcc \
        net-tools \
        tar \
        wget \
        curl \
        iptables \
        tcpdump \
        tmux \
        openssh-server

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

ENV IMAGE_NAME="my-debian-0"
RUN /bin/echo "$IMAGE_NAME" > /etc/hostname

CMD ["/bin/echo", "hello Docker $IMAGE_NAME"]

CMD ["/bin/ls", "-l", "/app/files"]

CMD ["/bin/bash", "/app/files/sayHello.sh", "5"]

# Run a program that never exits
CMD ["/bin/bash", "/app/files/nevers_stop.sh"]
