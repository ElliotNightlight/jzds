/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#ifndef JZDS_ARR2D_INCLUDED
#define JZDS_ARR2D_INCLUDED

#include <stddef.h> /* size_t */

struct jzds_arr2d {
	size_t msize;

	size_t         hgt;
	size_t         wdt;
	unsigned char *dat;
};

int jzds_arr2d_init(struct jzds_arr2d *a2,
                    size_t             msize,
                    size_t             hgt,
                    size_t             wdt);
void jzds_arr2d_cleanup(struct jzds_arr2d *a2);

void *jzds_arr2d_at(struct jzds_arr2d *a2, size_t row, size_t col);

#endif /* JZDS_ARR2D_INCLUDED */
