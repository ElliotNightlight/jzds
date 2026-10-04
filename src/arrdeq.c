/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#include "jzds/arrdeq.h"
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memcpy() */
#include <assert.h> /* assert() */

int jzds_arrdeq_init(struct jzds_arrdeq *ad, size_t msize)
{
	size_t n = 16;
	void *buf = malloc(n * msize);
	if (!buf)
		return 1;

	*ad = (struct jzds_arrdeq){
		.msize = msize,
		.beg = n / 2,
		.end = n / 2,
		.cap = n,
		.dat = buf
	};
	return 0;
}

void jzds_arrdeq_cleanup(struct jzds_arrdeq *ad)
{
	free(ad->dat);
}

size_t jzds_arrdeq_len(struct jzds_arrdeq *ad)
{
	return ad->end - ad->beg;
}

void *jzds_arrdeq_at(struct jzds_arrdeq *ad, size_t idx)
{
	const size_t msize = ad->msize;

	assert(idx < ad->end - ad->beg);

	idx += ad->beg;
	return &ad->dat[idx * msize];
}

static int JZDS_arrdeq_refit(struct jzds_arrdeq *ad)
{
	const size_t msize = ad->msize;

	size_t len = ad->end - ad->beg;
	size_t pad = len / 2 + 1;

	size_t ncap = len + pad * 2;
	unsigned char *ndat = malloc(ncap * msize);
	if (!ndat)
		return 1;

	memcpy(&ndat[pad * msize], &ad->dat[ad->beg * msize], len * msize);
	free(ad->dat);

	ad->beg = pad;
	ad->end = len + pad;
	ad->cap = ncap;
	ad->dat = ndat;

	return 0;
}

int jzds_arrdeq_push(struct jzds_arrdeq *ad, const void *val)
{
	const size_t msize = ad->msize;

	if (ad->end == ad->cap && JZDS_arrdeq_refit(ad))
		return 1;

	size_t idx = ad->end++;
	memcpy(&ad->dat[idx * msize], val, msize);

	return 0;
}

int jzds_arrdeq_unshift(struct jzds_arrdeq *ad, const void *val)
{
	const size_t msize = ad->msize;

	if (ad->beg == 0 && JZDS_arrdeq_refit(ad))
		return 1;

	size_t idx = --ad->beg;
	memcpy(&ad->dat[idx * msize], val, msize);

	return 0;
}

void jzds_arrdeq_pop(struct jzds_arrdeq *ad, void *val)
{
	const size_t msize = ad->msize;

	assert(ad->beg < ad->end);

	--ad->end;
	if (val) {
		size_t idx = ad->end;
		memcpy(val, &ad->dat[idx * msize], msize);
	}
}

void jzds_arrdeq_shift(struct jzds_arrdeq *ad, void *val)
{
	const size_t msize = ad->msize;

	assert(ad->beg < ad->end);

	if (val) {
		size_t idx = ad->beg;
		memcpy(val, &ad->dat[idx * msize], msize);
	}
	++ad->beg;
}
