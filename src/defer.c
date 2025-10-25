#include "defer.h"
#include <stdio.h>
#include <stdlib.h>
void defer_push(Defer_Table *d, DeferFn fn, void *data) {
  if (!d) {
    return;
  }
  if (d->cap <= d->count) {
    fprintf(stderr, "no slot any more\n");
    exit(-1);
    return;
  }
  d->task[d->count].func = fn;
  d->task[d->count].data = data;
  d->count++;
}
void defer_exec(Defer_Table *d) {
  if (!d) {
    fprintf(stderr, "invalid pointer to table\n");
  }
  if (d->count < 1) {
    fprintf(stderr, "no task to exec\n");
    exit(-1);
    return;
  }
  int size = d->count;
  while (size > 0) {
    size--;
    d->task[size].func(d->task[size].data);
  }
  d->count = 0;
}
