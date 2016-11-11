all: test_macros test_backtrace build_backtrace

test_macros:
	gcc macros.c -std=c89 -g -o macros

test_backtrace:
	gcc bt.c btasm.S -std=c89 -g -o bt

build_backtrace:
	gcc -c -std=c89 -g -Wall bt.c btasm.S -fPIC -I$(PWD)
	ar rcs libbt.a
	mkdir -p lib
	mv libbt.a ./lib

	gcc -shared -Wall bt.c btasm.S -o libbt.so -fPIC
	mv libbt.so ./lib
clean:
	rm -rf macros bt ./lib bt.o btasm.o
