# Use an official ubuntu runtime as a parent image
FROM ubuntu:18.04

# Update apt-get sorce
RUN apt-get update && apt-get install sudo

# Set the working directory to /app
WORKDIR /app

RUN mkdir -p /app/files

# Copy the current directory contents into the container at /app
COPY ["./files", "/app/files"]

# Install usefull applications
RUN apt-get install -y \
        net-tools \
        telnet \
        openssh-server \
        vim \
        tar \
        wget \
        curl \
        rsync \
        bzip2 \
        iptables \
        tcpdump \
        tmux \
        less \
        telnet \
        lsof

# Install gcc, g++
RUN apt-get install -y make
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y gcc
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y g++
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y cmake
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y gdb

# Initialization SSH
# RUN ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N ''
# RUN service sshd start
# RUN chkconfig sshd on
# RUN mkdir -p /var/run/sshd

# Clean cache
RUN apt-get clean all

# Solve Linux 8 hours earlier than host
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

# Change hostname
RUN echo 'myUbuntu18' > /etc/hostname

# Close Firewall
# RUN service iptables stop
# RUN chkconfig iptables off

# Close SElinux
# RUN sed -i ".bak" 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config

# Make port 22 available to the world outside this container
EXPOSE 22

# Define environment variable
ENV NAME=ubuntu18.04

# Run ssh
CMD ["/usr/sbin/sshd", "-D"]

# Run a program that never exits
CMD ["/bin/bash", "/app/files/nevers_stop.sh"]
