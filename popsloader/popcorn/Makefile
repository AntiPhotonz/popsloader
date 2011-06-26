all:
	$(PRO_HOME)/contrib/pspgz.py popcorn.prx $(PRO_HOME)/contrib/SystemControl.hdr popcorn.prx PROPopcornManager 0x1007

TARGET = popcorn

OBJS = main.o icon.o popcorn_patch_offset.o imports.o $(PRO_HOME)/Stargate/analog_patch.o
OBJS += $(PRO_HOME)/Common/utils.o $(PRO_HOME)/Common/strsafe.o $(PRO_HOME)/Common/libs.o

CFLAGS = -Os -G0 -Wall -I. -I$(PRO_HOME)/Common -I$(PRO_HOME)/include

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG=1
OBJS += $(PRO_HOME)/Common/printk.o
else
endif

ifeq ($(CONFIG_500), 1)
CFLAGS += -DCONFIG_500=1
PSP_FW_VERSION = 500
endif

ifeq ($(CONFIG_620), 1)
CFLAGS += -DCONFIG_620=1
PSP_FW_VERSION = 620
endif

ifeq ($(CONFIG_610), 1)
CFLAGS += -DCONFIG_610=1
PSP_FW_VERSION = 610
endif

ifeq ($(CONFIG_600), 1)
CFLAGS += -DCONFIG_600=1
PSP_FW_VERSION = 600
endif

ifeq ($(CONFIG_635), 1)
CFLAGS += -DCONFIG_635=1
PSP_FW_VERSION = 635
endif

ifeq ($(CONFIG_639), 1)
CFLAGS += -DCONFIG_639=1
PSP_FW_VERSION = 639
endif

LDFLAGS = -mno-crt0 -nostartfiles -L. -L$(PRO_HOME)/libs
LIBS += -lpspmodulemgr_kernel -lpspsystemctrl_kernel -lpspkubridge
LIBS += -lpspsemaphore

BUILD_PRX=1
PRX_EXPORTS = exports.exp

USE_KERNEL_LIBS=1
USE_KERNEL_LIBC=1

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak