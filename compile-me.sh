#!/bin/bash

USE_VERBOSE=""
CMAKE_BUILD_FLAGS=""
DOWNLOAD_CODE_AFTER_BUILD=0
IHX_FILE="build/STM8S103F3.ihx"
EXPORT_FOLDER=""

remove_build_folder_if_present() {
    if ls -d ./*/ | grep -Fq 'build' ; then
        rm -rf build/
    fi
}

build_code() {
    if  ! ls -d ./*/ | grep -qF 'build/' ; then
        mkdir build
        cd build || exit
        cmake $CMAKE_BUILD_FLAGS ..
        make $USE_VERBOSE
        cd ..
    else
        cd build || exit
        make $USE_VERBOSE
        cd ..
    fi
}

download_code() {
    echo "[INFO] Downloading code ($1) to the board"
    stm8flash -c stlinkv2 -p stm8s103f3 -s flash -w "$1"
}

print_usage() {
    echo "Usage: ./build-project [OPTION]..."
    echo "Options:"
    echo "  -S              Use VERBOSE=1 for make command"
    echo "  -r              Rebuild code"
    echo "  -f              Specifies file .ihx to use for download to the board"
    echo "  -d              Download code to board after building it"
    echo "  -e              Export .ihx file to the specified folder"
    echo "  -h              Print this message and exits"
}

while getopts 'Srdf:e:h' flag; do
  case "${flag}" in
    S)  echo "[INFO] Using verbose make output"
        USE_VERBOSE="VERBOSE=1" ;;
    r)  echo "[INFO] Rebuilding code"
        remove_build_folder_if_present ;;
    d)  DOWNLOAD_CODE_AFTER_BUILD=1 ;;
    f)  IHX_FILE="${OPTARG}" ;;
    e)  EXPORT_FOLDER="${OPTARG}" ;;
    h)  print_usage
        exit 0 ;;
    *)  print_usage
       exit 1 ;;
  esac
done

build_code

if [[ $EXPORT_FOLDER != "" ]]; then
    cp "$IHX_FILE" "$EXPORT_FOLDER"  
fi

if [ $DOWNLOAD_CODE_AFTER_BUILD -eq 1 ]; then
    download_code "$IHX_FILE"
fi
