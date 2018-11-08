# nm - objdump for OSX

Rewrite the tools nm and otool that you can find on OSX.
These provides the same functionnalities as objdump on Linux softwares.

This project provides two binaries :
```bash
./nm # This program read mach o files
```
```bash
./otool # This program displays segment text of mach o files
```
## External sources
- [Get started](https://lowlevelbits.org/parsing-mach-o-files/)
- [loader.h](https://opensource.apple.com/source/cctools/cctools-795/include/mach-o/loader.h)
- [nlist.h](https://opensource.apple.com/source/xnu/xnu-201/EXTERNAL_HEADERS/mach-o/nlist.h)
