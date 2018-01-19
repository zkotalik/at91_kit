#-----------------------------------------------------------------------------
# project name
#
PROJECT     := test

#-----------------------------------------------------------------------------
ARM_COMP_PREFIX := arm-none-eabi-

# ARM CPU, ARCH, FPU, and Float-ABI types...
# ARM_CPU:   [cortex-m0 | cortex-m0plus | cortex-m1 | cortex-m3 | cortex-m4]
# ARM_ARCH:  [6 | 7] (NOTE: must match ARM_CPU!)
# ARM_FPU:   [ | vfp]
# FLOAT_ABI: [ | soft | softfp | hard]
#
ARM_CPU   := -mcpu=arm920t
ARM_ARCH  := -march=armv4t
ARM_FPU   :=
FLOAT_ABI := -mfloat-abi=soft

AS := $(ARM_COMP_PREFIX)as
LD := $(ARM_COMP_PREFIX)ld
CC := $(ARM_COMP_PREFIX)gcc
CPP := $(ARM_COMP_PREFIX)g++
LINK := $(ARM_COMP_PREFIX)gcc
BIN := $(ARM_COMP_PREFIX)objcopy

VPATH = src inc FreeRTOS/Source FreeRTOS/Source/include \
		FreeRTOS/Demo/Common/Minimal FreeRTOS/Demo/Common/include \
		FreeRTOS/Source/portable/MemMang
INCLUDES = -Iinc -IFreeRTOS/Source/include -IFreeRTOS/Demo/Common/include

#-----------------------------------------------------------------------------
# files
#

# assembler source files
ASM_SRCS := \
	startup.s \

# C source files
C_SRCS := \
	main.c \
	led.c \
	zxtasks.c \
	tasks.c \
	queue.c \
	list.c \
	heap_2.c \
	port.c \
	portISR.c

# C++ source files
CPP_SRCS := \

OUTPUT    := $(PROJECT)
ifeq (, $(CONF))
LD_SCRIPT := $(PROJECT).ld
else
LD_SCRIPT := $(PROJECT).$(CONF).ld
endif

LIB_DIRS  :=
LIBS      :=

##############################################################################
# Typically, you should not need to change anything below this line

# basic utilities 

MKDIR := mkdir
RM    := rm

#-----------------------------------------------------------------------------
HWFLAGS := --defsym NO_MO_SETUP=1 --defsym NO_PLLA_SETUP=1 \
		   --defsym NO_PLLB_SETUP=1 --defsym NO_SMC_SETUP=1 \
		   --defsym NO_MCK_SETUP=1 --defsym NO_SDRAM_SETUP=1
RAMVECTFLAGS := --defsym NO_COPY=1
IRFLAGS := 	--defsym NO_PLLB_SETUP=1

ifeq (rel, $(CONF)) # Release configuration ..................................

BIN_DIR := rel

ASFLAGS = $(ARM_CPU) $(ARM_CPU) $(ARM_FPU) $(INCLUDES) 

CFLAGS = $(ARM_CPU) $(ARM_CPU) $(ARM_FPU) $(FLOAT_ABI) -Wall \
		 -Wextra -Wcast-align -fomit-frame-pointer \
		 -fno-strict-aliasing -fno-dwarf2-cfi-asm \
		 -O1 $(INCLUDES) -DNDEBUG

CPPFLAGS = $(ARM_CPU) $(ARM_CPU) $(ARM_FPU) $(FLOAT_ABI) -Wall \
	-O1 $(INCLUDES) -DNDEBUG

else ifeq (ira, $(CONF)) # Release configuration ..................................

BIN_DIR := ira

ASFLAGS = $(ARM_CPU) $(ARM_CPU) $(ARM_FPU) $(INCLUDES) $(RAMVECTFLAGS) $(IRFLAGS)

CFLAGS = $(ARM_CPU) $(ARM_CPU) $(ARM_FPU) $(FLOAT_ABI) -Wall \
		 -Wextra -Wcast-align -fomit-frame-pointer \
		 -fno-strict-aliasing -fno-dwarf2-cfi-asm \
		 -O1 $(INCLUDES) -DNDEBUG

CPPFLAGS = $(ARM_CPU) $(ARM_CPU) $(ARM_FPU) $(FLOAT_ABI) -Wall \
	-O1 $(INCLUDES) -DNDEBUG

else # default Debug configuration ..........................................

BIN_DIR := dbg

