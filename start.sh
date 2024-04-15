#!/bin/bash

# libopenal-dev 패키지가 설치되어 있는지 확인
dpkg -s libopenal-dev > /dev/null 2>&1

# dpkg-query 결과를 통해 libopenal-dev가 설치되어 있지 않은 경우에만 설치 진행
if [ $? -ne 0 ]; then
    echo "libopenal-dev Package is not Downloaded yet. Continue Downloading."
    sudo apt-get update
    sudo apt-get install -y libopenal-dev
else
    echo "libopenal-dev is already Downloaded"
fi

dpkg -s libncursesw5-dev > /dev/null 2>&1

# dpkg-query 결과를 통해 libopenal-dev가 설치되어 있지 않은 경우에만 설치 진행
if [ $? -ne 0 ]; then
    echo "libncursesw5-dev is not Downloaded yet. Continue Downloading."
    sudo apt-get update
    sudo apt-get install -y libncursesw5-dev
else
    echo "libncursesw5-dev is already Downloaded"
fi

cd ./src 
make clean
make
./tstart
