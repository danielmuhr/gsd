FROM node:current-alpine
RUN mkdir -p /code/gsd/app
COPY . /code/gsd/app
WORKDIR /code/gsd/app
RUN apk add --no-cache g++ && /usr/bin/g++ main1.cpp -o main1.out
CMD ["./main1.out"]