
#define STRESS_TEST_SIZE 25000
#define POOL_SIZE 25

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdatomic.h>

#include "thread_pool.h"

static volatile atomic_ulong big_counter = 0;

void demo_task(void *unused)
{
    int local_counter = 0;
    assert(unused == NULL);

    for (int i = 0; i < 100; i++)
    {
        local_counter++;
        //sleep(1);
    }

    big_counter += local_counter;
}

int main()
{
    int ret = 0;

    thread_pool_t *pool = pool_init(POOL_SIZE);

    for(int i = 0; i < STRESS_TEST_SIZE; i++)
    {
        pool_do(pool, demo_task, NULL);
    }

    pool_flush(pool);

    printf("%ld\n", big_counter);

    ret = pool == NULL ? 1 : 0;

    return ret;
}