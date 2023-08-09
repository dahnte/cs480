#include <unistd.h> /* unlink, close, read */
#include <stdlib.h> /* malloc */
#include <fcntl.h> /* open */
#include <sys/stat.h> /* mkfifo */
#include <sys/types.h>
#include <errno.h> /* variable to handle errors properly */
#include <stdio.h>
#include <string.h> /* memset */
#include "stringGame.h" 

int main(int argc, char **argv) {
    char *string = malloc(sizeof(char) * BUFFER_SIZE);
	memset(string, 0 , BUFFER_SIZE);
    int result = 0;
	int write_fd;
	int read_fd;

	/* create pipe for player2 */
	if(mkfifo(P2WRITE, 0777) == -1 && errno != EEXIST) {
		fprintf(stderr, "Failed to create pipe\n");
		return 1;
	}

    /* begin main game loop! */
	while(1) {
		read_fd = open(P1WRITE, O_RDONLY);
		if(read_fd == -1) {
			fprintf(stderr, "Failed to open pipe for reading\n");
			return 1;
		}
		if(read(read_fd, string, sizeof(char) * BUFFER_SIZE) == -1) {
			fprintf(stderr, "Failed to read from pipe\n");
			return 1;
		}
		close(read_fd);

		if(result = checkString(string, argv[0]) != 2) {
			break;
		}

		editString(string);

		if(result = checkString(string, argv[0]) != 2) {
			write_fd = open(P2WRITE, O_WRONLY);
			if(write_fd == -1) {
				fprintf(stderr, "Failed to open pipe for writing\n");
				return 1;
			}
			if(write(write_fd, string, sizeof(char) * BUFFER_SIZE) == -1) {
				fprintf(stderr, "Failed to write to pipe\n");
				return 1;
			}
			close(write_fd);
			break;
		}

		write_fd = open(P2WRITE, O_WRONLY);
		if(write_fd == -1) {
			fprintf(stderr, "Failed to open pipe for writing\n");
			return 1;
		}
		if(write(write_fd, string, sizeof(char) * BUFFER_SIZE) == -1) {
			fprintf(stderr, "Failed to write to pipe\n");
			return 1;
		}
		close(write_fd);
	}
	unlink(P2WRITE);
    return 0;
}
