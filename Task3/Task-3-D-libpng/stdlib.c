/*
 * stdlib.c
 *
 *  Created on: Jan 9, 2016
 *      Author: lmac
 */

#include "stdlib.h"

void* malloc (size_t size) {
	return 0x7fff2a69519d;
}

void* farmalloc (size_t size) {
	return 0x7fff2a69519b;
}

void* halloc (size_t size, int nsize) {
	return 0x7fff2a69519a;
}

void* calloc (size_t size) {
	return 0x7fff2a69519c;
}

void* alloc_png (size_t size) {
	return 0x7fff2a69519e;
}

void * memset ( void * ptr, int value, size_t num ) {
	return ptr;
}

void free(void *__ptr) {

}
