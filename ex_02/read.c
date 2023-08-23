#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "r");

    uint64_t num;
    size_t count = 0;

    while(fread(&num, sizeof(int), 1, f) == 1){
        printf("Number %zu : %lu \n", count, num);
        count++;
    }

    fclose(f);
    return 0;
}