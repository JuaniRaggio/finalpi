#include <stdio.h>
#include <errno.h>

#define NOERRORSFOUND 0

#undef assert

#define assert(expr, error, returnValue) \
  if (expr) { \
  }     \
  else { \
      fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d\n", #expr, __func__, __FILE__, __LINE__); \
      errno = error; \
      return returnValue; \
   }

