OCLDIR   = /opt/intel/inteloneapi/compiler/latest/linux/lib

CC       = clang
CFLAGS   = -std=c11
CFLAGS  += -g3 -Wall
CFLAGS  += -I../include

LDFLAGS  = -L.. -lusm
LDFLAGS += -L$(OCLDIR) -lOpenCL

all: device.x host.x shared.x

%.x: %.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

clean:
	-rm -f *.o *.x

