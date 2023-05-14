#!/bin/bash

# describe: build a debian images, and run a container.
# usage： 
#       1. cd the dir of the Dockerfile.
#       2. sh this script.

################# User Config Start #################
IMAGE_NAME=sde_build_image_simple
IMAGE_TAG=v9.3.2
CONTAINER_NAME=bf_sde_9_3_2_simulation
################# User Config End #################

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

echo "Build $IMAGE_NAME:$IMAGE_TAG image"
docker build -t $IMAGE_NAME:$IMAGE_TAG . --no-cache

echo "Run the image in a container"
docker run -dit --name $CONTAINER_NAME --privileged=true \
    -v /sys/bus/pci/devices:/sys/bus/pci/devices \
    -v /sys/kernel/mm/hugepages:/sys/kernel/mm/hugepages \
    -v /sys/devices/system/node:/sys/devices/system/node \
    -v /usr/share/zoneinfo:/usr/share/zoneinfo:ro \
    -v /etc/localtime:/etc/localtime:ro \
    -w /sde/ \
    -p 10990:22 -p 3000:3000 $IMAGE_NAME:$IMAGE_TAG bash

echo "done."
