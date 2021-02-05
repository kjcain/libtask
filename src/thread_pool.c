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
#include <stdbool.h>
#include <stdlib.h>

#include "thread_pool.h"

#define PTHREAD_SHARED 0

/**
 * @brief standard unit of work
 */
typedef struct _work_t
{
    work_func_t *func;
    void *params;

    struct _work_t *next;
}
work_t;

/**
 * @brief thread pool
 */
struct _thread_pool_t 
{
    size_t size;

    volatile atomic_int live_threads;
    volatile atomic_int busy_threads;
    volatile atomic_int work_backlog;

    sem_t all_dead;

    sem_t work_signal;
    sem_t work_lock;
    work_t *work;

    pthread_t threads[];
};

work_t *_pool_get_task(thread_pool_t *pool)
{
    work_t *work;

    sem_wait(&(pool->work_signal));
    sem_wait(&(pool->work_lock));

    work = pool->work;

    if(work != NULL)
    {
        pool->work = pool->work->next;
        pool->work_backlog--;
    }

    sem_post(&(pool->work_lock));

    return work;
}

void _pool_add_task(thread_pool_t *pool, work_func_t *func, void *params)
{
    work_t *work = malloc(sizeof(work_t));
    work->func = func;
    work->params = params;
    work->next = NULL;

    sem_wait(&(pool->work_lock));

    if(pool->work == NULL)
    {
        pool->work = work;
    }
    else
    {
        work_t *work_node = pool->work;
        while(work_node->next != NULL)
        {
            work_node = work_node->next;
        }

        work_node->next = work;
    }

    pool->work_backlog++;

    sem_post(&(pool->work_lock));
    sem_post(&(pool->work_signal));
}

void *_pool_kernel(void *pool_generic)
{
    thread_pool_t *pool = (thread_pool_t *) pool_generic;

    bool flush = false;
    pool->live_threads++;

    while(!flush)
    {
        work_t *work = _pool_get_task(pool);

        if(work != NULL)
        {
             pool->busy_threads++;

            work->func(work->params);

            free(work);

            pool->busy_threads--;
        }
        else
        {
            flush = true;
        }
    }
    pool->live_threads--;

    if(pool->live_threads <= 0)
    {
        sem_post(&(pool->all_dead));
    }

    return NULL;
}

/**
 * @brief create a new pool
 * 
 * @param size 
 * @return thread_pool_t* 
 */
thread_pool_t *pool_init(size_t size)
{
    assert(size > 0);

    size_t pool_size = sizeof(thread_pool_t) + (sizeof(pthread_t) * size);
    thread_pool_t *pool = malloc(pool_size);
    assert(pool != NULL && "unable to allocate pool");

    pool->size = size;
    
    pool->live_threads = 0;
    pool->busy_threads = 0;
    pool->work_backlog = 0;

    sem_init(&(pool->all_dead), PTHREAD_SHARED, 0);
    
    sem_init(&(pool->work_signal), PTHREAD_SHARED, 0);
    sem_init(&(pool->work_lock), PTHREAD_SHARED, 1);

    pool->work = NULL;

    for(size_t thread = 0; thread < size; thread++)
    {
        pthread_create(&(pool->threads[thread]), NULL, _pool_kernel, pool);
    }

    return pool;
}

/**
 * @brief wait for all units of work to terminate and free the pool
 * 
 * @param pool 
 */
void pool_flush(thread_pool_t *pool)
{
    for(size_t count = 0; count < pool->size; count++)
    {
        sem_post(&(pool->work_signal));
    }
    
    sem_wait(&(pool->all_dead));

    for(size_t count = 0; count < pool->size; count++)
    {
        pthread_join(pool->threads[count], NULL);
    }

    free(pool);
    pool = NULL;
}

/**
 * @brief perform a unit of work on the thread pool
 * 
 * @param pool 
 * @param func 
 * @param params 
 */
void pool_do(thread_pool_t *pool, work_func_t *func, void *params)
{
    _pool_add_task(pool, func, params);
}

/* end of task_pool.c */
