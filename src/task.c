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

#include <assert.h>
#include <stdlib.h>
#include <semaphore.h> 

#include "task_pool.h"

#include "task.h"


/**
 * @brief task object
 * 
 */
struct _task_t 
{
    sem_t completion_sem;
    task_pool_t *pool;
    task_status_t status;
    task_priority_t priority;
    task_func_t *func;
    void *params;
    void *result;
    task_callback_func_t *callback;
};

/**
 * @brief build a new task
 * @note requires: non-null pool and task
 * @note ensures: task is either successfully built and added to pool, or null is returned
 * 
 * @param pool 
 * @param status 
 * @param priority 
 * @param func 
 * @param params 
 * @param callback 
 * @return task_t*
 */
task_t *_task_build(
    task_pool_t *pool, 
    task_status_t status, 
    task_priority_t priority, 
    task_func_t *func, 
    void* params, 
    task_callback_func_t *callback)
{
    assert(pool != NULL && "pool given is null");
    assert(func != NULL && "function given is null");

    task_t *task = malloc(sizeof(task_t));
    assert(task != NULL && "unable to allocate memory for task");

    /* blocked by default, wait calls sem_post, only time it's used */
    sem_init(&(task->completion_sem), 1, 0);
    
    task->pool = pool;
    task->priority = priority;
    task->status = status;
    task->func = func;
    task->params = params;
    task->callback = callback;

    task->result = NULL;

    task_pool_add(pool, task);

    return task;
}

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
    return _task_build(
        pool,
        TASK_STATUS_WAITING,
        priority, 
        func, 
        params,
        NULL
    );
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
    return _task_build(
        pool,
        TASK_STATUS_WAITING,
        priority, 
        func, 
        params,
        callback
    );
}

/**
 * @brief executes a task
 * 
 * @param task 
 */
void task_execute(task_t *task)
{
    task->status = TASK_STATUS_RUNNING;

    task->result = task->func(task->params);

    task->status = TASK_STATUS_FINISHED;
    
    if(task->callback == NULL)
    {
        task->callback(task);
    }

    /* send the completion signal */
    sem_post(&(task->completion_sem));
}

/**
 * @brief wait for a task to complete
 * 
 * @param task 
 * @return void* 
 */
void *task_wait(task_t *task)
{
    /* wait and immediately repost */
    /* only waiting for the completion signal before continuing */
    sem_wait(&(task->completion_sem));
    sem_post(&(task->completion_sem));

    return task->result;
}

/**
 * @brief get a tasks status
 * 
 * @param task 
 * @return task_status_t 
 */
task_status_t task_status(task_t *task)
{
    return task->status;
}

/**
 * @brief get a tasks priority
 * 
 * @param task 
 * @return task_priority_t 
 */
task_priority_t task_priority(task_t *task)
{
    return task->priority;
}

/**
 * @brief collect task resources
 * @note could be used as a callback for fire-and-forget tasks
 * 
 * @param task 
 */
void task_free(task_t *task)
{
    /* wait for the task to finish */
    task_wait(task);

    sem_destroy(&(task->completion_sem));
    free(task->params);
    free(task);
    task = NULL;
}

/* end of task.c */
