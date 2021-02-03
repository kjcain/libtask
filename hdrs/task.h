/**
 * @file task.h
 * @author kyler cain
 * @brief a task object
 * @version 0.1
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TASK_H
#define TASK_H

#include <stddef.h>

#include "task_pool.h"

/**
 * @brief task object
 * 
 */
typedef struct _task_t task_t;

/**
 * @brief prioritization of the tasks
 * 
 */
typedef enum _task_priority_t
{
    TASK_PRIORITY_INDEPENDENT, /*<! spins up new thread to run on */
    TASK_PRIORITY_ASYNC /*<! normal task on thread pool */
}
task_priority_t;

/**
 * @brief status of the task
 * 
 */
typedef enum _task_status_t
{
    TASK_STATUS_WAITING,
    TASK_STATUS_RUNNING,
    TASK_STATUS_FINISHED,
    TASK_STATUS_FAILED,
    TASK_STATUS_KILLED
}
task_status_t;

/**
 * @brief function to execute
 * 
 * @param args 
 * @return typedef* 
 */
typedef void* task_func_t(void *args);

/**
 * @brief function to call back after completion of a task
 * 
 * @param task_t
 * @return typedef 
 */
typedef void task_callback_func_t(task_t *task);


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
    void *params);

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
);

/**
 * @brief wait for a task to complete
 * 
 * @param task 
 * @return void* 
 */
void *task_wait(task_t *task);

/**
 * @brief get a tasks status
 * 
 * @param task 
 * @return task_status_t 
 */
task_status_t task_status(task_t *task);

/**
 * @brief get a tasks priority
 * 
 * @param task 
 * @return task_priority_t 
 */
task_priority_t task_priority(task_t *task);

/**
 * @brief collect task resources
 * 
 * @param task 
 */
void task_free(task_t *task);

#endif /* TASK_H */

/* end of task.h */
