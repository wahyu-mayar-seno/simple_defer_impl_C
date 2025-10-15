
#ifndef DEFER_H
#define DEFER_H
#ifdef __cplusplus
extern "C" {
#endif
typedef void (*DeferFn)(void *data);
typedef struct {
  DeferFn func;
  void *data;
} Defer_Item;
typedef struct {
  Defer_Item *task;
  int count;
  int cap;
} Defer_Table;
// init defer table
int defer_init(Defer_Table *t, int cap);
// destroy defer table
void defer_destroy(Defer_Table *t);
// push task to defer stack
int defer_push(Defer_Table *t, DeferFn func, void *data);
// call all task in defer table
void defer_exec(Defer_Table *t);
#ifdef DEFER_C_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>

int defer_init(Defer_Table *t, int cap) {
  if (!t) {
    return -1;
  }
  if (cap <= 0) {
    cap = 16;
  }
  t->cap = cap;
  t->count = 0;
  t->task = (Defer_Item *)malloc(sizeof(Defer_Item) * cap);
  if (!t->task) {
    t->cap = 0;
    t->count = 0;
    t->task = NULL;
    return -1;
  }
  return 0;
}

void defer_destroy(Defer_Table *t) {
  if (!t) {
    return;
  }
  free(t->task);
  t->task = NULL;
  t->count = 0;
  t->cap = 0;
}
int defer_push(Defer_Table *t, DeferFn func, void *data) {
  if (t == NULL || func == NULL) {
    return -1;
  }
  if (t->count >= t->cap) {
    int newcap = t->cap * 2;
    Defer_Item *items = (Defer_Item *)malloc(newcap * sizeof(Defer_Item));
    if (!items) {
      return -2;
    }
    t->cap = newcap;
    memcpy(items, t->task, sizeof(Defer_Item) * t->count);
    free(t->task);
    t->task = items;
  }
  t->task[t->count].func = func;
  t->task[t->count].data = data;
  t->count++;

  return 0;
}
void defer_exec(Defer_Table *t) {
  if (!t) {
    return;
  }
  int i = t->count;
  i--;
  while (i >= 0) {
    t->task[i].func(t->task[i].data);
    i--;
  }
  defer_destroy(t);
}
#endif
#ifdef __cplusplus
}
#endif
#endif
