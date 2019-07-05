#include "mm.h"
#include "entry.h"
#include "sched.h"

int int main(int argc, char const *argv[]) {

  struct task_struct *p;
  p = (struct task_struct *)get_free_page();

  return p;
}
