all: build_loader

# DO NOT EVER DO THIS IN PRODUCTION CODE!
build_loader:
	gcc loader.c -std=c89 -Wl,-z,execstack -o loader

clean:
	rm loader
