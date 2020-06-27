#include "test.h"

#define N 1600




sint_t test(void)
{
  sint_t i,k;
  real_t j;
  
  trs_pq_t * q = trs_pq_create(N);

  for (i=0;i<N;++i) {
    j = (N % (i+10))/(real_t)N;
    trs_pq_push(j,i,q);
  }

  while (q->size > 0) {
    k = trs_pq_peek(q);
    i = trs_pq_pop(q);
    TESTEQUALS(i,k,PF_SINT_T);
  }

  trs_pq_free(q);

  return 0;
}
