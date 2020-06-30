#include "test.h"

#define N 16000

sint_t test(void)
{
  unsigned int seed = 1;
  sint_t i;
  
  sint_t * unsorted = sint_alloc(N);
  sint_t * sorted = sint_alloc(N);

  sint_incset(sorted,0,1,N);
  sint_incset(unsorted,0,1,N);

  sint_shuffle_r(unsorted,N,&seed);

  sint_insertionsort(unsorted,N);

  for (i=0;i<N;++i) {
    TESTEQUALS(unsorted[i],sorted[i],PF_SINT_T);
  }
  return 0;
}
