#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

uint64_t dig_sum(uint64_t value){
    unsigned long long sum = 0;
    while(value > 0){ 
        sum += value %10;
        value /= 10;
    }
    return sum;
}

void *sum_thread(void *args){
    char *file = (char*)args;
    printf("STARTED THREAD WITH INDEX: %s\n", (char*)args);
    

    unsigned long long file_sum = 0;

    int fd = open(file, O_RDONLY);

    uint64_t num = 0;
    ssize_t read_bytes;
    
    while((read_bytes = read(fd, &num, sizeof(uint64_t))) > 0){
        file_sum += dig_sum(num);
    }

    close(fd);

    printf("%s - %lld \n", file, file_sum);

    unsigned long long *result = malloc(sizeof(int));
    *result = file_sum;
    return result;                                         

}

int main(int argc, char *argv[]){
    int total_sum = 0;

    pthread_t thread[argc-1];

    for(int i = 1; i < argc ; i++){
        if((pthread_create(&thread[i], NULL, sum_thread, argv + i)) < 0){
            perror("Error creating thread");
            exit(-1);
        } else {
            printf("Successfully created\n");
        }
    }

    for(int i = 1; i < argc; i++){
        unsigned long long *thread_res;
        pthread_join(thread[i],(void **)&thread_res);
        total_sum += *thread_res;
        free(thread_res);
    }

    printf("Total sum %d \n" , total_sum);
}