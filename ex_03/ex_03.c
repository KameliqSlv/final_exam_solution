#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct ROW{
    char row[100];
    int row_num;        // number of rows
    int *value;         // array of value 
    int num_values;     // number of values in array
    double average;     // average
}ROW;

void *average(void *args){      // функция която изпълнява отделни нишки
                                // за изчисляване на avrg
    ROW *row = (ROW *)args;

    double sum = 0;
    for(int i = 0; i < row->num_values; i++){
        sum += row->value[i];
    }

    row->average = sum / row->num_values;

    pthread_exit(NULL);
}

int main(){
    int N , M;
    printf("Number of row and counter of number : ");
    scanf("%d %d", &N, &M);  // причита броя на редовете N и броя 
                                    // на числата във всеки ред (М)

    // Задекяме памет за данните за редовете нишки
    ROW *row_data = malloc(N * sizeof(ROW));
    pthread_t *thread = malloc(N * sizeof(pthread_t));

    for(int i = 0; i < N; i++){
        printf("Enter a string and number of row : ");
        //Четем символния низ ROW и номер на реда
        scanf("%s %d", row_data[i].row, &row_data[i].row_num);

        //row_data[i].row_num = N;

        // Заделяме памет за масива
        row_data[i].value = malloc(M * sizeof(int));
        row_data[i].num_values = M;

        for(int j = 0; j < M; j++){
            row_data[i].value[j] = rand() % 20;
            //scanf("%d", &row_data[i].value[j]);
        }

        // създаваме нова нишка
        pthread_create(&thread[i], NULL, average, &row_data[i]);
    }

    // Изчакваме завършването на нишките
    for (int i = 0; i < N; i++) {
        pthread_join(thread[i], NULL);
    }

    char output_file[100];
    printf("FILE : ");
    scanf("%s", output_file);

    FILE *f = fopen(output_file, "w+");


    for(int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            fprintf(f, "%d ", row_data[i].value[j]);
        
        }
        fprintf(f, "\n");
    }

    fprintf(f, "\n");

    
    for(int i = 0; i < N; i++) {
        fprintf(f, "%s %d %.3lf \n", row_data[i].row ,row_data[i].row_num, row_data[i].average);
    }

    fprintf(f, "\n");

    for(int i = 0; i < N; i++) {
        fprintf(f, "Average %.2lf \n",  row_data[i].average);
    }

    fclose(f);

    for (int i = 0; i< N; i++) {
        free(row_data[i].value);
    }

    free(row_data);
    free(thread);

    return 0;
}