SRC_DIR = src
BUILD_DIR = build
INC_DIR = ../includes
MODNAME = umcxray
TARGET = $(BUILD_DIR)/$(MODNAME)

CC = gcc
LD = ld

CFLAGS = -m64 -O2 -D_KERNEL -DDEBUG -mcmodel=kernel -I/usr/include/sys -I$(INC_DIR)
LDFLAGS = -r -ztype=kmod

include objs.mk

all: $(TARGET)

$(TARGET): $(OBJS)
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

ins:
	pfexec cp umcxray.conf /kernel/drv/umcxray.conf
	pfexec cp $(TARGET) /kernel/drv/amd64/$(MODNAME)
	pfexec rem_drv $(MODNAME) || true
	pfexec add_drv -u -m '* 0666 root sys' $(MODNAME)
	pfexec devfsadm -u

info:
	@printf "\n"
	@modinfo | grep $(MODNAME) || true
	@printf "\n======================================================================================\n\n"
	@tail /var/adm/messages
	@printf "\n"

rem:
	pfexec modunload $(MODNAME) || true
	pfexec rm /kernel/drv/umcxray.conf || true
	pfexec rm /kernel/drv/amd64/$(MODNAME)

