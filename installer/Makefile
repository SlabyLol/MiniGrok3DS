# MiniGrok Installer - standard 3DS homebrew (3dsx), optional CIA
.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment.")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

TARGET   := MiniGrokInstaller
BUILD    := build
SOURCES  := source
DATA     := data
INCLUDES := include

APP_TITLE       := MiniGrok Installer
APP_DESCRIPTION := Installs MiniGrok.3gx as default plugin
APP_AUTHOR      := MiniGrok Team

ARCH     := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
CFLAGS   := -g -Wall -O2 -mword-relocations -ffunction-sections $(ARCH)
CFLAGS   += $(INCLUDE) -D__3DS__
CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS  := -g $(ARCH)
LDFLAGS   = -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)
LIBS     := -lctru -lm
LIBDIRS  := $(CTRULIB)

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT := $(CURDIR)/$(TARGET)
export TOPDIR := $(CURDIR)
export VPATH  := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                 $(foreach dir,$(DATA),$(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(BUILD)

CFILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

ifeq ($(strip $(CPPFILES)),)
export LD := $(CC)
else
export LD := $(CXX)
endif

export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES_BIN     := $(addsuffix .o,$(BINFILES))
export OFILES         := $(OFILES_BIN) $(OFILES_SOURCES)
export HFILES         := $(addsuffix .h,$(subst .,_,$(BINFILES)))
export INCLUDE        := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
                         $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                         -I$(CURDIR)/$(BUILD)
export LIBPATHS       := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: all clean

all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@rm -fr $(BUILD) $(TARGET).3dsx $(TARGET).smdh $(TARGET).elf $(TARGET).cia

else

DEPENDS := $(OFILES:.o=.d)

all: $(OUTPUT).3dsx

$(OUTPUT).3dsx: $(OUTPUT).elf $(OUTPUT).smdh

$(OUTPUT).elf: $(OFILES)

$(OFILES_SOURCES): $(HFILES)

%.bin.o %_bin.h: %.bin
	@echo $(notdir $<)
	@$(bin2o)

# 3gx embedded as binary blob (filename MiniGrok.3gx -> MiniGrok_3gx)
%.3gx.o %_3gx.h: %.3gx
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

endif
