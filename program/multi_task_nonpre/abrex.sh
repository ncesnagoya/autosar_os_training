#!/bin/sh

ROOT_DIR=../../
OS_DIR=$ROOT_DIR/atk2-sc1
ABREX_DIR=$OS_DIR/utils/abrex


APP_NAME=toppers_atk2

ruby $ABREX_DIR/abrex.rb ./$APP_NAME.yaml
