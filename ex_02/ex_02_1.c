#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "w+");

    int N = atoi(argv[2]);

    //fwrite((*(uitn64_t*)argv[1]), 1, sizeof(uint64_t), f);
    srand(time(NULL));
    for(size_t i = 0; i < N; i++){
        uint64_t num = (uint64_t)rand();
        fwrite(&num, sizeof(uint64_t), 1, f);
    }

    fclose(f);

    //printf("Successfully wrote %d numbers to %c\n", N, f);

    
    return 0;
}