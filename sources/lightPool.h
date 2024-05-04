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

#ifndef LP_HEADER
#define LP_HEADER

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t topIndex; // index of the first buffer
    uint8_t count; // number of buffers
    size_t size; // size of each buffer
	uint8_t *memory; // pointer to the memory location of the pool
} pool_t;

bool pool_init(pool_t *pool, void *memory, uint8_t buffersCount, size_t bufferSize);
bool pool_isEmpty(pool_t *pool);
void * pool_allocate(pool_t *pool);
bool pool_free(pool_t *pool, void *buffer);

#endif
