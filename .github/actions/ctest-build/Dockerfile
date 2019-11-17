FROM ubuntu:18.04
RUN apt-get update -y
RUN apt-get install -y software-properties-common

RUN apt-get install -y wget
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key 2>/dev/null | apt-key add -
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add -

RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN echo "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic main" >> /etc/apt/sources.list.d/llvm.list
RUN echo "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-8 main" >> /etc/apt/sources.list.d/llvm.list
RUN echo "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-9 main" >> /etc/apt/sources.list.d/llvm.list

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install -y gcc-9 gcc-8 gcc-7 gcc-6 gcc-5 gcc-4.8 cmake clang-9 clang-tidy-9 clang-8 clang-tidy-8 clang-7 clang-tidy-7 clang-6.0 clang-tidy-6.0 ninja-build valgrind git pkg-config libsystemd-dev

# COPY entrypoint.sh /entrypoint.sh
# RUN chmod +x /entrypoint.sh
# 
# ENTRYPOINT ["/entrypoint.sh"]
