/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#include "jzds/sparseset.h"
#include <stdlib.h> /* malloc(), free(), realloc() */
#include <assert.h> /* assert() */

int jzds_sparseset_init(struct jzds_sparseset *sps, size_t rng)
{
	void *bufd = malloc(rng * sizeof *sps->dense);
	if (!bufd)
		return 1;
	void *bufs = malloc(rng * sizeof *sps->spars);
	if (!bufs) {
		free(bufd);
		return 1;
	}

	*sps = (struct jzds_sparseset){
		.cnt = 0,
		.rng = rng,
		.dense = bufd,
		.spars = bufs
	};
	return 0;
}

void jzds_sparseset_cleanup(struct jzds_sparseset *sps)
{
	free(sps->dense);
	free(sps->spars);
}

bool jzds_sparseset_find(struct jzds_sparseset *sps, size_t val, size_t *idxp)
{
	assert(val < sps->rng);

	size_t idx = sps->spars[val];
	if (idx >= sps->cnt || sps->dense[idx] != val)
		return false;
	if (idxp)
		*idxp = idx;
	return true;
}

void jzds_sparseset_add(struct jzds_sparseset *sps, size_t val)
{
	assert(val < sps->rng);

	size_t i = sps->spars[val];
	if (i < sps->cnt && sps->dense[i] == val)
		return;

	assert(sps->cnt < sps->rng);

	size_t j = sps->cnt++;
	sps->dense[j] = val;
	sps->spars[val] = j;
}

void jzds_sparseset_remove(struct jzds_sparseset *sps, size_t val)
{
	assert(val < sps->rng);

	size_t i = sps->spars[val];
	if (i >= sps->cnt || sps->dense[i] != val)
		return;

	size_t j = --sps->cnt;
	sps->dense[i] = sps->dense[j];
	sps->spars[sps->dense[i]] = i;
}
