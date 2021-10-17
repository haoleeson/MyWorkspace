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

echo "Build centos image"
docker build -t $IMAGE_NAME:$IMAGE_TAG .

echo "Run the image in a container"
docker run -dit -p 2222:22 \
        --name $CONTAINER_NAME \
        $IMAGE_NAME:$IMAGE_TAG

echo "done."