FROM mcr.microsoft.com/devcontainers/base:2-trixie

USER root
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        git make python3 python3-yaml unzip wget \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /home/toppers
RUN wget https://github.com/toppers/athrill-gcc-v850e2m/releases/download/v1.1/athrill-gcc-package.tar.gz && \
    tar xzf athrill-gcc-package.tar.gz && \
    tar xzf athrill-gcc-package/athrill-gcc.tar.gz && \
    mv usr/local/athrill-gcc /usr/local/

# athrill3: the RH850F1x simulator built from the cpp branch of
# toppers/athrill-target-rh850f1x (CMake, Athrill core cpp).
ARG ATHRILL_TARGET_TAG=RC2-v1.0.0
ARG ATHRILL_TARGET_ASSET=athrill-target-rh850f1x-x86_64-linux-20261104.tar.gz
ARG ATHRILL_TARGET_SHA256=14a9ac6e33aec22fac3a55c8efe1b80caab29e6246d308820f495e72600b00a8
RUN wget https://github.com/toppers/athrill-target-rh850f1x/releases/download/${ATHRILL_TARGET_TAG}/${ATHRILL_TARGET_ASSET} && \
    echo "${ATHRILL_TARGET_SHA256}  ${ATHRILL_TARGET_ASSET}" | sha256sum -c - && \
    tar xzf ${ATHRILL_TARGET_ASSET} && \
    rm ${ATHRILL_TARGET_ASSET} && \
    athrill-target-rh850f1x/bin/athrill3 2>&1 | grep -q "TARGET:"

RUN git clone --depth=1 https://github.com/toppers/atk2-sc1.git

# cfg_py parses ARXML with Python's expat, which rejects multi-byte
# encodings such as EUC-JP. Convert the kernel's EUC-JP ARXML files
# (target_serial.arxml, ostm.arxml) to UTF-8, as atk2_sc1_shin ships them.
RUN grep -rl --include='*.arxml' 'encoding="EUC-JP"' atk2-sc1 | while read -r f; do \
        iconv -f EUC-JP -t UTF-8 "$f" | sed '1s/encoding="EUC-JP"/encoding="UTF-8"/' > "$f.utf8" && \
        mv "$f.utf8" "$f"; \
    done && \
    ! grep -rl --include='*.arxml' 'encoding="EUC-JP"' atk2-sc1

# The configurator (cfg_py) and the YAML-to-ARXML generator (abrex.py) come
# from atk2_sc1_shin; both are Python and need no AUTOSAR XML schema.
# The pinned commit is shin main plus the boolean fix of
# https://github.com/exshonda/atk2_sc1_shin/pull/1; switch back to
# exshonda/atk2_sc1_shin once that is merged.
ARG SHIN_REPO=mitsut/atk2_sc1_shin
ARG SHIN_REF=7b8e16f6008dbaa84a7e77eb5a850ffd47deef03
RUN wget -O shin.tar.gz https://github.com/${SHIN_REPO}/archive/${SHIN_REF}.tar.gz && \
    mkdir shin && \
    tar xzf shin.tar.gz -C shin --strip-components=1 && \
    mkdir -p atk2-sc1/cfg && \
    cp -r shin/cfg/cfg_py atk2-sc1/cfg/cfg_py && \
    rm -rf atk2-sc1/cfg/cfg_py/tests && \
    cp shin/utils/abrex/abrex.py shin/utils/abrex/param_info.yaml atk2-sc1/utils/abrex/ && \
    rm -rf shin shin.tar.gz

ENV PATH=/usr/local/athrill-gcc/bin/:${PATH}
ENV PATH=/home/toppers/athrill-target-rh850f1x/bin:${PATH}

USER vscode
