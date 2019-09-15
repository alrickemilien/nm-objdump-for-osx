/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:07:46 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:07:48 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static const char	g_help[] =
"Usage: %s [-arch arch_type]"
" [-fahlLDtdorSTMRIHGvVcXmqQjCP]"
" [-mcpu=arg] [--version]"
" <object file> ...\n"
"	-f print the fat headers\n"
"	-a print the archive header\n"
"	-h print the mach header\n"
"	-l print the load commands\n"
"	-L print shared libraries used\n"
"	-D print shared library id name\n"
"	-t print the text section (disassemble with -v)\n"
"	-p <routine name>  start dissassemble from routine name\n"
"	-s <segname> <sectname> print contents of section\n"
"	-d print the data section\n"
"	-o print the Objective-C segment\n"
"	-r print the relocation entries\n"
"	-S print the table of contents of a library\n"
"	-T print the table of contents of a dynamic shared library\n"
"	-M print the module table of a dynamic shared library\n"
"	-R print the reference table of a dynamic shared library\n"
"	-I print the indirect symbol table\n"
"	-H print the two-level hints table\n"
"	-G print the data in code table\n"
"	-v print verbosely (symbolically) when possible\n"
"	-V print disassembled operands symbolically\n"
"	-c print argument strings of a core file\n"
"	-X print no leading addresses or headers\n"
"	-m don't use archive(member) syntax\n"
"	-B force Thumb disassembly (ARM objects only)\n"
"	-q use llvm's disassembler (the default)\n"
"	-Q use otool(1)'s disassembler\n"
"	-mcpu=arg use `arg' as the cpu for disassembly\n"
"	-j print opcode bytes\n"
"	-P print the info plist section as strings\n"
"	-C print linker optimization hints\n"
"	--version print the version of %s\n";

int	exit_with_help(void)
{
	if (write(1, g_help, sizeof(g_help)) < 0)
		return (-1);
	return (0);
}
