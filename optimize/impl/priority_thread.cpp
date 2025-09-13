#include "priority_thread.h"
#include <iostream>

PriorityThread::PriorityThread() {
    // 设置当前进程nice值为最低，设置为最高优先级进程
    nice(-20);

    // 获取当前线程优先级，并保存为老的优先级参数，后续在析构函数中好进行恢复
    pthread_getschedparam(pthread_self(), &policy, &param);
    old_priority = param.sched_priority;

    // 设置当前线程优先级为最高优先级
    param.sched_priority = sched_get_priority_max(policy);
    pthread_setschedparam(pthread_self(), policy, &param);
}

PriorityThread::~PriorityThread() {
    // 析构函数中恢复当前进程和线程的优先级
    // 设置当前nice值为最高，降低优先级
    nice(19);

    // 恢复当前线程优先级为普通优先级
    param.sched_priority = old_priority;
    pthread_setschedparam(pthread_self(), policy, &param);
}

