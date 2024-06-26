FROM node:current-alpine

LABEL org.opencontainers.image.title="gsd" \
org.opencontainers.image.description="web server test" \
org.opencontainers.image.authors="@danielmuhr"

RUN mkdir -p /code/gsd/app

COPY  . /code/gsd/app

WORKDIR /code/gsd/app

RUN apk add --no-cache g++ && /usr/bin/g++ server_linux.cpp -o server_linux.out

CMD ["./server_linux.out"]