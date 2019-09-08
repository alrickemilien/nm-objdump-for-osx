#include "nm.h"

#define A_ uint64_t last, int (*cmp)(const void *, const void *), size_t

static void		swap(void *a, void *b, size_t type_size)
{
	size_t		i;
	uint8_t     tmp_short;
	uint64_t	tmp;

	i = 0;
	while (i < (type_size & 7) && i < type_size)
	{
		tmp_short = ((uint8_t*)a)[i];
		((uint8_t*)a)[i] = ((uint8_t*)b)[i];
		((uint8_t*)b)[i] = tmp_short;
		i++;
	}
	while (i < type_size)
	{
		tmp = ((uint64_t*)a)[i / 8];
		((uint64_t*)a)[i / 8] = ((uint64_t*)b)[i / 8];
		((uint64_t*)b)[i / 8] = tmp;
		i += 8;
	}
}

static uint64_t	partitioning(
    void *tab,
    uint64_t start,
    uint64_t pivot,
    A_ type_size)
{
	uint64_t	i;
	uint64_t	u;

	swap(tab + last * type_size, tab + pivot * type_size, type_size);
	i = start;
	u = start;
	while (i < last)
	{
		if (cmp(tab + i * type_size, tab + last * type_size) < 0)
			swap(tab + i * type_size, tab + (u++ * type_size), type_size);
		i++;
	}
	swap(tab + last * type_size, tab + u * type_size, type_size);
	return (u);
}

static void		quicksort(void *tab, uint64_t start, A_ type_size)
{
	uint64_t	pivot;

	if (start < last)
	{
		pivot = (rand() % (last - start + 1)) + start;
		pivot = partitioning(tab, start, pivot, last, cmp, type_size);
		if (pivot > 0)
			quicksort(tab, start, pivot - 1, cmp, type_size);
		quicksort(tab, pivot + 1, last, cmp, type_size);
	}
}

void					sort(
    void *tab,
    size_t elem_nbr,
    size_t type_size,
    int (*cmp)(const void *, const void *))
{
	if (!elem_nbr)
		return ;
	quicksort(tab, 0, elem_nbr - 1, cmp, type_size);
	return ;
}

#undef A_
