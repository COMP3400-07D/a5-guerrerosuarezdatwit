// Daniel Guerrero
// W00427795

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    if (argc != 2) {
        puts("USAGE: parta FILEIN");
        return 1;
    }

    const char* filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        // file not found or cannot open
        printf("ERROR: %s not found", filename);
        return 2;
    }

    long upper = 0, lower = 0, number = 0, space = 0, other = 0;
    ssize_t nread;
    while ((nread = read(fd, buffer, BUFSIZE)) > 0) {
        for (ssize_t i = 0; i < nread; ++i) {
            unsigned char ch = (unsigned char)buffer[i];
            if (isupper(ch)) ++upper;
            else if (islower(ch)) ++lower;
            else if (isdigit(ch)) ++number;
            else if (isspace(ch)) ++space;
            else ++other;
        }
    }

    close(fd);

    // Print in the order required by the tests (note label "Other" singular)
    printf("Upper,%ld\n", upper);
    printf("Lower,%ld\n", lower);
    printf("Number,%ld\n", number);
    printf("Space,%ld\n", space);
    printf("Other,%ld\n", other);

    return 0;
}
