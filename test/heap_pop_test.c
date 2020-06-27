#include "test.h"

#define N 160000
#define M 137

sint_t test(void)
{
  sint_t i,j,k;
  real_t key;
  kv_t pair;

  sint_heap_t * maxh = sint_heap_create(N);
  kv_heap_t * kvh = kv_heap_create(N);

  /* sint_t */
  for (i=1;(i<<1)<N;i<<=1) {
    j = (i<<1)-1;
    sint_incset(maxh->elements+i-1,N-j,1,i);
  }
  sint_incset(maxh->elements+i-1,0,1,N-i+1);

  maxh->size = N;

  for (i=0;i<N;++i) {
    j = sint_heap_pop(maxh);
    TESTEQUALS(N-i-1,j,PF_SINT_T);
  }

  TESTEQUALS(maxh->size,0UL,PF_SIZE_T);

  sint_heap_free(maxh);


  /* kv_t */
  for (i=1;(i<<1)<N;i<<=1) {
    j = (i<<1)-1;
    for (k=0;k<i;++k) {
      pair.key = N-j + k;
      pair.value = i;
      kvh->elements[i-1+k] = pair;
    }
  }
  kvh->size = N;

  key = N;
  for (i=0;i<N;++i) {
    pair = kv_heap_pop(kvh);
    j = pair.value;

    TESTLESSTHANOREQUAL(pair.key,key,PF_REAL_T);
    key = pair.key;
  }

  TESTEQUALS(maxh->size,0UL,PF_SIZE_T);

  kv_heap_free(kvh);


  return 0;
}
