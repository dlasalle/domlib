#include "test.h"

#define N 1234567
#define NTHREADS 11 


static void myfunc(void * ptr)
{
  int x;

  x = *((int*)ptr);

  x += 1;

  *(int*)(ptr) = x;
}


sint_t test(void)
{
  int t;
  int a[N];
  int r[NTHREADS];

  #pragma omp parallel num_threads(NTHREADS)
  {
    int i, j;

    size_t myid = omp_get_thread_num();

    r[myid] = 0;

    for (j=0;j<__DLTHREAD_POOL_TS_TERM;++j) {
      dlthread_pool_init(NTHREADS);
      dlthread_pool_set_schedule(j);

      #pragma omp for
      for (i=0;i<N;++i) {
        a[i] = i;
        dlthread_pool_add(&myfunc,a+i);
      }

      dlthread_pool_finalize();

      #pragma omp for
      for (i=0;i<N;++i) {
        if (r[myid] == 0) {
          OMPTESTTRUE(a[i] == i+1,r[myid]);
        }
      }
    }
  }

  for (t=0;t<NTHREADS;++t) {
    TESTEQUALS(r[t],0,"%d");
  }
  return 0;
}
