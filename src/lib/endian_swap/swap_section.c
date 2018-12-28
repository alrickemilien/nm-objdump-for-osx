void	swap_section_32(struct section *section)
{
	section->addr = swap_int32(section->addr);
	section->size = swap_int32(section->size);
	section->offset = swap_int32(section->offset);
	section->align = swap_int32(section->align);
	section->reloff = swap_int32(section->reloff);
	section->nreloc = swap_int32(section->nreloc);
	section->flags = swap_int32(section->flags);
}

void	swap_section_64(struct section_64 *section)
{
	section->addr = swap_int64(section->addr);
	section->size = swap_int64(section->size);
	section->offset = swap_int32(section->offset);
	section->align = swap_int32(section->align);
	section->reloff = swap_int32(section->reloff);
	section->nreloc = swap_int32(section->nreloc);
	section->flags = swap_int32(section->flags);
}