FROM node:current-alpine

LABEL org.opencontainers.image.title="gsd" \
org.opencontainers.image.description="web server test" \
org.opencontainers.image.authors="@danielmuhr"

RUN mkdir -p ~/code/gsd/app

COPY  ~/code/simple_webserver ~/code/gsd/app

WORKDIR /code/gsd/app

RUN g++ server_linux.cpp -o server_linux.o

CMD ./server_linux.o