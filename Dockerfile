FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev git \
    python3-pip \
    python3.10-venv

# Install the RISC-V GNU toolchain
RUN git clone --recursive https://github.com/riscv-collab/riscv-gnu-toolchain
WORKDIR /riscv-gnu-toolchain
RUN ./configure --enable-multilib
RUN make -j$(nproc)
# RUN rm -rf /riscv-gnu-toolchain

WORKDIR /freedom