ASFLAGS = -g $(ARM_CPU) $(ARM_ARCH) $(ARM_FPU) $(INCLUDES) $(HWFLAGS)

CFLAGS = -g $(ARM_CPU) $(ARM_ARCH) $(ARM_FPU) $(FLOAT_ABI) -Wall \
		 -Wextra -Wcast-align -fomit-frame-pointer \
		 -fno-strict-aliasing -fno-dwarf2-cfi-asm \
		 -O $(INCLUDES)

CPPFLAGS = -g $(ARM_CPU) $(ARM_ARCH) $(ARM_FPU) $(FLOAT_ABI) -Wall \
	-O $(INCLUDES)

endif # ......................................................................


#LINKFLAGS = -T$(LD_SCRIPT) $(ARM_CPU) $(ARM_ARCH) $(ARM_FPU) $(FLOAT_ABI) \
	-nostdlib -specs=nano.specs \
	-Wl,-Map,$(BIN_DIR)/$(OUTPUT).map,--cref,--gc-sections $(LIB_DIRS)

LINKFLAGS = -T$(LD_SCRIPT) $(ARM_CPU) $(ARM_ARCH) $(ARM_FPU) $(FLOAT_ABI) \
	-Wl,-Map,$(BIN_DIR)/$(OUTPUT).map,--cref,--gc-sections $(LIB_DIRS)

ASM_OBJS     := $(patsubst %.s,%.o,  $(notdir $(ASM_SRCS)))
C_OBJS       := $(patsubst %.c,%.o,  $(notdir $(C_SRCS)))
CPP_OBJS     := $(patsubst %.cpp,%.o,$(notdir $(CPP_SRCS)))

TARGET_BIN   := $(BIN_DIR)/$(OUTPUT).bin
TARGET_ELF   := $(BIN_DIR)/$(OUTPUT).elf
ASM_OBJS_EXT := $(addprefix $(BIN_DIR)/, $(ASM_OBJS))
C_OBJS_EXT   := $(addprefix $(BIN_DIR)/, $(C_OBJS))
C_DEPS_EXT   := $(patsubst %.o, %.d, $(C_OBJS_EXT))
CPP_OBJS_EXT := $(addprefix $(BIN_DIR)/, $(CPP_OBJS))
CPP_DEPS_EXT := $(patsubst %.o, %.d, $(CPP_OBJS_EXT))

# create $(BIN_DIR) if it does not exist
ifeq ("$(wildcard $(BIN_DIR))","")
$(shell $(MKDIR) $(BIN_DIR))
endif

#-----------------------------------------------------------------------------
# rules
#

all: $(TARGET_BIN)
#all: $(TARGET_ELF)

$(TARGET_BIN): $(TARGET_ELF)
	$(BIN) -O binary $< $@

$(TARGET_ELF) : $(ASM_OBJS_EXT) $(C_OBJS_EXT) $(CPP_OBJS_EXT)
	$(LINK) $(LINKFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/%.d : %.c
	$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $< > $@

$(BIN_DIR)/%.d : %.cpp
	$(CPP) -MM -MT $(@:.d=.o) $(CPPFLAGS) $< > $@

$(BIN_DIR)/%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o : %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

# include dependency files only if our goal depends on their existence
ifneq ($(MAKECMDGOALS),clean)
  ifneq ($(MAKECMDGOALS),show)
-include $(C_DEPS_EXT) $(CPP_DEPS_EXT)
  endif
endif


.PHONY : clean
clean:
	-$(RM) $(BIN_DIR)/*.o \
	$(BIN_DIR)/*.d \
	$(BIN_DIR)/*.bin \
	$(BIN_DIR)/*.elf \
	$(BIN_DIR)/*.map
	
show:
	@echo PROJECT = $(PROJECT)
	@echo CONF = $(CONF)
	@echo DEFINES = $(DEFINES)
	@echo ASM_FPU = $(ASM_FPU)
	@echo ASM_SRCS = $(ASM_SRCS)
	@echo C_SRCS = $(C_SRCS)
	@echo CPP_SRCS = $(CPP_SRCS)
	@echo ASM_OBJS_EXT = $(ASM_OBJS_EXT)
	@echo C_OBJS_EXT = $(C_OBJS_EXT)
	@echo C_DEPS_EXT = $(C_DEPS_EXT)
	@echo CPP_DEPS_EXT = $(CPP_DEPS_EXT)
	@echo TARGET_ELF = $(TARGET_ELF)

