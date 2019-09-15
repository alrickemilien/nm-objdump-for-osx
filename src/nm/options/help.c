/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:52:41 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:52:42 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static const char g_help[] =
"OVERVIEW: llvm symbol table dumper\n\n"
"USAGE: nm [options]"
" <input files> --s"
" Dump only symbols from this segment and "
"section name, Mach-O only\n\n"
"OPTIONS:\n\n"
"General options:\n\n"
"  -B                                   - Alias for --format=bsd\n"
"  -P                                   - Alias for --format=posix\n"
"  -aarch64-neon-syntax                 "
"- Choose style of NEON code to emit from AArch64 backend:\n"
"    =generic                           -   Emit generic NEON assembly\n"
"    =apple                             "
"-   Emit Apple-style NEON assembly\n"
"  -add-dyldinfo                        "
"- Add symbols from the dyldinfo not already in the symbol table, Mach-O only\n"
"  -arch=<string>                       "
"- architecture(s) from a Mach-O file to dump\n"
"  -arm-add-build-attributes            -\n"
"  -arm-implicit-it                     "
"- Allow conditional instructions outdside of an IT block\n"
"    =always                            "
"-   Accept in both ISAs, emit implicit ITs in Thumb\n"
"    =never                             -   Warn in ARM, reject in Thumb\n"
"    =arm                               -   Accept in ARM, reject in Thumb\n"
"    =thumb                             "
"-   Warn in ARM, emit implicit ITs in Thumb\n"
"  -debug-syms                          "
"- Show all symbols, even debugger only\n"
"  -defined-only                        - Show only defined symbols\n"
"  -demangle                            - Demangle C++ symbol names\n"
"  -dyldinfo-only                       "
"- Show only symbols from the dyldinfo, Mach-O only\n"
"  -dynamic                             "
"- Display the dynamic symbols instead of normal symbols.\n"
"  -extern-only                         - Show only external symbols\n"
"  -filter-print-funcs=<function names> "
"- Only print IR for functions whose name "
"match this for all print-[before|after][-all] options\n"
"  -format                              - Specify output format\n"
"    =bsd                               -   BSD format\n"
"    =sysv                              -   System V format\n"
"    =posix                             -   POSIX.2 format\n"
"    =darwin                            -   Darwin -m format\n"
"  -just-symbol-name                    - Print just the symbol's name\n"
"  -m                                   - Alias for --format=darwin\n"
"  -no-dyldinfo                         "
"- Don't add any symbols from the dyldinfo, Mach-O only\n"
"  -no-llvm-bc                          - Disable LLVM bitcode reader\n"
"  -no-sort                             - Show symbols in order encountered\n"
"  -numeric-sort                        - Sort symbols by address\n"
"  -print-after-all                     - Print IR after each pass\n"
"  -print-armap                         - Print the archive map\n"
"  -print-before-all                    - Print IR before each pass\n"
"  -print-file-name                     "
"- Precede each symbol with the object file it came from\n"
"  -print-size                          "
"- Show symbol size instead of address\n"
"  -radix                               "
"- Radix (o/d/x) for printing symbol Values\n"
"    =d                                 "
"-   decimal\n"
"    =o                                 "
"-   octal\n"
"    =x                                 -   hexadecimal\n"
"  -reverse-sort                        - Sort in reverse order\n"
"  -rng-seed=<seed>                     "
"- Seed for the random number generator\n"
"  -s=<string>                          "
"- Dump only symbols from this segment and section name, Mach-O only\n"
"  -size-sort                           - Sort symbols by size\n"
"  -time-passes                         "
"- Time each pass, printing elapsed time for each on exit\n"
"  -undefined-only                      - Show only undefined symbols\n"
"  -verify-debug-info                   -\n"
"  -verify-dom-info                     "
"- Verify dominator info (time consuming)\n"
"  -x                                   "
"- Print symbol entry in hex, Mach-O only\n"
"  -x86-asm-syntax                      "
"- Choose style of code to emit from X86 backend:\n"
"    =att                               -   Emit AT&T-style assembly\n"
"    =intel                             -   Emit Intel-style assembly\n"
"\n"
"Generic Options:\n\n"
"  -help                                "
"- Display available options (-help-hidden for more)\n"
"  -help-list                           "
"- Display list of available options (-help-list-hidden for more)\n"
"  -version                             "
"- Display the version of this program\n";

int	exit_with_help(void)
{
	if (write(1, g_help, sizeof(g_help)) < 0)
		return (-1);
	return (0);
}
