/*
 * stdlib.h
 *
 *  Created on: Jan 9, 2016
 *      Author: lmac
 */

#ifndef TASK_3_U_LIBPNG_STDLIB_H_
#define TASK_3_U_LIBPNG_STDLIB_H_

#include <stddef.h>

void* malloc (size_t size);

void* calloc (size_t size);

void free(void *__ptr);

void* farmalloc (size_t size);

void* halloc (size_t size, int nsize);

void * memset ( void * ptr, int value, size_t num );

#endif /* TASK_3_U_LIBPNG_STDLIB_H_ */
