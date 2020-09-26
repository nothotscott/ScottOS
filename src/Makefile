ASM=nasm
CC=x86_64-elf-gcc
LD=x86_64-elf-ld

OUTPUT_DIR=../bin
ASM_FLAGS = -i kernel/ -f elf64 
C_FLAGS = -I kernel/ -ffreestanding -mno-red-zone -m64 -std=c++17

ifeq ($(OS), Windows_NT)
	MKDIR = powershell mkdir
    RM = powershell del
else
	MKDIR = mkdir
    RM = rm -f
endif
#########################################

all:						boot kernel
							cat $(OUTPUT_DIR)/boot.bin $(OUTPUT_DIR)/kernel.bin > $(OUTPUT_DIR)/bootloader.flp	# clunky

.PHONY:	boot
boot:						boot/boot.asm
							$(ASM) $^ -i boot/ -f bin -o $(OUTPUT_DIR)/$@.bin

.PHONY:	kernel
kernel:						$(OUTPUT_DIR)/kernel1.o $(OUTPUT_DIR)/kernel2.o $(OUTPUT_DIR)/library.o
							$(LD) -T "link.ld" -L $(OUTPUT_DIR)

$(OUTPUT_DIR)/kernel1.o:	kernel/kernel1.asm
							$(ASM) $(ASM_FLAGS) $^ -o $@

$(OUTPUT_DIR)/kernel2.o:	kernel/kernel2.cpp
							$(CC) $(C_FLAGS) -c $^ -o $@

$(OUTPUT_DIR)/%.o:			kernel/%.cpp
							$(CC) $(C_FLAGS) -c $^ -o $@


.PHONY:	clean
clean:						# Escape * characters so they don't expand
							$(RM) $(OUTPUT_DIR)/\*.flp
							$(RM) $(OUTPUT_DIR)/\*.bin
							$(RM) $(OUTPUT_DIR)/\*.o