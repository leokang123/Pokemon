#!/bin/bash

# libopenal-dev 패키지가 설치되어 있는지 확인
dpkg -s libopenal-dev > /dev/null 2>&1

# dpkg-query 결과를 통해 libopenal-dev가 설치되어 있지 않은 경우에만 설치 진행
if [ $? -ne 0 ]; then
    echo "libopenal-dev 패키지가 설치되어 있지 않습니다. 설치를 진행합니다."
    sudo apt-get update
    sudo apt-get install libopenal-dev
else
    echo "libopenal-dev 패키지가 이미 설치되어 있습니다."
fi

dpkg -s libncursesw5-dev > /dev/null 2>&1

# dpkg-query 결과를 통해 libopenal-dev가 설치되어 있지 않은 경우에만 설치 진행
if [ $? -ne 0 ]; then
    echo "libncursesw5-dev 패키지가 설치되어 있지 않습니다. 설치를 진행합니다."
    sudo apt-get update
    sudo apt-get install libncursesw5-dev
else
    echo "libncursesw5-dev 패키지가 이미 설치되어 있습니다."
fi

cd ./src 
make clean
make
./tstart