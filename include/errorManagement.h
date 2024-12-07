#ifndef __ERRORMANAGEMENT_H__
#define __ERRORMANAGEMENT_H__

#include <stdio.h>
#include <errno.h>

#define ERRORMSG "Exit with code: %d, function %s, file %s, line %d\n"

#define INVALIDARG 'I'
#define NOERRORSFOUND 0
#define NULLARG 'N'

#undef assert

#define checkErrno(exit_status) \
    if (errno == NOERRORSFOUND) { \
    } \
    else { \
        fprintf(stderr, ERRORMSG, errno, __func__, __FILE__, __LINE__); \
        (exit_status) = errno; \
    }

// if expr == true => sets errno
#define assert(expr, error, returnValue) \
  if (!(expr)) { \
  }     \
  else { \
      fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d\n", #expr, __func__, __FILE__, __LINE__); \
      errno = error; \
      return returnValue; \
   }

#endif

