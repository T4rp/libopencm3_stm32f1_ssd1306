OPENCM3_DIR = ../libopencm3

DEVICE = stm32f103C8T6

VPATH += ../src/
OBJS  += main.o ssd1306.o

CFLAGS   += -Os -ggdb3 -Wall -Wextra -flto -I../include
CPPFLAGS += -MD
LDFLAGS  += -static -nostartfiles --specs=rdimon.specs -flto
LDLIBS   += -Wl,--start-group -lc -lgcc -lrdimon -Wl,--end-group

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: clean all flash bear

all: out.bin out.elf

bear:
	make clean
	bear -- make all

flash: out.bin
	st-flash write out.bin 0x8000000

clean:
	$(Q)$(RM) -rf out.* *.o *.d  *.ld

include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/mk/gcc-rules.mk
