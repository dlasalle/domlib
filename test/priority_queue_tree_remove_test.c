#include "test.h"

#define K 120500UL
#define L 121024UL
#define M 120000UL
#define N 160000UL




sint_t test(void)
{
  size_t i;
  real_t j;
  
  trs_pq_t * q = trs_pq_create(N-M);

  for (i=M;i<N;++i) {
    trs_pq_push(i/((real_t)N),i,q);
  }

  TESTEQUALS(N-M,q->size,PF_SIZE_T);

  for (i=K;i<L;++i) {
    trs_pq_remove(i,q);
  }

  TESTEQUALS(N-M-(L-K),q->size,PF_SIZE_T);

  j = q->elements[0].key;
  trs_pq_pop(q);
  while (q->size > 0) {
    TESTLESSTHANOREQUAL(q->elements[0].key,j,PF_REAL_T);
    j = q->elements[0].key;
    trs_pq_pop(q); 
  }

  for (i=M;i<N;++i) {
    TESTEQUALS(trs_pq_contains(i,q),0,"%d");
  }

  trs_pq_free(q);

  return 0;
}
