#include <stdio.h>
#include <errno.h>

#define ERRORMSG "Exit with code: %d, function %s, file %s, line %d\n"

#define NOERRORSFOUND 0
#define NULLARG 'N'

#undef assert

#define checkErrno() \
    if (errno != NOERRORSFOUND) { \
        fprintf(stderr, ERRORMSG, errno, __func__, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    }

#define assert(expr, error, returnValue) \
  if (expr) { \
  }     \
  else { \
      fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d\n", #expr, __func__, __FILE__, __LINE__); \
      errno = error; \
      return returnValue; \
   }

