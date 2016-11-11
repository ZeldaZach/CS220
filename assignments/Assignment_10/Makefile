all: test_macros build_backtrace

test_macros:
	gcc macros.c -std=c89 -m32 -g -o macros

build_backtrace:
	gcc -c -std=c89 -g -m32 -Wall bt.c -fPIC -I$(PWD)
	ar rcs libbt.a bt.o
	mkdir -p lib
	mv libbt.a ./lib

	gcc -shared -m32 -Wall bt.c btasm.S -o libbt.so -fPIC
	mv libbt.so ./lib

clean:
	rm -rf macros bt ./lib bt.o
