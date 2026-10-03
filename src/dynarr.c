/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#include "jzds/dynarr.h"
#include <stdlib.h> /* malloc(), free(), realloc() */
#include <string.h> /* memcpy() */
#include <assert.h> /* assert() */

int jzds_dynarr_init(struct jzds_dynarr *da, size_t msize)
{
	assert(msize > 0);

	size_t n = 16;
	void *buf = malloc(n * msize);
	if (!buf)
		return 1;

	*da = (struct jzds_dynarr){
		.msize = msize,
		.len = 0,
		.cap = n,
		.dat = buf
	};
	return 0;
}

void jzds_dynarr_cleanup(struct jzds_dynarr *da)
{
	free(da->dat);
}

void *jzds_dynarr_at(struct jzds_dynarr *da, size_t idx)
{
	const size_t msize = da->msize;

	assert(idx < da->len);

	return &da->dat[idx * msize];
}

static int JZDS_dynarr_grow(struct jzds_dynarr *da)
{
	const size_t msize = da->msize;

	size_t ncap = da->cap * 3 / 2 + 1;
	void *ndat = realloc(da->dat, ncap * msize);
	if (!ndat)
		return 1;

	da->cap = ncap;
	da->dat = ndat;

	return 0;
}

int jzds_dynarr_push(struct jzds_dynarr *da, const void *val)
{
	const size_t msize = da->msize;

	if (da->len == da->cap && JZDS_dynarr_grow(da))
		return 1;

	size_t idx = da->len++;
	memcpy(&da->dat[idx * msize], val, msize);

	return 0;
}

void jzds_dynarr_pop(struct jzds_dynarr *da, void *val)
{
	const size_t msize = da->msize;

	assert(da->len > 0);

	--da->len;
	if (val) {
		size_t idx = da->len;
		memcpy(val, &da->dat[idx * msize], msize);
	}
}
