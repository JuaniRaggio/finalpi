#include <stdio.h>

#undef assert

#define assert(expr) \
  if (expr) { \
  }     \
  else { \
      fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d\n", #expr, __func__, __FILE__, __LINE__); \
   }

