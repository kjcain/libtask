/**
 * @file task_pool.h
 * @author kyler cain
 * @brief simple task pool
 * @version 0.1
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TASK_POOL_H
#define TASK_POOL_H

#include <stddef.h>

#include "task.h"

/**
 * @brief task pool
 */
typedef struct _task_pool_t task_pool_t;

/**
 * @brief create a new thread pool with a target number of threads
 * 
 * @param thread_count 
 * @return task_pool_t* 
 */
task_pool_t *task_pool_init(size_t thread_count);

/**
 * @brief gets the target size of the pool
 * 
 * @param pool 
 * @return size_t 
 */
size_t task_pool_target_size(task_pool_t *pool);

/**
 * @brief gets the current size of the pool
 * 
 * @param pool 
 * @return size_t 
 */
size_t task_pool_current_size(task_pool_t *pool);

/**
 * @brief get the current number of busy threads
 * 
 * @param pool 
 * @return size_t 
 */
size_t task_pool_running_threads(task_pool_t *pool);

/**
 * @brief set the target size of the pool
 * 
 * @param pool 
 * @param new_thread_count 
 * @return int 
 */
int task_pool_set_target_size(task_pool_t *pool, size_t new_thread_count);

/**
 * @brief add a task to the pool
 * 
 * @param pool 
 * @param task 
 */
void task_pool_add(task_pool_t *pool, task_t *task);

/**
 * @brief free the pool, kill any threads, mark all tasks as killed
 * 
 * @param pool 
 * @return task_pool_t* 
 */
task_pool_t *task_pool_free(task_pool_t *pool);

#endif /* TASK_POOL_H */

/* end of task_pool.h */