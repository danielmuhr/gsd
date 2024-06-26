FROM cpp:latest
COPY service_b.cpp /app/
RUN apt-get update && apt-get install -y libcpr-dev
RUN cd /app && c++ -o service_b service_b.cpp -lcpr
CMD ["/app/service_b"]
