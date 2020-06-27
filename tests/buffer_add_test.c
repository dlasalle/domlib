#include "test.h"

static const size_t M = 500;
static const size_t N = 5000;



sint_t test(void) 
{
  size_t i;

  sint_buffer_t * buffer = sint_buffer_create(M);

  TESTEQUALS((size_t)0,buffer->size,PF_SIZE_T);

  for (i=0;i<N;++i) {
    sint_buffer_add((sint_t)i,buffer);
  }

  TESTEQUALS(N,buffer->size,PF_SIZE_T);

  for (i=0;i<N;++i) {
    TESTEQUALS((sint_t)i,buffer->elements[i],PF_SINT_T);
  }

  sint_buffer_free(buffer);

  return 0;
}
