all: proj1 proj2

proj1:
	gcc -c -std=c89 -g -Wall sorter.c -fPIC -I$(PWD)
	ar rcs libsort.a
	mkdir -p lib
	mv libsort.a ./lib/

	gcc -shared -o libsort.so sorter.o
	mv libsort.so ./lib/

proj2:
	gcc estimator.c estimator.S -m32 -std=c89 -g -o estimator

clean:
	rm -rf sorter.o ./lib estimator
