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

#endif /* JZDSX_INCLUDED */
