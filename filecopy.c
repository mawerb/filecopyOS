/**
 * filecopy.c
 * 
 * This program copies files using a pipe.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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

	if (pipe(fd) == -1) {
		printf("An error occured when opening the pipe\n");
		return 1;
	}

	int pid = fork();
	if (pid == -1) {
		printf("An error occured while creating the child process.\n");
		exit(1);
	}
	if (pid == 0) {
		close(fd[WRITE_END]);

		char buf[4096];
		ssize_t n;
		int dst_fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
		if (dst_fd < 0) {
			printf("An error occured opening the output file %s\n", output);
			exit(1);
		}
		
		while ((n = read(fd[READ_END], buf, sizeof(buf))) > 0) {
			write(dst_fd, buf, n);
		}

		close(fd[READ_END]);
		close(dst_fd);
	} else {
		close(fd[READ_END]);

		char buf[4096];
		ssize_t n;	
		int src_fd = open(input, O_RDONLY);

		if (src_fd < 0) {
			printf("An error occured opening the input file. Are you sure %s exists?\n", input);
			exit(1);
		}

		while ((n = read(src_fd, buf, sizeof(buf))) > 0) {
			write(fd[WRITE_END], buf, n);
		}
		close(fd[WRITE_END]);
		close(src_fd);
		
		wait(NULL);
	}

	return 0;
}
