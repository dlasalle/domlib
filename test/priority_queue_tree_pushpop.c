#include "test.h"

#define M 12000UL
#define N 16000UL
#define L 2500UL




sint_t test(void)
{
  size_t i;
  real_t j;

  trs_pq_t * q = trs_pq_create(L);

  for (i=0;i<L;++i) {
    trs_pq_push(i/((real_t)M),M+i,q);
  }

  TESTEQUALS(L,q->size,PF_SIZE_T);

  j = q->elements[0].key;
  trs_pq_pop(q);
  while (q->size > 0) {
    TESTLESSTHANOREQUAL(q->elements[0].key,j,PF_REAL_T);
    j = q->elements[0].key;
    trs_pq_pop(q);
  }

  TESTEQUALS(0UL,q->size,PF_SIZE_T);

  trs_pq_free(q);

  return 0;
}
