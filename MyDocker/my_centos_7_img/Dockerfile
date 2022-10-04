# Use an official centos runtime as a parent image
FROM centos:7.9.2009

# Update yum sorce
RUN yum makecache fast && yum -y update glibc 

# Set the working directory to /app
WORKDIR /app

RUN mkdir -p /app/files

# Copy the current directory contents into the container at /app
COPY ["./files", "/app/files"]

# Solve Linux 8 hours earlier than host
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

# Change hostname
RUN echo 'myCentOs7' > /etc/hostname

# Install usefull applications
RUN yum install -y \
        initscripts \
        openssh-server \
        vim \
        tar \
        wget \
        net-tools nc telnet \
        curl \
        rsync \
        bzip2 \
        iptables \
        tcpdump \
        tmux \
        less \
        telnet \
        lsof

# Initialization SSH
RUN ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N ''
# RUN service sshd start
# RUN chkconfig sshd on
RUN mkdir -p /var/run/sshd

# Install git
RUN  yum install -y \
         https://repo.ius.io/ius-release-el7.rpm \
         https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm \
         && yum install -y git

# Install C/C++ environment
RUN yum -y install centos-release-scl \
        && yum -y install devtoolset-7-gcc devtoolset-7-gcc-c++ devtoolset-7-binutils \
        && yum -y install devtoolset-7-gdb make \
        && yum -y install libatomic

# Install cmake 
WORKDIR /root
RUN wget https://github.com/Kitware/CMake/releases/download/v3.19.8/cmake-3.19.8-Linux-x86_64.tar.gz
RUN tar -xzvf cmake-3.19.8-Linux-x86_64.tar.gz
RUN rm -rf cmake-3.19.8-Linux-x86_64.tar.gz
RUN ln -s /root/cmake-3.19.8-Linux-x86_64/bin/cmake /usr/bin/cmake \
&& ln -s /root/cmake-3.19.8-Linux-x86_64/bin/ccmake /usr/bin/ccmake \
&& ln -s /root/cmake-3.19.8-Linux-x86_64/bin/cmake-gui /usr/bin/cmake-gui \
&& ln -s /root/cmake-3.19.8-Linux-x86_64/bin/cpack /usr/bin/cpack \
&& ln -s /root/cmake-3.19.8-Linux-x86_64/bin/ctest /usr/bin/ctest

# Close Firewall
# RUN service iptables stop
# RUN chkconfig iptables off

# Close SElinux
# RUN sed -i ".bak" 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config

# Make port 22 available to the world outside this container
EXPOSE 22

# Define environment variable
ENV NAME=Centos7.9

# Run ssh
RUN mv /etc/ssh/sshd_config /etc/ssh/sshd_config_bak
RUN cp /app/files/sshd_config /etc/ssh/sshd_config
CMD ["/usr/sbin/sshd", "-D"]

# Clean cache
RUN yum clean all

# Run a program that never exits
CMD ["/bin/bash", "/app/files/nevers_stop.sh"]
