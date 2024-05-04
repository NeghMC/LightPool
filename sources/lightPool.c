/*
 * LightPool
 * 
 * Author: Grzegorz Świstak (NeghMC)
 * 
 * DISCLAIMER: This software is provided 'as-is', without any express
 * or implied warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "lightPool.h"

#define POOL_NONE ((uint8_t)0xff)
#define POOL_MAX ((uint8_t)0x254)

/// Initializes the pool
/// @param p pointer to an instance of pool_t
/// @param memory linear buffer for all elements in size of 'count' * 'size' bytes
/// @param buffersCount number of elements in the pool
/// @param bufferSize size of an element in the pool
/// @note element size must be greater than actual size by POOL_OVERHEAD
bool pool_init(pool_t *p, void *memory, uint8_t buffersCount, size_t bufferSize)
{
    if(buffersCount > POOL_MAX)
    {
        return false;
    }

    p->memory = (uint8_t *)memory;
    p->count = buffersCount;
    p->size = bufferSize;
    p->topIndex = 0;
    
    // first byte contains number of the next buffer
    for(uint8_t i = 0; i < (buffersCount - 1); ++i)
    {
        p->memory[i * bufferSize] = i + 1;
    }
    p->memory[(buffersCount - 1) * bufferSize] = POOL_NONE;

    return true;
}

/// Checks if pool is empty
/// @param p pointer to an instance of pool_t
/// @return true if pool is empty, false otherwise
bool pool_isEmpty(pool_t *p)
{
    return p->topIndex == POOL_NONE;
}

/// Gets first empty buffer from the pool
/// @param p pointer to an instance of pool_t
/// @return pointer to the allocated element
void * pool_allocate(pool_t *p)
{
    if(pool_isEmpty(p))
        return NULL;
    
    uint8_t *buffer = p->memory + (p->topIndex * p->size);
    p->topIndex = buffer[0]; // first byte points to the next free buffer
    return buffer;
}

/// Gives buffer back to pool
/// @param p pointer to an instance of pool_t
/// @param buffer to a buffer
/// @return true successfully freed, false otherwise
bool pool_free(pool_t *p, void *buffer)
{
    size_t bufferId;

    // validate pointer and calculate buffer number (ID)
    if((size_t)buffer < (size_t)p->memory)
    {
        return false;
    }
    else
    {
        bufferId = ((size_t)buffer - (size_t)p->memory) / p->size;
        if(bufferId > POOL_MAX)
        {
            return false;
        }
    }

    ((uint8_t *)buffer)[0] = p->topIndex;
    p->topIndex = bufferId; 
    return true;  
}
