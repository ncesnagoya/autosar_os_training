@echo off

set ROOT_DIR=../../
set OS_DIR=%ROOT_DIR%/atk2-sc1
set ABREX_DIR=%OS_DIR%/utils/abrex


set APP_NAME=toppers_atk2

ruby %ABREX_DIR%/abrex.rb ./%APP_NAME%.yaml

pause
exit
