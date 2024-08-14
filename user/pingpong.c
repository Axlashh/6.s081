#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);
    int pid = fork();
    char ll[1] = { 'o' };
    if (pid == 0) {
        close(p2c[1]);
        read(p2c[0], ll, sizeof ll);
        pid = getpid();
        printf("%d: received ping\n", pid);
        write(c2p[1], ll, sizeof ll);
        exit(0);
    }
    pid = getpid();

    write(p2c[1], ll, sizeof ll);
    close(c2p[1]);
    read(c2p[0], ll, sizeof ll);
    printf("%d: received pong\n", pid);
    exit(0);
}