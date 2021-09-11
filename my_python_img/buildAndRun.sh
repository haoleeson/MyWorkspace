#!/bin/bash

# describe: build a python images, and run a container.
# usage： 
#       1. cd the dir of the Dockerfile.
#       2. sh this script.

# User Config Start
IMAGE_NAME=my-python-img
IMAGE_TAG=latest
CONTAINER_NAME=my-python-container
SHARED_DIR=/c/Workspace/MyDockers/commonShareDir
# User Config End

# Remove old container and images(if exist)
ret=$(docker ps -a | grep $CONTAINER_NAME)
if [ -n "$ret" ]; then
    docker container stop $CONTAINER_NAME
    docker rm -f $CONTAINER_NAME
fi

ret=$(docker images | grep $IMAGE_NAME)
if [ -n "$ret" ]; then
    docker rmi -f $IMAGE_NAME
fi

# Build Python image
docker build -t $IMAGE_NAME:$IMAGE_TAG .

# Run the image in a container
docker run -dit -p 4000:80 \
        --name $CONTAINER_NAME \
        $IMAGE_NAME:$IMAGE_TAG \
        /bin/sh -c "while true;do echo hello docker;sleep 1;done"
