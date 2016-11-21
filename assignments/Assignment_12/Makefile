all: build_loader

# DO NOT EVER DO THIS IN PRODUCTION CODE!
build_loader:
	gcc loader.c -m32 -std=c89 -g -Wl,-z,execstack -o loader

clean:
	rm loader
