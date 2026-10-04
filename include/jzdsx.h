/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#ifndef JZDSX_INCLUDED
#define JZDSX_INCLUDED

#include "jzds.h"
#include <stddef.h> /* size_t */

/* dynarr */
void jzdsX_dynarr_init(struct jzds_dynarr *da, size_t msize);
void jzdsX_dynarr_push(struct jzds_dynarr *da, const void *val);

/* arr2d */
void jzdsX_arr2d_init(struct jzds_arr2d *a2,
                      size_t             msize,
                      size_t             hgt,
                      size_t             wdt);

/* arrdeq */
void jzdsX_arrdeq_init   (struct jzds_arrdeq *ad, size_t msize);
void jzdsX_arrdeq_push   (struct jzds_arrdeq *ad, const void *val);
void jzdsX_arrdeq_unshift(struct jzds_arrdeq *ad, const void *val);

#endif /* JZDSX_INCLUDED */
