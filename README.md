
# How to cross compile this project

$ source ~/your/sdp/path/qnxsdp-env.sh
$ mkdir ./build
$ cd ./build
$ cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/modules/qnx-sadk-toolchain.cmake
