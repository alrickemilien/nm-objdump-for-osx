# nm - objdump for OSX

Rewrite the tools nm and otool that you can find on OSX.
These provides the same functionnalities as objdump on Linux softwares.

This project provides three binaries :
```bash
# This program read mach o files
./nm
```
```bash
# This program displays segment text of mach o files
./otool
```
```bash
# This program generate a mach o file from a config
./mach-o-builder mach-o-builder.conf 1> mach-o-object.gen.o
```

## External sources
- [Get started](https://lowlevelbits.org/parsing-mach-o-files/)
- [loader.h](https://opensource.apple.com/source/cctools/cctools-795/include/mach-o/loader.h)
- [nlist.h](https://opensource.apple.com/source/xnu/xnu-201/EXTERNAL_HEADERS/mach-o/nlist.h)

## Devutils
- [Atom for plugin .conf files](https://atom.io/packages/language-generic-config)
