#include <stdio.h>
#include <stdlib.h>
#include "file_recognizer.h"

int main(int argc, char *argv[])
{
	int fileType;
	
	/* If there aren't two arguement (./exe, file_name), die */
	if (argc != 2)
	{
		printf("Invalid input.\n");
		exit(1);
	}
	
	/* Attempt to get the file type */
	fileType = getFileType(argv[1]);
	

	/* Switch through the results of the helper function */
	switch (fileType)
	{
		case -2:
		printf("Invalid input.\n");
		break;
		
		default:
		case -1:
		printf("File type unknown.\n");
		break;
		
		case 0:
		case 1:
		printf("This is a GIF file.\n");
		break;
		
		case 2:
		printf("This is an ELF file.\n");
		break;
		
		case 3:
		printf("This is a PDF file.\n");
		break;
		
		case 4:
		printf("This is a ZIP file.\n");
		break;
		
		case 5:
		printf("This is a Java class file.\n");
		break;
		
		case 6:
		printf("This is a PNG file.\n");
		break;
	}
	
	return fileType;
}

int getFileType(char *file_name)
{
	FILE *fp;
	const int MAX_HEADER_SIZE = 9;
	unsigned char *header_bytes = malloc(MAX_HEADER_SIZE + 1);
	int i, j, found_file_type, retVal = -1;

	const unsigned char FILE_TYPES[7][9] = {
		{0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x0}, /* GIF */
		{0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x0}, /* GIF */
		{0x7F, 0x45, 0x4C, 0x46, 0x0}, /* ELF */
		{0x25, 0x50, 0x44, 0x46, 0x0}, /* PDF */
		{0x50, 0x4B, 0x0}, /* ZIP */
		{0xCA, 0xFE, 0xBA, 0xBE, 0x0}, /* JAVA CLASS */
		{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x0} /* PNG */
		
	};
	
	/* Attempt to open file "file_name" */
	fp = fopen(file_name, "r");
	
	/* File does not exist, return -2 (file not opening) */
	if (!fp)
		return -2;

	/* Convert the first few bytes of the file into a pointer of the byte values */
	for (j = 0; j < MAX_HEADER_SIZE; j++)
		header_bytes[j] = fgetc(fp);
	
	/* Now lets iterate through the FILE_TYPES array to find a header match */
	for (i = 0; i < sizeof(FILE_TYPES); i++)
	{
		found_file_type = 1; /* The default is we found a match at FILE_TYPES[i] */
		for (j = 0; FILE_TYPES[i][j] != 0x0; j++)
		{
			/* If char @ header.j != char @ FILE_TYPES.i.j => i++ (to check next in FILE_TYPES) */
			if (header_bytes[j] != FILE_TYPES[i][j])
			{
				found_file_type = 0;
				break;
			}
		}
		
		/* This will be true if and only if the header_bytes == the FILE_TYPES[i] */
		if (found_file_type)
		{
			retVal = i;
			break;
		}
	}

	fclose(fp);
	return retVal;
}
