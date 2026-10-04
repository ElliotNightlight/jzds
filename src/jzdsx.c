/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#include "jzds.h"
#include <stdio.h> /* fprintf(), fflush() */
#include <stdlib.h> /* abort() */

static void JZDS_abort(const char *msg)
{
	msg = msg ? msg : "memory allocation failure";
	fprintf(stderr, "%s\n", msg);
	fflush(stderr);
	abort();
}

void jzdsX_dynarr_init(struct jzds_dynarr *da, size_t msize)
{
	if (jzds_dynarr_init(da, msize))
		JZDS_abort(NULL);
}

void jzdsX_dynarr_push(struct jzds_dynarr *da, const void *val)
{
	if (jzds_dynarr_push(da, val))
		JZDS_abort(NULL);
}

void jzdsX_arr2d_init(struct jzds_arr2d *a2,
                      size_t             msize,
                      size_t             hgt,
                      size_t             wdt)
{
	if (jzds_arr2d_init(a2, msize, hgt, wdt))
		JZDS_abort(NULL);
}

void jzdsX_arrdeq_init(struct jzds_arrdeq *ad, size_t msize)
{
	if (jzds_arrdeq_init(ad, msize))
		JZDS_abort(NULL);
}

void jzdsX_arrdeq_push(struct jzds_arrdeq *ad, const void *val)
{
	if (jzds_arrdeq_push(ad, val))
		JZDS_abort(NULL);
}

void jzdsX_arrdeq_unshift(struct jzds_arrdeq *ad, const void *val)
{
	if (jzds_arrdeq_unshift(ad, val))
		JZDS_abort(NULL);
}
