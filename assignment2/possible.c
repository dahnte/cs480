#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {  // Parent process (player1.c)
        close(pipefd[0]);  // Close unused read end

        printf("Enter a string consisting of 5 and 7: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        write(pipefd[1], buffer, strlen(buffer) + 1);

        close(pipefd[1]);  // Close write end after writing
        wait(NULL);        // Wait for child process (player2.c) to exit

        exit(EXIT_SUCCESS);
    } else {  // Child process (player2.c)
        close(pipefd[1]);  // Close unused write end

        read(pipefd[0], buffer, sizeof(buffer));
        // Perform further processing on the received data (player2.c logic)
        // Example: printing the received string
        printf("Received string in player2.c: %s", buffer);

        close(pipefd[0]);  // Close read end

        exit(EXIT_SUCCESS);
    }

    return 0;
}
