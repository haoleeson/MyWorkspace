# Use an official centos runtime as a parent image
FROM hub.c.163.com/netease_comb/centos:7

# Update yum sorce
RUN yum makecache fast && yum -y update glibc 

# Set the working directory to /app
WORKDIR /app

RUN mkdir -p /app/files

# Copy the current directory contents into the container at /app
COPY ["./files", "/app/files"]

# Install usefull applications
RUN yum install -y \
        openssh-server \
        vim \
        tar \
        wget \
        curl \
        rsync \
        bzip2 \
        iptables \
        tcpdump \
        less \
        telnet \
        net-tools \
        lsof

# Initialization SSH
RUN ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N ''
# RUN service sshd start
# RUN chkconfig sshd on
RUN mkdir -p /var/run/sshd

# Clean cache
RUN yum clean all

# Close Firewall
# RUN service iptables stop
# RUN chkconfig iptables off

# Close SElinux
# RUN sed -i ".bak" 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config

# Make port 22 available to the world outside this container
EXPOSE 22

# Define environment variable
ENV NAME=Centos7

# Run ssh
CMD ["/usr/sbin/sshd", "-D"]

# Run a program that never exits
CMD ["/bin/bash", "/app/files/nevers_stop.sh"]
