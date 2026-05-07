#include <cstdio>
#include <omp.h>
int main() {
  printf("max threds = %d\n", omp_get_max_threads());

#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int total = omp_get_num_threads();
    printf("hellow from thread %d / %d\n", tid, total);
  }
  return 0;
}
