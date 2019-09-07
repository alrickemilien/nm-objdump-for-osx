#include "mach_o.h"

/*
** This file finds the common sections and tables of a mach o file
*/

/*
** This function loops over section
** and returns the adress of the corresponding section
** with given segment_name and section_name
*/

uint32_t    find_section_index(t_mach_o_processor *mach_o,
                        char *segment_name,
                        char *section_name)
{
	uint32_t	i;

	// assert(mach_o->secs || mach_o->secs_64);

	i = 0;

 	// 32 bits
	if (mach_o->secs)
	{
		while (i < mach_o->nsects)
		{
			if (ft_strequ(segment_name, mach_o->secs[i]->segname)
				&& ft_strequ(section_name, mach_o->secs[i]->sectname))
				return (i);
			i++;
		}
	}

 	// 64 bits
	else
	{
		while (i < mach_o->nsects)
		{
			if (ft_strequ(segment_name, mach_o->secs_64[i]->segname)
				&& ft_strequ(section_name, mach_o->secs_64[i]->sectname))
				return (i);
			i++;
		}
	}

  return ((uint32_t)-1);
}

/*
** This function finds common sections of mach o files :
** __TEXT section
** __DATA section
** __BSS section
*/

void		find_common_sections_indexes(t_mach_o_processor *mach_o)
{
	mach_o->text_nsect = find_section_index(mach_o, SEG_TEXT, SECT_TEXT);
	mach_o->data_nsect = find_section_index(mach_o, SEG_DATA, SECT_DATA);
	mach_o->bss_nsect = find_section_index(mach_o, SEG_DATA, SECT_BSS);
}

static struct symtab_command	*find_symbol_table_load_command(t_mach_o *file)
{
	return
  ((struct symtab_command *)find_load_command_by_command(file, LC_SYMTAB));
}

static struct dysymtab_command	*find_dsymtab_load_command(t_mach_o *file)
{
	return
  ((struct dysymtab_command *)find_load_command_by_command(file, LC_DYSYMTAB));
}

/*
** This function finds the start of the symbol table in a mach o file
*/

uint32_t	find_symbol_table_index(t_mach_o_processor *mach_o,
										t_mach_o *file)
{
	if ((mach_o->st_lc = find_symbol_table_load_command(file)) == NULL)
		return (-1);

 	mach_o->dysym_lc = find_dsymtab_load_command(file);

 	// 32 bits structure
 	if (file->mh)
 	{
		mach_o->symtab = (struct nlist *)(void *)((uint8_t*)file->o_addr
										+ mach_o->st_lc->symoff);

    	// Find the associated string table index
    	mach_o->string_table = (uint8_t*)((uint8_t*)file->o_addr
										+ mach_o->st_lc->stroff);
	}

 	// 64 bits structure
 	else
	{
		mach_o->symtab_64 = (struct nlist_64 *)(void *)(
										(uint8_t*)file->o_addr
										+ mach_o->st_lc->symoff);

    	// Find the associated string table index
    	mach_o->string_table = (uint8_t*)((uint8_t*)file->o_addr
										+ mach_o->st_lc->stroff);
	}

 	return (0);
}
