
#include <stdio.h>
#include <stdlib.h>

#include "defer.h"
size_t malloc_count = 0;
size_t free_count = 0;
void *dmalloc(size_t s) {
  malloc_count++;
  return malloc(s);
}
void dfree(void *fj) {
  free_count++;
  printf("free %zu\n", free_count);
  free(fj);
}
void ff(void *a) { printf("aha\n"); }
int main(void) {
  Defer_Item _task[10];
  Defer_Table t = {.task = _task, .count = 0, .cap = 10};
  void *a = dmalloc(256);
  defer_push(&t, dfree, a);
  void *b = dmalloc(256);
  defer_push(&t, dfree, b);
  void *c = dmalloc(256);
  defer_push(&t, dfree, c);
  void *d = dmalloc(256);
  defer_push(&t, dfree, d);
  void *e = dmalloc(256);
  defer_push(&t, dfree, e);
  defer_push(&t, ff, 0);
  defer_push(&t, ff, 0);
  defer_push(&t, ff, 0);
  defer_push(&t, ff, 0);
  defer_push(&t, ff, 0);
  // defer_push(&t, ff, 0);// this call will exit because task is full

  defer_exec(&t);
  printf("malloc : %zu\n free : %zu\n", malloc_count, free_count);

  return 0;
}
