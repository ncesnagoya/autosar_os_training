@echo off

del /F *.mtud cfg\*.c cfg\*.h cfg\*.inc cfg\*.mtud cfg\*.src cfg\*.srec cfg\*.syms cfg\*.tf cfg\*.asm kernel\*.mtud
rmdir /S /Q DefaultBuild cfg\DefaultBuild kernel\DefaultBuild

@pause
exit
