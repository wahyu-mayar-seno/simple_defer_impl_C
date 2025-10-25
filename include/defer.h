
#ifndef DEFER_H
#define DEFER_H

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
// push task into defer table
void defer_push(Defer_Table *t, DeferFn func, void *data);
// call all task in defer table
void defer_exec(Defer_Table *t);

#endif
