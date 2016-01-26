
/* pngmem.c - stub functions for memory allocation
 *
 * libpng version 1.2.6beta4 - July 28, 2004
 * For conditions of distribution and use, see copyright notice in png.h
 * Copyright (c) 1998-2004 Glenn Randers-Pehrson
 * (Version 0.96 Copyright (c) 1996, 1997 Andreas Dilger)
 * (Version 0.88 Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.)
 *
 * This file provides a location for all memory allocation.  Users who
 * need special memory handling are expected to supply replacement
 * functions for png_malloc() and png_free(), and to use
 * png_create_read_struct_2() and png_create_write_struct_2() to
 * identify the replacement functions.
 */

#define PNG_INTERNAL
//#include "png.h" //Original code

#include "pngmem.h"

/* Allocate memory for a png_struct or a png_info.  The malloc and
   memset can be replaced by a single call to calloc() if this is thought
   to improve performance noticably. */
png_voidp /* PRIVATE */
png_create_struct(int type)
{
#ifdef PNG_USER_MEM_SUPPORTED
   return (png_create_struct_2(type, png_malloc_ptr_NULL, png_voidp_NULL));
}

/* Allocate memory for a png_struct or a png_info.  The malloc and
   memset can be replaced by a single call to calloc() if this is thought
   to improve performance noticably. */
png_voidp /* PRIVATE */
png_create_struct_2(int type, png_malloc_ptr malloc_fn, png_voidp mem_ptr)
{
#endif /* PNG_USER_MEM_SUPPORTED */
   png_size_t size;
   png_voidp struct_ptr;

   if (type == PNG_STRUCT_INFO)
      size = png_sizeof(png_info);
   else if (type == PNG_STRUCT_PNG)
      size = png_sizeof(png_struct);
   else
      return (NULL);

#ifdef PNG_USER_MEM_SUPPORTED
   if(malloc_fn != NULL)
   {
      png_struct dummy_struct;
      png_structp png_ptr = &dummy_struct;
      png_ptr->mem_ptr=mem_ptr;
      struct_ptr = (*(malloc_fn))(png_ptr, size);
      if (struct_ptr != NULL)
         png_memset(struct_ptr, 0, size);
      return (struct_ptr);
   }
#endif /* PNG_USER_MEM_SUPPORTED */

   /** Idea
    *    if ((struct_ptr =
	*		# if defined(_MSC_VER) && defined(MAXSEG_64K)
	*	   	   (png_voidp)halloc(size,1))
	*		#else
	*	   	   (png_voidp)malloc(size)
	*		#endif
	*	   	   != NULL))
    **/

   /*Solution
    *
    *  #if defined(__TURBOC__) && !defined(__FLAT__)
    *  		if ((struct_ptr = (png_voidp)farmalloc(size,1)) != NULL)
    *  #endif
    *  #if defined(_MSC_VER) && defined(MAXSEG_64K)
    *  		if ((struct_ptr = (png_voidp)halloc(size,1)) != NULL)
    *  #endif
    *  #if defined(OPT_0)
    *  		if ((struct_ptr = (png_voidp)calloc(size,1)) != NULL)
    *  #endif
    *  #if defined(__ALOCPNG__)
    *  		if ((struct_ptr = (png_voidp)alloc_png(size)) != NULL)
    *  #else
    *  		if ((struct_ptr = (png_voidp)malloc(size)) != NULL)
    *  #endif
    */

# if defined(_MSC_VER) && defined(MAXSEG_64K)
	if ((struct_ptr = (png_voidp)halloc(size,1)) != NULL)
# else
	if ((struct_ptr = (png_voidp)malloc(size)) != NULL)
# endif
      png_memset(struct_ptr, 0, size);

   return (struct_ptr);
}

/* Free memory allocated by a png_create_struct() call */
void /* PRIVATE */
png_destroy_struct(png_voidp struct_ptr)
{
#ifdef PNG_USER_MEM_SUPPORTED
   png_destroy_struct_2(struct_ptr, png_free_ptr_NULL, png_voidp_NULL);
}

/* Free memory allocated by a png_create_struct() call */
void /* PRIVATE */
png_destroy_struct_2(png_voidp struct_ptr, png_free_ptr free_fn,
    png_voidp mem_ptr)
{
#endif /* PNG_USER_MEM_SUPPORTED */
   if (struct_ptr != NULL)
   {
#ifdef PNG_USER_MEM_SUPPORTED
      if(free_fn != NULL)
      {
         png_struct dummy_struct;
         png_structp png_ptr = &dummy_struct;
         png_ptr->mem_ptr=mem_ptr;
         (*(free_fn))(png_ptr, struct_ptr);
         return;
      }
#endif /* PNG_USER_MEM_SUPPORTED */
#if defined(__TURBOC__) && !defined(__FLAT__)
      farfree(struct_ptr);
#else
# if defined(_MSC_VER) && defined(MAXSEG_64K)
      hfree(struct_ptr);
# else
      free(struct_ptr);
# endif
#endif
   }
}
