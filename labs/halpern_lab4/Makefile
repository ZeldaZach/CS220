all: ptrs main secret

ptrs:
	gcc ptrs.c -o ptrs.o -std=c89 -g
	
main:
	gcc print_main.c -o print_main.o -std=c89 -g
	
secret:
	gcc -o secret.o main.c secret_obj.o -std=c89
	
clean:
	rm ptrs.o
	rm print_main.o
	rm secret.o