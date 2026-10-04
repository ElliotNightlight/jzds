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

#endif /* JZDSX_INCLUDED */
