#include "test.h"

#define M 123
#define NTHREADS 21


static void myfunc(void * ptr)
{
  int * r;
  sint_t i,j, n;
  sint_t counts[M];
  sint_t prefix[M+1];
  sint_t * gprefix;
  sint_t * array;

  size_t const myid = dlthread_get_id(DLTHREAD_COMM_ROOT);
  size_t const nthreads = dlthread_get_nthreads(DLTHREAD_COMM_ROOT);

  n = ((nthreads+1)*nthreads*M)/2;

  r = (int*)ptr;
  r[myid] = 0;

  gprefix = dlthread_get_shmem(sizeof(sint_t)*((M+1)+n),DLTHREAD_COMM_ROOT);
  array = gprefix+M+1;

  if (myid == 0) {
    sint_set(array,-1,n);
  }

  sint_set(counts,myid+1,M);
  sint_copy(prefix,counts,M);
  prefix[M] = 0;

  sint_dlthread_prefixsum(prefix,M+1,gprefix,DLTHREAD_COMM_ROOT);

  OMPTESTTRUE(prefix[M] <= n,r[myid]);
  OMPTESTEQUALS(gprefix[M],n,PF_SINT_T,r[myid]);

  /* fill array with identifiable values */
  for (i=0;i<M;++i) {
    for (j=prefix[i];j<prefix[i]+counts[i];++j) {
      array[j] = myid+(i*nthreads);
    }
  }

  dlthread_barrier(DLTHREAD_COMM_ROOT);

  /* verify array integrity */
  if (myid == 0) {
    for (i=0;i<M;++i) {
      for (j=gprefix[i];j<gprefix[i+1];++j) {
        OMPTESTTRUE(array[j] >= (sint_t)nthreads*i,r[myid]);
        OMPTESTTRUE(array[j] < (sint_t)nthreads*(i+1),r[myid]);
        if (r[myid] != 0) {
          goto END;
        }
      }
    }
  }

  END:

  dlthread_free_shmem(gprefix,DLTHREAD_COMM_ROOT);
}


sint_t test(void)
{
  int x, n, r[NTHREADS];

  for (n=1;n<NTHREADS;++n) {
    dlthread_launch(n,&myfunc,r);
    if ((x = sint_sum(r,n)) != 0) {
      return x;
    } 
  }

  return 0;
}
