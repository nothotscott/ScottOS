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
IF "%1"=="debug" (
	cd src
	make debug
	cd ../
)