/**
 * @file task_pool.c
 * @author kyler cain
 * @brief simple task pool
 * @version 0.1
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <assert.h>
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>
#include <stdatomic.h>

#include "thread_pool.h"

#define THREAD_POOL_SCALING_FACTOR 10

/* end of task_pool.c */
