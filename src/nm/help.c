static const char *help = 
"OVERVIEW: llvm symbol table dumper\n\n"
"USAGE: nm [options] <input files> --s Dump only symbols from this segment and section name, Mach-O only\n\n"
"OPTIONS:\n\n"
"General options:\n\n"

"  -B                                   - Alias for --format=bsd\n"
"  -P                                   - Alias for --format=posix\n"
"  -aarch64-neon-syntax                 - Choose style of NEON code to emit from AArch64 backend:\n"
"    =generic                           -   Emit generic NEON assembly\n"
"    =apple                             -   Emit Apple-style NEON assembly"
  -add-dyldinfo                        - Add symbols from the dyldinfo not already in the symbol table, Mach-O only
  -arch=<string>                       - architecture(s) from a Mach-O file to dump
  -arm-add-build-attributes            -
  -arm-implicit-it                     - Allow conditional instructions outdside of an IT block
    =always                            -   Accept in both ISAs, emit implicit ITs in Thumb
    =never                             -   Warn in ARM, reject in Thumb
    =arm                               -   Accept in ARM, reject in Thumb
    =thumb                             -   Warn in ARM, emit implicit ITs in Thumb
  -debug-syms                          - Show all symbols, even debugger only
  -defined-only                        - Show only defined symbols
  -demangle                            - Demangle C++ symbol names
  -dyldinfo-only                       - Show only symbols from the dyldinfo, Mach-O only
  -dynamic                             - Display the dynamic symbols instead of normal symbols.
  -extern-only                         - Show only external symbols
  -filter-print-funcs=<function names> - Only print IR for functions whose name match this for all print-[before|after][-all] options
  -format                              - Specify output format
    =bsd                               -   BSD format
    =sysv                              -   System V format
    =posix                             -   POSIX.2 format
"    =darwin                            -   Darwin -m format\n"
"  -just-symbol-name                    - Print just the symbol's name\n"
"  -m                                   - Alias for --format=darwin\n"
"  -no-dyldinfo                         - Don't add any symbols from the dyldinfo, Mach-O only"
  -no-llvm-bc                          - Disable LLVM bitcode reader
  -no-sort                             - Show symbols in order encountered
  -numeric-sort                        - Sort symbols by address
  -print-after-all                     - Print IR after each pass
  -print-armap                         - Print the archive map
  -print-before-all                    - Print IR before each pass
  -print-file-name                     - Precede each symbol with the object file it came from
  -print-size                          - Show symbol size instead of address
  -radix                               - Radix (o/d/x) for printing symbol Values
    =d                                 -   decimal
    =o                                 -   octal
    =x                                 -   hexadecimal
"  -reverse-sort                        - Sort in reverse order\n"
"  -rng-seed=<seed>                     - Seed for the random number generator\n"
"  -s=<string>                          - Dump only symbols from this segment and section name, Mach-O only\n"
"  -size-sort                           - Sort symbols by size\n"
"  -time-passes                         - Time each pass, printing elapsed time for each on exit\n"
"  -undefined-only                      - Show only undefined symbols\n"
"  -verify-debug-info                   -\n"
"  -verify-dom-info                     - Verify dominator info (time consuming)\n"
"  -x                                   - Print symbol entry in hex, Mach-O only\n"
"  -x86-asm-syntax                      - Choose style of code to emit from X86 backend:\n"
"    =att                               -   Emit AT&T-style assembly\n"
"    =intel                             -   Emit Intel-style assembly\n"
"\n"
"Generic Options:\n\n"
"  -help                                - Display available options (-help-hidden for more)\n"
"  -help-list                           - Display list of available options (-help-list-hidden for more)\n"
"  -version                             - Display the version of this program\n";

int exit_with_help(void)
{
  write(1, help, sizeof(help));
  return (0);
}