#===========================================================================
# MAIN template ARM
#===========================================================================
NAMEPROJ   =test_stm32f051r8

FLAGS	   = -mcpu=cortex-m0
FLAGS	   += -mthumb
FLAGS	   += -O3

# The path to the tool change
TOOLCHAIN  =
# The path to the libraries for the core
CORE_LIB   =/usr/lib/arm-none-eabi/newlib/armv6-m/
# The path to the core libraries GCC
GCC_LIB    =/usr/lib/gcc/arm-none-eabi/4.8.2/armv6-m/
# Path to the project
PATH_PROJ  =../file/
PATH_INCLU =$(PATH_PROJ)

PATH_BIN   =$(PATH_PROJ)bin/
PATH_SRC   =$(PATH_PROJ)src/
PATH_INC   =$(PATH_PROJ)inc/

CC         =$(TOOLCHAIN)arm-none-eabi-gcc
CPP        =$(TOOLCHAIN)arm-none-eabi-g++
AS         =$(TOOLCHAIN)arm-none-eabi-as
LD         =$(TOOLCHAIN)arm-none-eabi-ld
OBJDUMP    =$(TOOLCHAIN)arm-none-eabi-objdump
OBJCOPY    =$(TOOLCHAIN)arm-none-eabi-objcopy
SIZE       =$(TOOLCHAIN)arm-none-eabi-size



#===========================================================================
# MHD44780
#===========================================================================
# Рабочий каталог
MHD44780_p =../../../hd44780/


# Дополнительные пути
MHD44780_p_inc=$(MHD44780_p)inc/
MHD44780_p_src=$(MHD44780_p)src/

# Дополнительные включения
MHD44780_p_I= \
          -I$(MHD44780_p_inc)

MHD44780_inc= \
	$(MHD44780_p_inc)hd44780.h \
	$(MHD44780_p_inc)hd44780_portmacro.h
	
MHD44780_opj= \
	hd44780.o \
	hd44780_portmacro.o



hd44780.o: $(MHD44780_p_src)hd44780.c $(MHD44780_inc)
	$(CC) $(CCFLAGS) -c $(MHD44780_p_src)hd44780.c -o hd44780.o
	
hd44780_portmacro.o: $(MHD44780_p_src)hd44780_portmacro.c $(MHD44780_inc)
	$(CC) $(CCFLAGS) -c $(MHD44780_p_src)hd44780_portmacro.c -o hd44780_portmacro.o



#===========================================================================
# MAIN FLAGS COMPIL
#===========================================================================
MAIN_I     =-I$(PATH_INC) \
            -I$(PATH_INC)cmsis \
            -I$(PATH_INC)cmsis/Include \
			$(MHD44780_p_I)

#===========================================================================
# LIB FLAGS
#===========================================================================
LIBFLAGS  =-L$(CORE_LIB) -lc -lg -L$(GCC_LIB) -lgcc

#===========================================================================
# ASM FLAGS
#===========================================================================
ASMFLAGS  = -g
ASMFLAGS  += -Wall
ASMFLAGS  += $(MAIN_I)

#===========================================================================
# C FLAGS
#===========================================================================
CCFLAGS	    = $(FLAGS)
CCFLAGS	    += -std=c99
CCFLAGS	    += -g
CCFLAGS	    += -Wall
CCFLAGS	    += $(MAIN_I)

#===========================================================================
# LINKER FLAGS
#===========================================================================
LINKFLAGS  =-T link.ld
LINKFLAGS  += -Map=$(PATH_BIN)$(NAMEPROJ).map



#===========================================================================
# MAIN
#===========================================================================
AFINC= \
	$(PATH_INC)globalincludefile.h \
	$(PATH_INC)startup_stm32f0xx.h \
	$(PATH_INC)main.h \
	$(PATH_INC)phisic.h \
	$(PATH_INC)xprintf.h

AFOBJ= \
	startup_stm32f0xx.o \
	main.o \
	phisic.o \
	xprintf.o


.PHONY : all
all: $(AFOBJ) $(MHD44780_opj)
	@$(LD) $(AFOBJ) $(MHD44780_opj) $(LINKFLAGS) $(LIBFLAGS) -o $(PATH_BIN)$(NAMEPROJ).elf
	@$(OBJDUMP) -D $(PATH_BIN)$(NAMEPROJ).elf > $(PATH_BIN)$(NAMEPROJ).asm
	@$(OBJCOPY) $(PATH_BIN)$(NAMEPROJ).elf $(PATH_BIN)$(NAMEPROJ).bin -O binary

startup_stm32f0xx.o: $(PATH_SRC)startup_stm32f0xx.c $(AFINC)
	$(CC) $(CCFLAGS) -c $(PATH_SRC)startup_stm32f0xx.c -o startup_stm32f0xx.o

phisic.o: $(PATH_SRC)phisic.c $(AFINC)
	$(CC) $(CCFLAGS) -c $(PATH_SRC)phisic.c -o phisic.o

main.o: $(PATH_SRC)main.c $(AFINC)
	$(CC) $(CCFLAGS) -c $(PATH_SRC)main.c -o main.o
#===========================================================================
# All
#===========================================================================
xprintf.o: $(PATH_SRC)xprintf.c $(AFINC)
	$(CC) $(CCFLAGS) -c $(PATH_SRC)xprintf.c -o xprintf.o

	
#===========================================================================
.PHONY : clean
clean:
	-@rm -f *.o
	-@$(SIZE) $(PATH_BIN)$(NAMEPROJ).elf
