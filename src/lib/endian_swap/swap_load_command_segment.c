void	swap_load_command_segment_32(struct load_command *lc)
{
	struct segment_command	*sc;
	uint32_t				i;

	sc = (struct segment_command *)lc;
	sc->vmaddr = swap_int32(sc->vmaddr);
	sc->vmsize = swap_int32(sc->vmsize);
	sc->fileoff = swap_int32(sc->fileoff);
	sc->filesize = swap_int32(sc->filesize);
	sc->maxprot = (vm_prot_t)swap_int32((uint32_t)sc->maxprot);
	sc->initprot = (vm_prot_t)swap_int32((uint32_t)sc->initprot);
	sc->nsects = swap_int32(sc->nsects);
	sc->flags = swap_int32(sc->flags);
	i = 0;
	while (i < sc->nsects)
		swap_section((struct section *)(sc + 1) + i++);
}

void	swap_load_command_segment_64(struct load_command *lc)
{
	struct segment_command_64	*sc;
	uint32_t					i;

	sc = (struct segment_command_64 *)(void *)lc;
	sc->vmaddr = swap_int64(sc->vmaddr);
	sc->vmsize = swap_int64(sc->vmsize);
	sc->fileoff = swap_int64(sc->fileoff);
	sc->filesize = swap_int64(sc->filesize);
	sc->maxprot = (vm_prot_t)swap_int32((uint32_t)sc->maxprot);
	sc->initprot = (vm_prot_t)swap_int32((uint32_t)sc->initprot);
	sc->nsects = swap_int32(sc->nsects);
	sc->flags = swap_int32(sc->flags);
	i = 0;
	while (i < sc->nsects)
		swap_section_64((struct section_64 *)(sc + 1) + i++);
}