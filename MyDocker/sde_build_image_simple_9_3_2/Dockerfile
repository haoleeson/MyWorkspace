FROM debian:stretch

WORKDIR /root/

RUN mkdir -p /sde/
COPY files/* /sde/
# COPY .ssh/ /root/.ssh/

# ENV HTTP_PROXY "http://EXAMPLE:PORT"
# ENV HTTPS_PROXY "http://EXAMPLE:PORT"
# ENV NO_PROXY "no.example.proxy.com"

# RUN cp /sde/sources.list /etc/apt/ && \
#     echo "export http_proxy=http://EXAMPLE:PORT" >> /etc/profile && \
#     echo "export https_proxy=http://EXAMPLE:PORT" >> /etc/profile && \
#     echo "export no_proxy=no.example.proxy.com" >> /etc/profile; \

# Change linux-header
RUN mv /bin/uname /bin/uname.old && \
    cp /sde/uname-deb9 /bin/uname && \
    chmod +x /bin/uname && \
    apt-get update && \
    apt install -y --force-yes sudo dh-make && \
    sudo apt-get install -y linux-headers-amd64; \

# Install dependencies
    apt-get install -y --force-yes sudo python python-pip \
    # minimal dependencies
    autoconf bridge-utils cpp doxygen cscope curl ethtool flex git \
    libtool make net-tools python-setuptools unzip wget aspell \
    build-essential g++ libbz2-dev libc6-dev libelf-dev libgmp10 \
    pkg-config python-cffi python-dev systemd \
    # thrift dependencies
    bison libevent-dev libssl-dev \
    # grpc dependencies
    libgoogle-perftools-dev\
    # ptf_modules dependencies
    python-scapy \
    # switch_p4_16 dependencies
    aspell-en libnl-route-3-dev libxml-simple-perl pkg-config \
    # bf_platforms dependencies
    libusb-1.0-0-dev libcur14-gnutls-dev \
    # bf_diags dependencies
    libpcap-dev \
    # pi dependencies
    libjudy-dev \
    # debian 9 dependencies
    libgc-dev libglib2.0-dev python3.5-dev \

    # ubuntu 18.04 minimal dependencies
    libboost-dev libboost-test-dev libboost-thread-dev libboost-system-dev \
    # other dependencies
    zlib1g-dev automake dh-make cmake python-ply libssl1.0.2 \
    python-crcmod python-jsonschema xz-utils \
    ca-certificates ca-certificates-java apt-transport-https \
    default-jdk default-jre default-jre-headless \
    zip vim expect; \

# Install python dependencies
    cp /sde/pip.conf /etc/pip.conf && \
    pip install pyyaml crc16 crcmod doxypy ipaddress jsl jsonschema==2.6.0 \
    packaging ply simplejson Tenjin -i http://mirrors.aliyun.com/pypi/simple/; \

    # # Install sde build dependences
    # git clone --single-branch -b bf-sde-9.3.2 git@your-bf-sde.git /sde/bf-sde-9.3.2 && \
    # cp /sde/set_sde.bash /sde/bf-sde-9.3.2/ && \
    # cd /sde/bf-sde-9.3.2/ && \
    # /bin/bash -c "source /etc/profile; source set_sde.bash; cd p4studio_build; \
    #               ./p4studio_build.py -fa -wk -up switch_p416_profile_sai15 -sp x1_tofino" && \
    # rm -rf /sde/bf-sde-9.3.2/ && \

    apt-get clean
