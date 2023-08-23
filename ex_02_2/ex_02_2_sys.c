#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int dig_sum(uint64_t num){
    int sum = 0;
    while(num > 0){
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main(int argc, char *argv[]){
    int total_sum = 0;

    for(int i = 1; i < argc; i++){
        pid_t pid = fork();

        if(pid == 0){
            int fd = open(argv[i], O_RDONLY);

            uint64_t num;
            int file_sum = 0;
            size_t bytes_read;
            while((bytes_read = read(fd, &num, sizeof(uint64_t))) > 0){
                file_sum += dig_sum(num);
            }

            close(fd);
            printf("%s - %d\n", argv[i], file_sum);
            //write(STDOUT_FILENO, &file_sum, sizeof(file_sum));
            exit(file_sum);

        }
    }

    for(int i = 1; i < argc; i++){
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            total_sum += WEXITSTATUS(wstatus);
        }
    }

    //write(STDOUT_FILENO, total_sum, sizeof(total_sum));
    
    printf("Total sum: %d\n", total_sum);
}