#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include <errno.h>
#include <stdlib.h>

const char filename[] = "fopi01_secure.c";

struct flocks {
    short l_type;
    short l_whence;
    off_t l_start;
    off_t l_len;
    off_t l_pid;
};

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    struct flocks myFlock = {F_RDLCK};

    printf("Press <RETURN> to try to get lock: ");
    getchar();

    printf("Trying to get lock... ");
    int fd = open(filename, O_RDWR);
    if (fd < 0){
        return EXIT_FAILURE;
    }

    if (fcntl(fd, F_GETLK, &myFlock) < 0) {
        return EXIT_FAILURE;
    }

    myFlock.l_type = F_WRLCK;
    if (fcntl(fd, F_SETLKW, &myFlock) < 0) {
        return EXIT_FAILURE;
    }

    printf("Got lock!\nPress <RETURN> to release lock: ");
    getchar();
    myFlock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &myFlock) < 0) {
        return EXIT_FAILURE;
    }

    close(fd);
    printf("Unlocked.\n");
    return 0;
}
