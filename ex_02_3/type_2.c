#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

// функция която съхранява името на файла и сумата от цифрите
typedef struct File{
    char *file;
    int file_sum;
}File;

int digit_sum(uint64_t num){
    int sum = 0;
    while(num > 0){
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

void *thread_file(void *args){
    File *file = (File*)args;
    
    FILE *f = fopen(file->file, "r");

    uint64_t num;
    file->file_sum = 0;

    while(fread(&num, sizeof(uint64_t), 1, f)){
        file->file_sum += digit_sum(num);
    }

    fclose(f);
    printf("%s - %d\n", file->file, file->file_sum);
    pthread_exit(NULL); // изход от текущата нишка

}

int main(int argc, char *argv[]){
    int total_sum = 0;
    pthread_t thread[argc-1];
    File file[argc -1];

    for(int i = 1; i< argc; i++){
        file[i].file = argv[i];
        file[i].file_sum = 0;

        pthread_create(&thread[i], NULL, thread_file, &file[i]);
    }

    for(int i = 1; i< argc; i++){
        pthread_join(thread[i], NULL);
        total_sum += file[i].file_sum;
    
    }

    printf("Total sum : %d \n", total_sum);

}