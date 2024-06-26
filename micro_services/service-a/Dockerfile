# FROM node:current-alpine

# LABEL org.opencontainers.image.title="service-a" \
# org.opencontainers.image.description="service-a for microservice test" \
# org.opencontainers.image.authors="@danielmuhr"

# COPY service_a.cpp /app/
# RUN apt-get update && apt-get install -y libcpr-dev
# RUN apk add --no-cache g++ && /usr/bin/g++ service_acpp -o service_a.o
# CMD ["/app/service_a"]

FROM ubuntu:latest



# Add the CPR repository
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    sudo apt-get install libcurl4-openssl-dev && \
    add-apt-repository ppa:romanz/libcpr-dev && \
    apt-get update

# Install C++ compiler and dependencies
RUN apt-get install -y build-essential libcpr-dev

# Copy the source code
COPY service_a.cpp /app/

# Build the application
RUN cd /app && c++ -o service_a service_a.cpp -lcpr

# Run the application
CMD ["/app/service_a"]
