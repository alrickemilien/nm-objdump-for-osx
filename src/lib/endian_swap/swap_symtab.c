
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

void	ofile_swap_macho_symtab(t_ofile *ofile)
{
	struct symtab_command	*sc;
	struct nlist			*nlist;
	struct nlist_64			*nlist_64;
	uint32_t				i;

	if (!(sc = ofile_get_symbol_table_lc(ofile)))
		return ;
	i = 0;
	nlist = (struct nlist *)(void *)((uint8_t*)ofile->object_addr + sc->symoff);
	nlist_64 = (struct nlist_64*)(void *)((uint8_t*)ofile->object_addr
										+ sc->symoff);
	if (ofile->mh)
		while (i < sc->nsyms)
			swap_nlist(nlist + i++);
	else
		while (i < sc->nsyms)
			swap_nlist_64(nlist_64 + i++);
}
