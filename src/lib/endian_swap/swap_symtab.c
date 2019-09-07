#include "mach_o.h"

void	swap_nlist(struct nlist *nlist)
{
	nlist->n_un.n_strx = swap_int32(nlist->n_un.n_strx);
	nlist->n_desc = (int16_t)swap_int16((uint16_t)nlist->n_desc);
	nlist->n_value = swap_int32(nlist->n_value);
}

void	swap_nlist_64(struct nlist_64 *nlist)
{
	nlist->n_un.n_strx = swap_int32(nlist->n_un.n_strx);
	nlist->n_desc = swap_int16(nlist->n_desc);
	nlist->n_value = swap_int64(nlist->n_value);
}

void	swap_symtab(t_mach_o *file)
{
	struct symtab_command	*sc;
	struct nlist			*nlist;
	struct nlist_64			*nlist_64;
	size_t					i;

	if (!(sc = file_get_symbol_table_lc(file)))
		return ;
	i = 0;
	nlist = (struct nlist *)(void *)((uint8_t*)file->o_addr + sc->symoff);
	nlist_64 = (struct nlist_64*)(void *)((uint8_t*)file->o_addr
										+ sc->symoff);
	if (file->mh)
		while (i < sc->nsyms)
			swap_nlist(nlist + i++);
	else
		while (i < sc->nsyms)
			swap_nlist_64(nlist_64 + i++);
}
