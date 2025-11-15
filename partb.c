// Daniel Guerrero
// W00427795

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        puts("USAGE: partb FILEIN FILEOUT");
        return 1;
    }

    const char* infile = argv[1];
    const char* outfile = argv[2];

    // Open output file for writing (create/truncate) with 0770 permissions
    int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd == -1) {
        perror("open");
        return 2;
    }

    // Redirect STDOUT to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return 2;
    }
    close(fd);

    // Print header and flush so it appears in file before exec replaces process
    printf("Category,Count\n");
    fflush(stdout);

    // Prepare args for exec: ./parta infile
    char* parta_args[3];
    parta_args[0] = "./parta";
    parta_args[1] = (char*)infile;
    parta_args[2] = NULL;

    execv("./parta", parta_args);
    // If execv returns, there was an error
    perror("exec");
    return 1;
}
