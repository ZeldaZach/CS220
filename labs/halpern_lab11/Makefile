all: test_prelim test_retlibc

test_prelim:
	gcc -std=c89 -m32 prelim.c -o prelim

test_retlibc:
	gcc -std=c89 -m32 ret-to-libc.c btasm.S -g -o ret-to-libc

clean:
	rm prelim ret-to-libc
