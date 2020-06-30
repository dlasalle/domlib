#include "test.h"

#define M 500UL
#define N 5000UL




sint_t test(void) 
{
  sint_buffer_t * const buffer = sint_buffer_create(M);

  TESTEQUALS((size_t)0,buffer->size,PF_SIZE_T);

  buffer->elements = sint_realloc(buffer->elements,N);
  buffer->maxsize = N;
  buffer->size = N;
  sint_incset(buffer->elements,0, 1, N);

  sint_buffer_clear(buffer);

  TESTEQUALS((size_t)0,buffer->size,PF_SIZE_T);
  TESTEQUALS((size_t)N,buffer->maxsize,PF_SIZE_T);

  sint_incset(buffer->elements,0,1,M);
  buffer->size = M;

  sint_buffer_reset(buffer);

  TESTEQUALS((size_t)0,buffer->size,PF_SIZE_T);
  TESTEQUALS((size_t)M,buffer->maxsize,PF_SIZE_T);

  sint_buffer_free(buffer);

  return 0;
}
