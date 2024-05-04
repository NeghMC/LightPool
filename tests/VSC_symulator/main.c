#include "lightPool.h"
#include <stdlib.h>
#include <time.h>

// library declarations
#define BUFFERS_COUNT (10)
#define BUFFER_SIZE (10)

pool_t pool;
char buffer[BUFFER_SIZE * BUFFERS_COUNT];

// function is shuffling 'randomOrder' array.
void randomizeOrder();
uint8_t randomOrder[BUFFERS_COUNT]; // this array is used to determined the order of returned buffers.

int main(void)
{
    // test initialisation
    srand(time(NULL));
    for(int i = 0; i < BUFFERS_COUNT; ++i)
    {
        randomOrder[i] = i;
    }
    const int TEST_ITERATIONS = 7;

    // pool initialisation
    pool_init(&pool, buffer, BUFFERS_COUNT, BUFFER_SIZE);

    // run test 7 times (arbitrary number)
    void * tab[BUFFERS_COUNT];
    for(int i = 0; i < TEST_ITERATIONS; ++i)
    {
        // test if all the pools can be allocated
        for(int i = 0; i < BUFFERS_COUNT; ++i)
        {
            tab[i] = pool_allocate(&pool);
            if(tab[i] == NULL)
            {
                goto failed;
            }
        }
        // test if allocating more pools returns error
        void *dummy = pool_allocate(&pool);
        if(dummy != NULL)
        {
            goto failed;
        }

        // return all the pools in random order
        randomizeOrder();
        for(int i = 0; i < BUFFERS_COUNT; ++i)
        {
            bool result = pool_free(&pool, tab[randomOrder[i]]);
            if(result == false)
            {
                goto failed;
            }
        }

        // test if freeing incorrect address returns error
        void * dummyAddress = (&pool) - 1;
        bool result = pool_free(&pool, dummyAddress);
        if(result != false)
        {
            goto failed;
        }
    }

    return 0;

failed:
    return 1;
}

void randomizeOrder()
{
    uint8_t toSwap1 = rand() % BUFFERS_COUNT;
    for(int i = 0; i < BUFFERS_COUNT; ++i)
    {
        uint8_t toSwap2 = rand() % BUFFERS_COUNT;
        uint8_t temp = randomOrder[toSwap1];
        randomOrder[toSwap1] = randomOrder[toSwap2];
        randomOrder[toSwap2] = temp;
        toSwap1 = toSwap2;
    }
}