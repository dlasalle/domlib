#include "test.h"

#define K 120500UL
#define L 121024UL
#define M 120000UL
#define N 160000UL




sint_t test(void)
{
  size_t i;
  
  trs_pq_t * q = trs_pq_create(N-M);

  for (i=M;i<N;++i) {
    trs_pq_push(i/((real_t)N),i,q);
  }

  TESTEQUALS(N-M,q->size,PF_SIZE_T);

  trs_pq_clear(q);

  TESTEQUALS((size_t)0,q->size,PF_SIZE_T);

  trs_pq_free(q);

  return 0;
}
