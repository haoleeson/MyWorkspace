#!/bin/bash

# describe: build a centos images, and run a container.
# usage： 
#       1. cd the dir of the Dockerfile.
#       2. sh this script.

# User Config Start
IMAGE_NAME=my-centos-img
IMAGE_TAG=v7.9
CONTAINER_NAME=my-centos-container
SHARED_DIR=/c/Workspace/MyDockers/commonShareDir
Docker_vEthernet_IP=172.24.32.1
Wsl_IP=172.24.32.181
MY_NET_PREFIX=172.148.0
# User Config End

echo "Remove the old same name container (if exist)"
ret=$(docker ps -a | grep $CONTAINER_NAME)
if [ -n "$ret" ]; then
    docker container stop $CONTAINER_NAME
    docker rm -f $CONTAINER_NAME
fi

echo "Remove the old same name images (if exist)"
ret=$(docker images | grep $IMAGE_NAME)
if [ -n "$ret" ]; then
    docker rmi -f $IMAGE_NAME
fi

# Add wsl config
# New-NetFirewallRule -DisplayName "WSL" -Direction Inbound  -InterfaceAlias "vEthernet (WSL)"  -Action Allow

echo "Build centos image"
docker build -t $IMAGE_NAME:$IMAGE_TAG .

echo "Check or build my own net"
ret=$(docker network ls | grep mynet >> /etc/null)
if [ "$?" == "1" ]; then
    echo "Creating my own net"
    docker network create --driver bridge --subnet ${MY_NET_PREFIX}.0/24 --gateway ${MY_NET_PREFIX}.1 mynet
    # remove manually
    # docker network rm mynet
else
    echo "My own net is existed"
fi

echo "Check or add my own net route to HOST"
ret=$(route print -4 | grep "$MY_NET_PREFIX.0")
if [ "$?" == "1" ]; then
    echo "Adding my own net route to HOST"
    # route -p add 172.148.0.0 MASK 255.255.255.0 172.24.32.1
    # route -p add $MY_NET_PREFIX.0 MASK 255.255.255.0 $Wsl_IP
    # remove
    # route delete 172.148.0.0
    # route delete $MY_NET_PREFIX.0
else
    echo "My own net route to HOST is existed"
fi

echo "Run the image in a container"
docker run -dit -p 62207:22 \
        --name $CONTAINER_NAME \
        --network=mynet --ip=${MY_NET_PREFIX}.7 \
        --privileged=true \
        $IMAGE_NAME:$IMAGE_TAG

echo "done."
