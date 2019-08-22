
# vim: ft=make noexpandtab

OBJECTS := net.o arp.o ether.o tcp.o

BINDIR_LINUX = ../bin/linux
BINDIR_MSP430G2553 = ../bin/msp430g2553

MD=mkdir -v -p

CFLAGS := -Wall -Werror -I../../mfat/src

$(BINDIR_LINUX)/libmnet.a: OBJDIR := ../obj/linux

$(BINDIR_MSP430G2553)/libmnet.a: OBJDIR := ../obj/msp430g2553
$(BINDIR_MSP430G2553)/libmnet.a: AR := msp430-ar
$(BINDIR_MSP430G2553)/libmnet.a: CC := msp430-gcc
$(BINDIR_MSP430G2553)/libmnet.a: CFLAGS += \
	-mmcu=msp430g2553 \
	-g \
	-pg \
	-Os \
	-DUSE_DISK_RO \
	-fno-builtin \
	-ffreestanding \
	-nostdlib

test_mnet: LDFLAGS += $(shell pkg-config --libs check) -L. -lmbmp
test_mnet: CFLAGS += -DCHECK -g -Wall -Werror
test_mnet: OBJDIR := ../obj/test_mbmp

all: $(BINDIR_LINUX)/libmnet.a $(BINDIR_MSP430G2553)/libmbmp.a

test_mnet: libmbmp.a check.o
	$(CC) -o $@ $(OBJDIR)/check.o $(LDFLAGS)

$(BINDIR_LINUX)/libmnet.a: $(addprefix ../obj/linux/,$(OBJECTS))
	$(MD) $(BINDIR_LINUX)
	$(AR) rcs $@ $^

$(BINDIR_MSP430G2553)/libmnet.a: $(addprefix ../obj/msp430g2553/,$(OBJECTS))
	$(MD) $(BINDIR_MSP430G2553)
	$(AR) rcs $@ $^

../obj/linux/%.o: $(notdir %.c)
	$(MD) $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

../obj/msp430g2553/%.o: $(notdir %.c)
	$(MD) $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf ../obj; \
	rm -f test_mnet; \
	rm -rf ../bin

