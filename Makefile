include config.mk

OBJS += obj/header.o
OBJS += obj/libhttpc.o
OBJS += obj/malloc.o
OBJS += obj/method.o
OBJS += obj/request.o
OBJS += obj/response.o
OBJS += obj/status.o

all: libhttpc.a libhttpc.so

obj:
	mkdir -p $@

obj/%.o: src/%.c | obj
	${CC} -c -std=c99 -fPIC -Iinclude -o $@ ${CFLAGS} $<

${OBJS}: include/libhttpc.h

libhttpc.a libhttpc.so: ${OBJS}

libhttpc.so:
	cc -shared -o $@ ${LDFLAGS} ${LDLIBS} $^

libhttpc.a:
	ar rcs $@ $^

install: all
	install -d $(DESTDIR)/lib ${DESTDIR}/include/libhttpc ${DESTDIR}/share/man/man3
	install -m644 libhttpc.a $(DESTDIR)/lib
	install -m755 libhttpc.so $(DESTDIR)/lib
	install -m644 include/{config,libhttpc}.h $(DESTDIR)/include/libhttpc
	install -m644 man/libhttpc*.3 ${DESTDIR}/share/man/man3

uninstall:
	$(RM) $(DESTDIR)/lib/libhttpc.{a,so}
	$(RM) -r $(DESTDIR)/include/libhttpc/
	$(RM) $(DESTDIR)/share/man/man3/libhttpc*.3

clean:
	rm -f ${OBJS} libhttpc.a libhttpc.so
