#!/bin/bash

# describe: build a ubuntu images, and run a container.
# usage： 
#       1. cd the dir of the Dockerfile.
#       2. sh this script.

# User Config Start
IMAGE_NAME=my-ubuntu-img
IMAGE_TAG=v18.04
CONTAINER_NAME=my-ubuntu-container
SHARED_DIR=/c/Workspace/MyDockers/commonShareDir
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

echo "Build ubuntu image"
docker build -t $IMAGE_NAME:$IMAGE_TAG .

echo "Check or build my own net"
ret=$(docker network ls | grep mynet >> /etc/null)
if [ "$?" == "1" ]; then
    echo "Creating my own net"
    docker network create --driver bridge --subnet 172.16.13.0/24 --gateway 172.16.13.1 mynet
    # remove manually
    # docker network rm mynet
else
    echo "My own net is existed"
fi

echo "Run the image in a container"
docker run -dit -p 3333:22 \
        --name $CONTAINER_NAME \
        --network=mynet --ip=172.16.13.18 \
        $IMAGE_NAME:$IMAGE_TAG

echo "done."
