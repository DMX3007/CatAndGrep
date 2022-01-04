FROM quay.io/school21/alpine:3.13
FROM gcc:4.9

RUN mkdir -p usr/src/myapp/
WORKDIR /usr/src/app/
COPY . /usr/src/app/

RUN gcc grep.c -o grep

CMD ["./grep"]