ARCH = msp430x2274
CC := msp430-gcc
UIF_TTY = /dev/ttyUSB0

CFLAGS := -g -mmcu=${ARCH} -Wall -O3 -std=gnu99
CFLAGS += -include `pwd`/config.h
LDFLAGS :=

O_FILES = main.o smps.o in.o out.o cmds.o trigger.o
SUBDIRS = drivers libsric flash430

LDFLAGS += -Ldrivers -ldrivers
LDFLAGS += -Llibsric -lsric
LDFLAGS += -Lflash430 -lflash430

all: jointio-bottom jointio-top

include depend

jointio-bottom: ${O_FILES} ${SUBDIRS}
	${CC} -o $@ ${O_FILES} ${CFLAGS} ${LDFLAGS} -Wl,-T,flash430/lkr/${ARCH}-bottom.x

jointio-top: ${O_FILES} ${SUBDIRS}
	${CC} -o $@ ${O_FILES} ${CFLAGS} ${LDFLAGS} -Wl,-T,flash430/lkr/${ARCH}-top.x

drivers:
	$(MAKE) -C $@ CC=${CC} ARCH=${ARCH} CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"

libsric:
	$(MAKE) -C $@ CC=${CC} ARCH=${ARCH} CFLAGS="${CFLAGS} -I`pwd`" LDFLAGS="${LDFLAGS}"

flash430:
	$(MAKE) -C $@ CC=${CC} ARCH=${ARCH} CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"

depend: *.c
	rm -f depend
	for file in $^; do \
		${CC} ${CFLAGS} -MM $$file -o - >> $@ ; \
	done ;

.PHONY: clean ${SUBDIRS} flash

flash: jointio-bottom
	mspdebug uif -d ${UIF_TTY} "prog $<"

clean:
	-rm -f jointio-{bottom,top} depend *.o
	for d in ${SUBDIRS} ; do\
		${MAKE} -C $$d clean ; \
	done ;

