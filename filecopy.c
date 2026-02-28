/**
 * filecopy.c
 * 
 * This program copies files using a pipe.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{

	int fd[2];

	if (argc < 3) {
		printf("Usage %s <input> <output>", argv[0]);
		return 1;
	}

	char *input = argv[1];
	char *output = argv[2];

	FILE* inptr;
	FILE* outptr;

	inptr = fopen(input , "r");
	outptr = fopen(output , "w");

	pipe(fd);

	return 0;
}
