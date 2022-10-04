#!/bin/bash

# describe: build a debian images, and run a container.
# usage： 
#       1. cd the dir of the Dockerfile.
#       2. sh this script.

# User Config Start
IMAGE_NAME=my-debian-img
IMAGE_TAG=v9
CONTAINER_NAME=my-debian-container-9
SHARED_DIR=/c/Workspace/MyDockers/commonShareDir
Docker_vEthernet_IP=172.24.32.1
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

echo "Build debian image"
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
    # route -p add $MY_NET_PREFIX.0 MASK 255.255.255.0 $Docker_vEthernet_IP
    # remove
    # route delete $MY_NET_PREFIX.0
else
    echo "My own net route to HOST is existed"
fi

echo "Run the image in a container"
docker run -dit -p 62209:22 \
        --name $CONTAINER_NAME \
        --network=mynet --ip=${MY_NET_PREFIX}.9 \
        --privileged=true \
        $IMAGE_NAME:$IMAGE_TAG

echo "done."
