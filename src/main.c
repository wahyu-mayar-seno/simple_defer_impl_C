
#include <stdio.h>
#include <stdlib.h>

#include "defer.h"
size_t malloc_count = 0;
size_t free_count = 0;
void *dmalloc(size_t s) {
  malloc_count++;
  return malloc(s);
}
void dfree(void *fj) { free(fj); }
int main(void) {
  Defer_Table t;
  defer_init(&t, 1024);
  void *a = dmalloc(256);
  void *b = dmalloc(256);
  void *c = dmalloc(256);
  void *d = dmalloc(256);
  defer_push(&t, dfree, a);
  defer_push(&t, dfree, b);
  defer_push(&t, dfree, c);
  defer_push(&t, dfree, d);
  defer_exec(&t);
  printf("malloc : %zu\n free : %zu\n", malloc_count, free_count);

  return 0;
}
