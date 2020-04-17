CC      = clang
CFLAGS  = -std=c11
CFLAGS += -I./include

AR      = ar
ARFLAGS = -r

all: libusm.a

libusm.a: libusm.o
	$(AR) $(ARFLAGS) $@ $<

libusm.o: src/libusm.c include/libusm.h include/CL/cl_usm.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f libusm.a libusm.o

