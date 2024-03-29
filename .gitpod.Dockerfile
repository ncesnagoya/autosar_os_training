# ビルド環境を構築してビルド
#FROM debian:buster-slim as build-env
#FROM ubuntu:18.04
FROM gitpod/workspace-full

ENV ATHRILL_HOME=/usr/local/athrill-target-rh850f1x
ENV ATHRILL_GCC=/usr/local/athrill-gcc

USER root

RUN apt-get update \
    && apt-get -y install git wget make ruby gem \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp

# athrill-gcc
RUN wget https://github.com/toppers/athrill-gcc-v850e2m/releases/download/v1.1/athrill-gcc-package.tar.gz && \
    tar xzf athrill-gcc-package.tar.gz && \
	tar xzf athrill-gcc-package/athrill-gcc.tar.gz && \
    mv usr/local/athrill-gcc /usr/local/

# athrill(rh850f1x)
RUN wget https://github.com/toppers/athrill-target-rh850f1x/releases/download/v0.A.2/athrill-target-rh850f1x-x86_64-linux-20220813.tar.gz && \
    tar xzf athrill-target-rh850f1x-x86_64-linux-20220813.tar.gz && \
    cp athrill-target-rh850f1x/build_linux/athrill2 athrill-target-rh850f1x/athrill/bin/linux/ && \
    mv athrill-target-rh850f1x /usr/local/

USER gitpod
WORKDIR /home/gitpod
# cfg
RUN wget https://github.com/mitsut/cfg/releases/download/1.9.7/cfg-1.9.7-x86_64-unknown-linux-gnu.tar.gz && \
	wget https://www.autosar.org/fileadmin/user_upload/standards/classic/4-0/AUTOSAR_MMOD_XMLSchema.zip && \
	mkdir schema && \
    tar xzf cfg-1.9.7-x86_64-unknown-linux-gnu.tar.gz && \
    mv cfg schema/ && \
	unzip AUTOSAR_MMOD_XMLSchema.zip -d schema

RUN git clone --depth=1 https://github.com/toppers/atk2-sc1.git && \
    mkdir -p atk2-sc1/cfg/cfg && \
    cp /home/gitpod/schema/* atk2-sc1/cfg/cfg/

ENV LD_LIBRARY_PATH="${ATHRILL_GCC}:${ATHRILL_GCC}/lib:${LD_LIBRARY_PATH}"
ENV PATH="${ATHRILL_GCC}/bin:${ATHRILL_HOME}/athrill/bin/linux:$PATH"