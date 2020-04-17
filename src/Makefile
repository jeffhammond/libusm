CC      = clang
CFLAGS  = -std=c11

AR      = ar
ARFLAGS = -r

all: libusm.a

libusm.a: libusm.o
	$(AR) $(ARFLAGS) $@ $<

libusm.o: libusm.x
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f libusm.a libusm.o

