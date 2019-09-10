
# vim: ft=make noexpandtab

OBJECTS := mnet.o marp.o mether.o mtcp.o mmem.o

BINDIR_LINUX = ../bin/linux
BINDIR_MSP430G2553 = ../bin/msp430g2553

OBJDIR_TESTS = ../obj/test_mnet

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

test_mnet: LDFLAGS += $(shell pkg-config --libs check) -L../bin/linux/ -lmnet
test_mnet: CFLAGS += -DCHECK -g -Wall -Werror
test_mnet: OBJDIR := ../obj/test_mnet

all: $(BINDIR_LINUX)/libmnet.a $(BINDIR_MSP430G2553)/libmnet.a

test_mnet: $(BINDIR_LINUX)/libmnet.a $(OBJDIR_TESTS)/check.o $(OBJDIR_TESTS)/check_ether.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR_LINUX)/libmnet.a: $(addprefix ../obj/linux/,$(OBJECTS))
	$(MD) $(BINDIR_LINUX)
	$(AR) rcs $@ $^

$(BINDIR_MSP430G2553)/libmnet.a: $(addprefix ../obj/msp430g2553/,$(OBJECTS))
	$(MD) $(BINDIR_MSP430G2553)
	$(AR) rcs $@ $^

../obj/linux/%.o: $(notdir %.c)
	$(MD) $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR_TESTS)/%.o: ../tests/$(notdir %.c)
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

