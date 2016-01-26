/*
 * pngmen.h
 *
 *  Created on: Jan 9, 2016
 *      Author: lmac
 */

#ifndef TASK_3_U_LIBPNG_PNGMEM_H_
#define TASK_3_U_LIBPNG_PNGMEM_H_

// Luiz Mock
#include "stdlib.h"

// Mock start

#define PNG_USER_MEM_SUPPORTED //Luiz

#define PNGARG(arglist) arglist

typedef void (*png_free_ptr) PNGARG((png_structp, png_voidp));

#define png_free_ptr_NULL         (png_free_ptr)NULL

#define PNG_STRUCT_PNG   0x0001
#define PNG_STRUCT_INFO  0x0002

#define FAR //It's a mock
//#define NULL "null" //It's a mock

#define PNGARG(arglist) arglist
#define png_malloc_ptr_NULL       (png_malloc_ptr)NULL
#define png_voidp_NULL            (png_voidp)NULL

typedef void * png_voidp;
typedef size_t png_size_t;
struct png_struct_def //It's a mock
{
	png_voidp mem_ptr;
};
typedef struct png_struct_def png_struct;
typedef png_struct FAR * png_structp;
typedef png_voidp (*png_malloc_ptr) PNGARG((png_structp, png_size_t));

typedef struct png_info_struct
{
	//It's a mock.
	int mock;
} png_info;

#ifdef PNG_SIZE_T
   typedef PNG_SIZE_T png_size_t;
#  define png_sizeof(x) png_convert_size(sizeof (x))
#else
   typedef size_t png_size_t;
#  define png_sizeof(x) sizeof (x)
#endif

#define png_memset  memset

//Mock end

png_voidp  png_create_struct_2(int type, png_malloc_ptr malloc_fn, png_voidp mem_ptr);

png_voidp png_create_struct(int type);

#endif /* TASK_3_U_LIBPNG_PNGMEM_H_ */
