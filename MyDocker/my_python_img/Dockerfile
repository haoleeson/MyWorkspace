# Use an official Python runtime as a parent image
FROM python:2.7-slim

# Set the working directory to /app
WORKDIR /app

RUN mkdir -p /app/files

# Copy the current directory contents into the container at /app
COPY ["./files", "/app/files"]

# Solve Linux 8 hours earlier than host
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

# Install any needed packages specified in requirements.txt
RUN pip install --trusted-host pypi.python.org -r /app/files/requirements.txt

# Make port 80 available to the world outside this container
EXPOSE 80

# Define environment variable
ENV NAME=World

# Run app.py when the container launches
CMD ["python", "/app/files/app.py"]

# Run a program that never exits
CMD ["/bin/bash", "/app/files/nevers_stop.sh"]
