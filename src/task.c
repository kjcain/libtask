/**
 * @file task.c
 * @author kyler cain
 * @brief a task object
 * @version 0.1
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "task.h"

/**
 * @brief task object
 * 
 */
struct _task_t 
{

};

/**
 * @brief create a new task in the pool
 * 
 * @param pool 
 * @param priority 
 * @param func 
 * @param params 
 * @return task_t* 
 */
task_t *task_init(
    task_pool_t *pool, 
    task_priority_t priority, 
    task_func_t *func,
    void *params)
{

}

/**
 * @brief create a function with a callback
 * 
 * @param pool 
 * @param priority 
 * @param func 
 * @param params 
 * @param callback 
 * @return task_t* 
 */
task_t *task_init_with_callback(
    task_pool_t *pool,
    task_priority_t priority,
    task_func_t *func,
    void *params,
    task_callback_func_t *callback
)
{

}

/**
 * @brief wait for a task to complete, run a "RUN_ON_WAIT"
 * 
 * @param task 
 * @return void* 
 */
void *task_wait(task_t *task)
{

}

/**
 * @brief get a tasks status
 * 
 * @param task 
 * @return task_status_t 
 */
task_status_t task_status(task_t *task)
{

}

/**
 * @brief get a tasks priority
 * 
 * @param task 
 * @return task_priority_t 
 */
task_priority_t task_priority(task_t *task)
{

}

/**
 * @brief collect task resources
 * 
 * @param task 
 * @return int 
 */
int task_free(task_t *task)
{

}

/* end of task.c */
