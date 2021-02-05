/**
 * @file thread_pool.h
 * @author kyler cain
 * @brief simple thread pool
 * @version 0.1
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stddef.h>

/**
 * @brief thread pool
 */
typedef struct _thread_pool_t thread_pool_t;

/**
 * @brief unit of work
 * 
 * @param params 
 * @return typedef 
 */
typedef void work_func_t(void *params);

/**
 * @brief create a new pool
 * 
 * @param size 
 * @return thread_pool_t* 
 */
thread_pool_t *pool_init(size_t size);

/**
 * @brief wait for all units of work to terminate and free the pool
 * 
 * @param pool 
 */
void pool_flush(thread_pool_t *pool);

/**
 * @brief perform a unit of work on the thread pool
 * 
 * @param pool 
 * @param func 
 * @param params 
 */
void pool_do(thread_pool_t *pool, work_func_t *func, void *params);

#endif /* THREAD_POOL_H */

/* end of thread_pool.h */