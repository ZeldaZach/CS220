#include <stdio.h>
#include <stdlib.h>

void bad(int dummy)
{	
	int age = 11;
	int *ptr = &age;
	int i;
	
	ptr -= 0x24;
	printf("Ptr: %p\n", ptr);
	
	
}

int main()
{
	struct {
		char *name;
		int age;
	} student = {
		.name = "John",
		.age = 22
	};
	
	printf("Real Age: %p\n", &student.age);
	
	bad(sizeof(student));
	
	printf("student.name = %s\nstudent.age = %d\n", student.name, student.age);
	
	return 0;
}