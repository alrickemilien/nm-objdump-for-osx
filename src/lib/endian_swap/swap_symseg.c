void		swap_lc_symseg(struct load_command *lc)
{
	struct symseg_command	*sc;

	sc = (struct symseg_command*)lc;
	sc->offset = swap_int32(sc->offset);
	sc->size = swap_int32(sc->size);
}