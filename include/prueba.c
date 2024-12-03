#include <errno.h>
#include "errorManagement.h"

int main() {
    errno = 1;
    assert(1, ENOMEM, 2);
    return 0;
}

