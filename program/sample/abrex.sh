#!/bin/sh

ROOT_DIR=../../
OS_DIR=$ROOT_DIR/atk2-sc1
ABREX_DIR=$OS_DIR/utils/abrex


APP_NAME=sample1

python3 $ABREX_DIR/abrex.py ./$APP_NAME.yaml
