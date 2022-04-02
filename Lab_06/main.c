#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>
#include <stdint.h>

void swap(uint64_t *i, uint64_t *j) {
   uint64_t temp = *i;
   *i = *j;
   *j = temp;
}

void crescente(uint64_t *v, uint64_t n) {
   for (uint64_t i = 0; i < n; i++) {
      v[i] = i;
   }
}

void decrescente(uint64_t *v, uint64_t n) {
   for (uint64_t i = 0; i < n; i++) {
      v[i] = n - 1 - i;
   }
}

void aleatorio(uint64_t *v, uint64_t n) {
   crescente(v, n);
   srand(time(NULL));
   for (uint64_t i = 0; i < n; i++) {
      swap(&v[i], &v[rand() % n]);
   }
}

void bolha(uint64_t *array, uint64_t n){
    uint64_t i, j;
    uint64_t trocas=0, comp=0;
    for (i = (n - 1); i > 0; i--) {
      for (j = 0; j < i; j++) {
        comp++;
         if (array[j] > array[j + 1]) {
           trocas++;
            swap(&array[j], &array[j + 1]);
         }
      }
   }
}

void insercao(uint64_t *array, uint64_t n){
    for (uint64_t i = 1; i < n; i++) {
      uint64_t tmp = array[i];
      uint64_t j = i - 1;

      while ((j >= 0) && (array[j] > tmp)) {
         array[j + 1] = array[j];
         if(j==0) break;
         j--;
      }
      array[j+1] = tmp;
   }
}

void selecao(uint64_t *array, uint64_t n){
    for (uint64_t i = 0; i < (n - 1); i++) {
      uint64_t menor = i;
      for (uint64_t j = (i + 1); j < n; j++){
         if (array[menor] > array[j]){
            menor = j;
         }
      }
      swap(&array[menor], &array[i]);
   }
}

double get_memory_used_MB()
{
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}

int main()
{
    uint64_t* vetor;

    clock_t start_time, end_time;
    double cpu_time_used, memory_used;
    size_t peakSize;

    int F = 0, O = 0;

    printf("O\tF\tn\tT\tM\n");

    for(uint64_t n = 2000; n <= 2048000; n *= 2){

        vetor = malloc(n * sizeof(uint64_t));

        //----------------------------------------

        //Ordenado
        crescente(vetor,n); O = 1;

        //Desordenado
        //decrescente(vetor,n); O = 2;

        //Permutado
        //aleatorio(vetor,n); O = 3;

        //----------------------------------------

        start_time = clock();

        bolha(vetor,n); int F = 1;

        //insercao(vetor, n); int F = 2;

        //selecao(vetor, n); int F = 3;

        end_time = clock();
        cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        memory_used = get_memory_used_MB();

        //----------------------------------------

        printf("%d\t%d\t%d\t%0.2f\t%0.2f\n", O, F, n, cpu_time_used, memory_used);

        free(vetor);

    }
}
