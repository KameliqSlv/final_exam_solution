#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
    int fd = open(argv[1], O_WRONLY | O_CREAT );
    int N = atoi(argv[2]);

    for (size_t i = 0; i < N; i++) {
        uint64_t num = (uint64_t)rand()%10;
        write(fd, &num, sizeof(uint64_t));
    }

    close(fd);
    return 0;
}