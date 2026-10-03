/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#ifndef JZDS_DYNARR_INCLUDED
#define JZDS_DYNARR_INCLUDED

#include <stdlib.h> /* size_t */

struct jzds_dynarr {
	size_t msize;

	size_t         len;
	size_t         cap;
	unsigned char *dat;
};

int  jzds_dynarr_init   (struct jzds_dynarr *da, size_t msize);
void jzds_dynarr_cleanup(struct jzds_dynarr *da);

void *jzds_dynarr_at(struct jzds_dynarr *da, size_t idx);

int  jzds_dynarr_push(struct jzds_dynarr *da, const void *val);
void jzds_dynarr_pop (struct jzds_dynarr *da, void *val);

#endif /* JZDS_DYNARR_INCLUDED */

