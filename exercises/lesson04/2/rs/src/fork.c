#include "entry.h"
#include "mm.h"
#include "sched.h"

int copy_process(unsigned long fn, unsigned long arg, long pri) {
  preempt_disable();
  struct task_struct *p;

  p = (struct task_struct *)get_free_page(); //set pri based on get_free_page output
  if (!p)
    return 1;

  if (p > (2^32 -1)*2/3) {
    pri = 3;
  } else if (p < (2^32 -1)*2/3 && p >= (2^32 -1)/3) {
    pri = 2;
  } else {
    pri = 1;
  }

  p->priority = pri; //set priority here, highest priority serve first
  p->state = TASK_RUNNING;
  p->counter = p->priority; //set to priority
  p->preempt_count = 1; // disable preemtion untill schedule_tail

  p->cpu_context.x19 = fn;
  p->cpu_context.x20 = arg;
  p->cpu_context.pc = (unsigned long)ret_from_fork;
  p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
  int pid = nr_tasks++;
  task[pid] = p;
  preempt_enable();
  return 0;
}
