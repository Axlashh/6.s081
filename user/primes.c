#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pipenum = 0;
    int p[33][2];
    int nums[36];
    pipe(p[0]);
    for (int i = 2; i <= 35; i++) {
        nums[i] = i;
        write(p[0][1], nums + i, sizeof nums[i]);
    }
    close(p[0][1]);

fo: int pid = fork();

    if (pid == 0) {
        pipenum++;
        int fatherPipe = pipenum - 1;
        int t, ne;
        int stop = read(p[fatherPipe][0], &t, sizeof t);
        if (stop == 0) {
            close(p[fatherPipe][0]);
            exit(0);
        }
        printf("prime %d\n", t);
        pipe(p[pipenum]);
        while (1) {
            stop = read(p[fatherPipe][0], &ne, sizeof ne);
            if (stop == 0) {
                close(p[fatherPipe][0]);
                close(p[pipenum][1]);
                goto fo;
            }
            if (ne % t != 0) {
                write(p[pipenum][1], nums + ne, sizeof nums[ne]);
            }
        }
    }
    wait(0);
    exit(0);
}