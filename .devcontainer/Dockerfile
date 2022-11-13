# [Choice] Debian / Ubuntu version (use Debian 11, Ubuntu 18.04/22.04 on local arm64/Apple Silicon): debian-11, debian-10, ubuntu-22.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT=debian-11
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Install CMake version different from what base image has already installed. 
# CMake reinstall choices: none, 3.21.5, 3.22.2, or versions from https://cmake.org/download/
# ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"

# Optionally install the cmake for vcpkg
# COPY ./reinstall-cmake.sh /tmp/
# RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
#         chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
#     fi \
#     && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# USER root

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends git wget make ruby gem

WORKDIR /home/toppers
RUN wget https://github.com/toppers/athrill-gcc-v850e2m/releases/download/v1.1/athrill-gcc-package.tar.gz && \
    tar xzf athrill-gcc-package.tar.gz && \
	tar xzf athrill-gcc-package/athrill-gcc.tar.gz && \
    mv usr/local/athrill-gcc /usr/local/

RUN wget https://github.com/toppers/athrill-target-rh850f1x/releases/download/v0.A.2/athrill-target-rh850f1x-x86_64-linux-20220813.tar.gz && \
    tar xzf athrill-target-rh850f1x-x86_64-linux-20220813.tar.gz && \
    cp athrill-target-rh850f1x/build_linux/athrill2 athrill-target-rh850f1x/athrill/bin/linux/

RUN wget https://github.com/mitsut/cfg/releases/download/1.9.7/cfg-1.9.7-x86_64-unknown-linux-gnu.tar.gz && \
	wget https://www.autosar.org/fileadmin/user_upload/standards/classic/4-0/AUTOSAR_MMOD_XMLSchema.zip && \
	mkdir schema && \
    tar xzf cfg-1.9.7-x86_64-unknown-linux-gnu.tar.gz && \
    mv cfg schema/ && \
	unzip AUTOSAR_MMOD_XMLSchema.zip -d schema

RUN git clone --depth=1 https://github.com/toppers/atk2-sc1.git && \
    mkdir -p atk2-sc1/cfg/cfg && \
    cp /home/toppers/schema/* atk2-sc1/cfg/cfg/

ENV PATH /usr/local/athrill-gcc/bin/:${PATH}
ENV PATH /home/toppers/athrill-target-rh850f1x/athrill/bin/linux:${PATH}

# USER codespace