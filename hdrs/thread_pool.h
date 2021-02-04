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
 * @note auto scaling will increase pool size in an effort to keep task backlog smaller than the number of threads available
 * @note scaling factor is ((max - min) / 10) + 1
 * 
 * @param min_size 
 * @return thread_pool_t* 
 */
thread_pool_t *pool_init(size_t min_size, size_t max_size);

/**
 * @brief release all resources associated with the threadpool
 * 
 * @param pool 
 */
void pool_free(thread_pool_t *pool);

/**
 * @brief wait for all units of work to terminate
 * 
 * @param pool 
 */
void pool_wait(thread_pool_t *pool);

/**
 * @brief perform a unit of work on the thread pool
 * 
 * @param pool 
 * @param func 
 * @param params 
 */
void pool_do(thread_pool_t *pool, work_func_t *func, void *params);

/**
 * @brief gets the number of allocatee threads in the pool
 * 
 * @param pool 
 * @return size_t 
 */
size_t pool_get_size(thread_pool_t *pool);

/**
 * @brief get the number of threads that are currently not running in the pool
 * 
 * @param pool 
 * @return size_t 
 */
size_t pool_get_free_threads(thread_pool_t *pool);

/**
 * @brief get the number of threads that are currently working in the pool
 * 
 * @param pool 
 * @return size_t 
 */
size_t pool_get_busy_threads(thread_pool_t *pool);

/**
 * @brief get the number of work units waiting to execute
 * 
 * @param pool 
 * @return size_t 
 */
size_t pool_get_backlog(thread_pool_t *pool);

/**
 * @brief print statistics for the pool
 * 
 * @param pool 
 */
void pool_print_stats(thread_pool_t *pool);

#endif /* THREAD_POOL_H */

/* end of thread_pool.h */