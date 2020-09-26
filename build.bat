@echo off
IF NOT EXIST bin (
	mkdir bin
)
cd src
make clean
make
cd ../
IF "%1"=="run" (
	start bochsrc.bxrc
)