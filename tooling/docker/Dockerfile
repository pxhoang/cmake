FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        bash \
        ca-certificates \
        build-essential \
        cmake \
        ninja-build \
        git \
        grep \
        coreutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
