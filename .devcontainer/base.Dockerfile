FROM mcr.microsoft.com/devcontainers/base:2-trixie

USER root
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        git make ruby ruby-rubygems unzip wget \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /home/toppers
RUN wget https://github.com/toppers/athrill-gcc-v850e2m/releases/download/v1.1/athrill-gcc-package.tar.gz && \
    tar xzf athrill-gcc-package.tar.gz && \
    tar xzf athrill-gcc-package/athrill-gcc.tar.gz && \
    mv usr/local/athrill-gcc /usr/local/

RUN wget https://github.com/toppers/athrill-target-rh850f1x/releases/download/v0.A.2/athrill-target-rh850f1x-x86_64-linux-20220813.tar.gz && \
    tar xzf athrill-target-rh850f1x-x86_64-linux-20220813.tar.gz && \
    cp athrill-target-rh850f1x/build_linux/athrill2 athrill-target-rh850f1x/athrill/bin/linux/

RUN wget https://github.com/mitsut/cfg/releases/download/1.9.7/cfg-1.9.7-x86_64-unknown-linux-gnu.tar.gz && \
    wget https://www.autosar.org/fileadmin/standards/R4.0.3/CP/AUTOSAR_MMOD_XMLSchema.zip && \
    mkdir schema && \
    tar xzf cfg-1.9.7-x86_64-unknown-linux-gnu.tar.gz && \
    mv cfg schema/ && \
    unzip AUTOSAR_MMOD_XMLSchema.zip -d schema

RUN git clone --depth=1 https://github.com/toppers/atk2-sc1.git && \
    mkdir -p atk2-sc1/cfg/cfg && \
    cp /home/toppers/schema/* atk2-sc1/cfg/cfg/

ENV PATH=/usr/local/athrill-gcc/bin/:${PATH}
ENV PATH=/home/toppers/athrill-target-rh850f1x/athrill/bin/linux:${PATH}

USER vscode
