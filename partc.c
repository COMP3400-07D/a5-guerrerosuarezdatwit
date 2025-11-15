// Daniel Guerrero
// W00427795

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("USAGE: partc FILEIN");
        return 1;
    }

    const char* infile = argv[1];

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent: act as producer (parta)
        // Close read end
        close(pipefd[0]);
        // Redirect STDOUT to pipe write end
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            return 1;
        }
        close(pipefd[1]);

        // Exec parta with infile
        char* parta_args[3];
        parta_args[0] = "./parta";
        parta_args[1] = (char*)infile;
        parta_args[2] = NULL;
        execv("./parta", parta_args);
        perror("exec");
        return 1;
    } else {
        // Child: act as consumer (sort)
        // Close write end
        close(pipefd[1]);
        // Redirect STDIN to pipe read end
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }
        close(pipefd[0]);

        // Exec sort -t, -k2 -n
        char* sort_args[] = {"sort", "-t,", "-k2", "-n", NULL};
        execv("/usr/bin/sort", sort_args);
        perror("exec");
        _exit(1);
    }

    return 0;
}
