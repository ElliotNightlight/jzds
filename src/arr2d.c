/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#include "jzds/arr2d.h"
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

int jzds_arr2d_init(struct jzds_arr2d *a2,
                    size_t             msize,
                    size_t             hgt,
                    size_t             wdt)
{
	assert(msize > 0);

	void *buf = malloc(hgt * wdt * msize);
	if (hgt && wdt && !buf)
		return 1;

	*a2 = (struct jzds_arr2d){
		.msize = msize,
		.hgt = hgt,
		.wdt = wdt,
		.dat = buf
	};
	return 0;
}

void jzds_arr2d_cleanup(struct jzds_arr2d *a2)
{
	free(a2->dat);
}

void *jzds_arr2d_at(struct jzds_arr2d *a2, size_t row, size_t col)
{
	const size_t msize = a2->msize;

	assert(row < a2->hgt);
	assert(col < a2->wdt);

	size_t idx = row * a2->wdt + col;
	return &a2->dat[idx * msize];
}
