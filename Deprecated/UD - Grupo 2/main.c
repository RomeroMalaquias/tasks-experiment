/*
 * main.c
 *
 *  Created on: Jan 9, 2016
 *      Author: lmac
 */

#include <stdio.h>

#include "pngmem.h"

int main () {
	png_voidp png_p = png_create_struct(PNG_STRUCT_PNG);
	printf("%p\n", png_p);
	return 0;
}
