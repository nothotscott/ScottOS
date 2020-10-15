ASM=nasm
CC=x86_64-elf-gcc
LD=x86_64-elf-ld

OUTPUT_DIR=../bin
ASM_FLAGS=-i kernel/ -f elf64 
C_FLAGS=-I kernel/ -ffreestanding -mno-red-zone -m64 -std=c++17 -fno-rtti -fno-exceptions

ifeq ($(OS), Windows_NT)
	MKDIR = powershell mkdir
    RM = powershell del
else
	MKDIR = mkdir
    RM = rm -f
endif
#########################################

all:						boot kernel
							$(LD) $(OUTPUT_DIR)/bootloader.o $(OUTPUT_DIR)/kernel.o -e 0x0000 --oformat binary -o $(OUTPUT_DIR)/ScottOS.flp	# generate bootable binary file
#							cat $(OUTPUT_DIR)/boot.bin $(OUTPUT_DIR)/kernel.bin > $(OUTPUT_DIR)/bootloader.flp	# clunky
#							ld -Ttext 0x8000 $(OUTPUT_DIR)/kernel.o $(OUTPUT_DIR)/boot.o -o $(OUTPUT_DIR)/bootloader.o	
#							objcopy -S -O binary $(OUTPUT_DIR)/bootloader.o $(OUTPUT_DIR)/bootloader.flp
#							$(LD) $(OUTPUT_DIR)/bootloader.o --oformat binary -e 0x0000 -o $(OUTPUT_DIR)/bootloader.bin
#							cat $(OUTPUT_DIR)/bootloader.bin $(OUTPUT_DIR)/kernel.bin > $(OUTPUT_DIR)/ScottOS.flp

.PHONY:	boot
boot:						$(OUTPUT_DIR)/boot.o $(OUTPUT_DIR)/loader.o
							$(LD) $^ -e 0x0000 -Ttext 0x7c00 -o $(OUTPUT_DIR)/bootloader.o

$(OUTPUT_DIR)/boot.o:		boot/boot.asm
							$(ASM) -i boot/ -f elf64 $^ -o $@

$(OUTPUT_DIR)/loader.o:		boot/loader.asm
							$(ASM) -i boot/ -f elf64 $^ -o $@


.PHONY:	kernel
kernel:						$(OUTPUT_DIR)/kernel1.o $(OUTPUT_DIR)/kernel2.o $(OUTPUT_DIR)/library.o $(OUTPUT_DIR)/binaries.o
							$(LD) -T "link.ld" -L $(OUTPUT_DIR) 

$(OUTPUT_DIR)/kernel1.o:	kernel/kernel1.asm
							$(ASM) $(ASM_FLAGS) $^ -o $@

$(OUTPUT_DIR)/kernel2.o:	kernel/kernel2.cpp
							$(CC) $(C_FLAGS) -c $^ -o $@

$(OUTPUT_DIR)/binaries.o:	binaries.asm
							$(ASM) $(ASM_FLAGS) $^ -o $@

$(OUTPUT_DIR)/%.o:			kernel/%.cpp
							$(CC) $(C_FLAGS) -c $^ -o $@


.PHONY:	clean
clean:						# Escape * characters so they don't expand
							$(RM) $(OUTPUT_DIR)/\*.flp
							$(RM) $(OUTPUT_DIR)/\*.bin
							$(RM) $(OUTPUT_DIR)/\*.o