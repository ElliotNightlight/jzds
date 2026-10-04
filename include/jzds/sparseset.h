/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#ifndef JZDS_SPARSESET_INCLUDED
#define JZDS_SPARSESET_INCLUDED

#include <stddef.h> /* size_t */
#include <stdbool.h> /* bool */

struct jzds_sparseset {
	size_t  cnt; /* count */
	size_t  rng; /* range */
	size_t *dense;
	size_t *spars;
};

int  jzds_sparseset_init   (struct jzds_sparseset *sps, size_t rng);
void jzds_sparseset_cleanup(struct jzds_sparseset *sps);

bool jzds_sparseset_find(struct jzds_sparseset *sps, size_t val, size_t *idxp);

void jzds_sparseset_add   (struct jzds_sparseset *sps, size_t val);
void jzds_sparseset_remove(struct jzds_sparseset *sps, size_t val);

#endif /* JZDS_SPARSESET_INCLUDED */
