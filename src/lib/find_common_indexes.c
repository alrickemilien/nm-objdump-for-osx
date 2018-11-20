/*
** This file finds the common sections and tables of a mach o file
*/

#include "mach_o_utils.h"

/*
** This function loop over section
** and returns the adress of the corresponding section
** with given segment_name and section_name
*/

uint32_t    find_section_index(t_nm_process_info *nm_info,
                        char *segment_name,
                        char *section_name)
{
	uint32_t	i;

	assert(nm_info->secs || nm_info->secs_64);

	i = 0;

  // 32 bits
	if (nm_info->secs)
	{
		while (i < nm_info->nsects)
		{
			if (ft_strequ(seg_name, nm_info->secs[i]->segname)
				&& ft_strequ(sec_name, nm_info->secs[i]->sectname))
				return (i);
			i++;
		}
	}

  // 64 bits
	else
	{
		while (i < nm_info->nsects)
		{
			if (ft_strequ(seg_name, nm_info->secs_64[i]->segname)
				&& ft_strequ(sec_name, nm_info->secs_64[i]->sectname))
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

inline void		find_common_sections_indexes()
{
	nm_info->text_nsect = find_section_index(nm_info, SEG_TEXT, SECT_TEXT);
	nm_info->data_nsect = find_section_index(nm_info, SEG_DATA, SECT_DATA);
	nm_info->bss_nsect = find_section_index(nm_info, SEG_DATA, SECT_BSS);
}


static struct symtab_command	*find_symbol_table_load_command(t_ofile *ofile)
{
	return
  ((struct symtab_command *)find_load_command_by_command(ofile, LC_SYMTAB));
}

static struct dysymtab_command	*find_dsymtab_load_command(t_ofile *ofile)
{
	return
  ((struct dysymtab_command *)find_load_command_by_command(ofile, LC_DYSYMTAB));
}

/*
** This function finds the start of the symbol table in a mach o file
*/

static uint32_t	find_symbol_table_index(t_nm_process_info *nm_info,
										t_ofile *ofile)
{
	if (NULL == (nm_info->st_lc = find_symbol_table_load_command(ofile)))
		return (-1);

  nm_info->dysym_lc = find_dsymtab_load_command(ofile);

  // 32 bits structure
  if (ofile->mh)
	{
		nm_info->symtab = (struct nlist *)(void *)((uint8_t*)ofile->object_addr
										+ nm_info->st_lc->symoff);

    // Find the associated string table index
    nm_info->string_table = (uint8_t*)((uint8_t*)ofile->object_addr
										+ nm_info->st_lc->stroff);
	}

  // 64 bits structure
  else
	{
		nm_info->symtab_64 = (struct nlist_64 *)(void *)(
										(uint8_t*)ofile->object_addr
										+ nm_info->st_lc->symoff);

    // Find the associated string table index
    nm_info->string_table = (uint8_t*)((uint8_t*)ofile->object_addr
										+ nm_info->st_lc->stroff);
	}

  return (0);
}
