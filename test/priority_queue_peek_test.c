#include "test.h"

#define N 1600




sint_t test(void)
{
  sint_t i,k;
  real_t j;
  
  rs_pq_t * q = rs_pq_create(0,N);

  for (i=0;i<N;++i) {
    j = (N % (i+10))/(real_t)N;
    rs_pq_push(j,i,q);
  }

  while (q->size > 0) {
    k = rs_pq_peek(q);
    i = rs_pq_pop(q);
    TESTEQUALS(i,k,PF_SINT_T);
  }

  rs_pq_free(q);

  return 0;
}
