#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int dig_sum(uint64_t value){
    int sum = 0;
    while(value > 0){ 
        sum += value %10;
        value /= 10;
    }
    return sum;
}

int main(int argc, char *argv[]){
    int total_sum = 0;
    for(int i=1; i< argc; i++){

        pid_t pid = fork();

        if(pid == 0){  // Child process
            uint64_t num;
            int file_sum = 0;
            FILE *f = fopen(argv[i], "r"); // фаила се отваря за четене
            
            while(fread(&num, sizeof(uint64_t), 1, f)){
                file_sum += dig_sum(num); 
            }

            fclose(f);
            printf("Total sum of file %s is %d\n", argv[i], file_sum);
            exit(file_sum); // завършва със сумата на цифрите
        }else if(pid > 0){ // parrent process
            int wstatus;
            // ако децата са завършили успешно (през exit) тогава се взима кофа
            // с WEXITSTATUS и се добавя към общата сума
            wait(&wstatus);
            //if(WIFEXITED(wstatus)) 
            total_sum += WEXITSTATUS(wstatus);
            
        } else {
            return 1;
        }

        
        // printf("Total sum : %d\n", total_sum);
    }   

    // for(int i = 1; i < argc; i++) {
    //     int wstatus;
    //     wait(&wstatus);
    //     total_sum += WEXITSTATUS(wstatus);
    // }
    printf("Total sum : %d\n", total_sum);
}