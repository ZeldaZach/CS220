#include <stdio.h>
#include <stdlib.h>

void bad(int dummy)
{	
	char *newName = "Quick brown fox jumped over the lazy dog";
	int newAge = 1000;

	char *n_ptr = (char *)(&newName + 0x5);
	int *a_ptr = (int *)(&newAge + 0xD);

	*n_ptr = newName;
	*a_ptr = newAge;
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
	bad(sizeof(student));
	printf("student.name = %s\nstudent.age = %d\n", student.name, student.age);	
	return 0;
}
