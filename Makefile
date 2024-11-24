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

clean:
	rm -f ${OBJS} libhttpc.a libhttpc.so
