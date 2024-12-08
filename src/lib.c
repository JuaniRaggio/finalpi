#include "lib.h"

void freeList(void * list, size_t sizeTillNext) {
    if (list == NULL) {
        return;
    }
    freeList((void *)((char *)list + sizeTillNext), sizeTillNext);
    free(list);
}

// A utility function to get the maximum 
// value in arr[]
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] 
// according to the digit represented by exp
void countSort(int arr[], int n, int exp) {
    int output[n]; // Output array
    int count[10] = {0}; // Initialize count array as 0

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now 
    // contains actual position of this digit
    // in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], 
    // so that arr[] now contains sorted 
    // numbers according to current digit
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to sort arr[] of size 
// n using Radix Sort
void radixSort(int arr[], int n) {
  
    // Find the maximum number to know 
    // the number of digits
    int m = getMax(arr, n); 

    // Do counting sort for every digit
    // exp is 10^i where i is the current 
    // digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void trimWhitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}










int max(int a, int b) {
    return a > b ? a:b;
}

int myStrcpy(char * target, size_t targetDim, const char * source, char * separators) {
    int i = 0;
    for (; source[i] != '\0' && i < targetDim - 1; ++i) {
        if (strchr(separators, source[i]) != NULL) {
            target[i] = '\0';
            return i;
        }
        target[i] = source[i];
    }
    target[i] = '\0';
    return i;
}

unsigned int getLine(char s[], unsigned int maxLength) {
    int c;
    unsigned int n=0;
    while ( (c=getchar()) != EOF && c != '\n') {
        if (n < maxLength)
            s[n++] = c;
    }
    s[n] = 0;
    return n;
}

void reCalloc(void ** ptr, size_t sizePtr, size_t oldSize, size_t newSize) {
    if (oldSize >= newSize) return;
    void * tmp = realloc(*ptr, sizePtr * newSize);
    errno = NOERRORSFOUND;
    assert(tmp == NULL, ENOMEM,);
    *ptr = tmp;
    memset((char *)*ptr + oldSize * sizePtr, 0, (newSize - oldSize) * sizePtr);
    return;
}

