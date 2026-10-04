/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#ifndef JZDS_ARRDEQ_INCLUDED
#define JZDS_ARRDEQ_INCLUDED

#include <stddef.h> /* size_t */

struct jzds_arrdeq {
	size_t msize;

	size_t         beg;
	size_t         end;
	size_t         cap;
	unsigned char *dat;
};

int  jzds_arrdeq_init   (struct jzds_arrdeq *ad, size_t msize);
void jzds_arrdeq_cleanup(struct jzds_arrdeq *ad);

size_t  jzds_arrdeq_len(struct jzds_arrdeq *ad);
void   *jzds_arrdeq_at (struct jzds_arrdeq *ad, size_t idx);

int  jzds_arrdeq_push   (struct jzds_arrdeq *ad, const void *val);
int  jzds_arrdeq_unshift(struct jzds_arrdeq *ad, const void *val);
void jzds_arrdeq_pop    (struct jzds_arrdeq *ad, void *val);
void jzds_arrdeq_shift  (struct jzds_arrdeq *ad, void *val);

#endif /* JZDS_ARRDEQ_INCLUDED */
