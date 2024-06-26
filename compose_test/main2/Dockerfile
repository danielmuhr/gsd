FROM node:current-alpine
RUN mkdir -p /code/gsd/app
COPY . /code/gsd/app
WORKDIR /code/gsd/app
RUN apk add --no-cache g++ && /usr/bin/g++ main2.cpp -o main2.out
CMD ["./main2.out"]