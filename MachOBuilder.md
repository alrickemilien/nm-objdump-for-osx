# MachOBuilder Configuration file Reference

<!-- toc -->

- [MachOBuilder](#MachOBuilder)
  - [`[GLOBAL_CONFIGURATION]`](#GLOBAL_CONFIGURATION)
  - [`[HEADER]`](#HEADER)
    - [magic_number](#magic_number)
    - [cputype](#cputype)
    - [cpusubtype](#cpusubtype)
    - [filetype](#filetype)
    - [ncmds](#ncmds)
    - [sizeofcmds](#sizeofcmds)
    - [flags](#flags)
    - [reserved](#reserved)
  - [`[FAT_HEADER]`](#FAT_HEADER)
  - [`[LOAD_COMMAND]`](#LOAD_COMMAND)
  - [`[SECTION_COMMAND]`](#SECTION_COMMAND)
  - [`[FAT_ARCH]`](#FAT_ARCH)
  - [`[SEGMENT_COMMAND]`](#SEGMENT_COMMAND)
  - [`[SYMTAB_COMMAND]`](#SYMTAB_COMMAND)
  - [`[DATA_SECTION]`](#DATA_SECTION)

<!-- tocstop -->

## MachOBuilder

## `[GLOBAL_CONFIGURATION]`

Set the global configuration to set

## `[HEADER]`

Set the header of the file

### `uint32_t` `magic_number`

Possible valid values :

|  |  |
|---|---|
| MH_MAGIC_64 | 0xfeedfacf |
| MH_CIGAM_64 | 0xcffaedfe |

```conf
magic_number=0xff
```

### `uint32_t` `cputype`

Possible valid values :

|  |  |
|---|---|
| CPU_TYPE_ANY | ((cpu_type_t) -1) |
| CPU_TYPE_VAX | ((cpu_type_t) 1) |
| CPU_TYPE_MC680x0 | ((cpu_type_t) 6) |
| CPU_TYPE_X86 | ((cpu_type_t) 7) |
| CPU_TYPE_I386 | (CPU_TYPE_X86 | CPU_ARCH_ABI64) |
| CPU_TYPE_X86_64 | ((cpu_type_t) 10) |
| CPU_TYPE_MC98000 | ((cpu_type_t) 11) |
| CPU_TYPE_HPPA | ((cpu_type_t) 12) |
| CPU_TYPE_ARM | ((cpu_type_t) 13) |
| CPU_TYPE_ARM64 | ((cpu_type_t) 14) |
| CPU_TYPE_MC88000 | ((cpu_type_t) 15) |
| CPU_TYPE_SPARC | ((cpu_type_t) 16) |
| CPU_TYPE_I860 | ((cpu_type_t) 18) |
| CPU_TYPE_ALPHA | (CPU_TYPE_POWERPC | CPU_ARCH_ABI64) |
| CPU_TYPE_POWERPC |  |
| CPU_TYPE_POWERPC64 |  |

```conf
cputype=0xD
```

### `cpusubtype`

### `filetype`

### `ncmds`

### `sizeofcmds`

### `flags`

### `reserved`

### example
```bash
#
# Header
#

[HEADER]

# Magic number
# uint32_t
# Possible valid values :
# 0xfeedfacf // MH_MAGIC_64
# 0xcffaedfe // MH_CIGAM_64
magic_number=0xcffaedfe

# cputype number
# uint32_t
#    Machine types known by all.
#define CPU_TYPE_ANY            ((cpu_type_t) -1)
#define CPU_TYPE_VAX            ((cpu_type_t) 1)
#define CPU_TYPE_MC680x0        ((cpu_type_t) 6)
#define CPU_TYPE_X86            ((cpu_type_t) 7)
#define CPU_TYPE_I386           CPU_TYPE_X86            /* compatibility */
#define CPU_TYPE_X86_64         (CPU_TYPE_X86 | CPU_ARCH_ABI64)
#define CPU_TYPE_MC98000        ((cpu_type_t) 10)
#define CPU_TYPE_HPPA           ((cpu_type_t) 11)
#define CPU_TYPE_ARM            ((cpu_type_t) 12)
#define CPU_TYPE_ARM64          (CPU_TYPE_ARM | CPU_ARCH_ABI64)
#define CPU_TYPE_MC88000        ((cpu_type_t) 13)
#define CPU_TYPE_SPARC          ((cpu_type_t) 14)
#define CPU_TYPE_I860           ((cpu_type_t) 15)
#define CPU_TYPE_ALPHA          ((cpu_type_t) 16)
#define CPU_TYPE_POWERPC                ((cpu_type_t) 18)
#define CPU_TYPE_POWERPC64              (CPU_TYPE_POWERPC | CPU_ARCH_ABI64)
cputype=0x7

# cpusubtype
# uint32_t
#define CPU_SUBTYPE_MULTIPLE            ((cpu_subtype_t) -1)
#define CPU_SUBTYPE_LITTLE_ENDIAN       ((cpu_subtype_t) 0)
#define CPU_SUBTYPE_BIG_ENDIAN          ((cpu_subtype_t) 1)
#define CPU_SUBTYPE_X86_ALL             ((cpu_subtype_t)3)
#define CPU_SUBTYPE_X86_64_ALL          ((cpu_subtype_t)3)
#define CPU_SUBTYPE_X86_ARCH1           ((cpu_subtype_t)4)
#define CPU_SUBTYPE_X86_64_H            ((cpu_subtype_t)8)      /* Haswell feature subset */
cpusubtype=0xFFFFFFFF

# Filetype
# uint32_t
# Possible valid values :
#define MH_OBJECT       0x1
#define MH_EXECUTE      0x2
#define MH_FVMLIB       0x3
#define MH_CORE         0x4
#define MH_PRELOAD      0x5
#define MH_DYLIB        0x6
#define MH_DYLINKER     0x7
#define MH_BUNDLE       0x8
#define MH_DYLIB_STUB   0x9
#define MH_DSYM         0xa
#define MH_KEXT_BUNDLE  0xb
#define MH_NOUNDEFS     0x1
#define MH_INCRLINK     0x2
#define MH_DYLDLINK     0x4
#define MH_BINDATLOAD   0x8
#define MH_PREBOUND     0x10
#define MH_SPLIT_SEGS   0x20
#define MH_LAZY_INIT    0x40
#define MH_TWOLEVEL     0x80
#define MH_FORCE_FLAT   0x100
#define MH_NOMULTIDEFS  0x200
#define MH_NOFIXPREBINDING 0x400
#define MH_PREBINDABLE  0x800
#define MH_ALLMODSBOUND 0x1000
#define MH_SUBSECTIONS_VIA_SYMBOLS 0x2000
#define MH_CANONICAL    0x4000
#define MH_WEAK_DEFINES 0x8000
#define MH_BINDS_TO_WEAK 0x10000
#define MH_ALLOW_STACK_EXECUTION 0x20000
#define MH_ROOT_SAFE 0x40000
#define MH_SETUID_SAFE 0x80000
#define MH_NO_REEXPORTED_DYLIBS 0x100000
#define MH_PIE 0x200000
#define MH_DEAD_STRIPPABLE_DYLIB 0x400000
#define MH_HAS_TLV_DESCRIPTORS 0x800000
#define MH_NO_HEAP_EXECUTION 0x1000000
#define MH_APP_EXTENSION_SAFE 0x02000000
filetype=0x1

# number of load commands
# uint32_t
ncmds=0x1

# The size of all the load commands
# uint32_t
sizeofcmds=0xFF

# Magic number
# uint32_t
# Possible valid values :
#define MH_NOUNDEFS     0x1
#define MH_INCRLINK     0x2
#define MH_DYLDLINK     0x4
#define MH_BINDATLOAD   0x8
#define MH_PREBOUND     0x10
#define MH_SPLIT_SEGS   0x20
#define MH_LAZY_INIT    0x40
#define MH_TWOLEVEL     0x80
#define MH_FORCE_FLAT   0x100
#define MH_NOMULTIDEFS  0x200
#define MH_NOFIXPREBINDING 0x400
#define MH_PREBINDABLE  0x800
#define MH_ALLMODSBOUND 0x1000
#define MH_SUBSECTIONS_VIA_SYMBOLS 0x2000
#define MH_CANONICAL    0x4000
#define MH_WEAK_DEFINES 0x8000
#define MH_BINDS_TO_WEAK 0x10000
#define MH_ALLOW_STACK_EXECUTION 0x20000
#define MH_ROOT_SAFE 0x40000
#define MH_SETUID_SAFE 0x80000
#define MH_NO_REEXPORTED_DYLIBS 0x100000
#define MH_PIE 0x200000
#define MH_DEAD_STRIPPABLE_DYLIB 0x400000
#define MH_HAS_TLV_DESCRIPTORS 0x800000
#define MH_NO_HEAP_EXECUTION 0x1000000
#define MH_APP_EXTENSION_SAFE 0x02000000
flags=0x1

# reserved
# uint32_t
reserved=0x8

#
# Load command
#

[LOAD_COMMAND]

# Possible valid values :
#define LC_SEGMENT      0x1     /* segment of this file to be mapped */
#define LC_SYMTAB       0x2     /* link-edit stab symbol table info */
#define LC_SYMSEG       0x3     /* link-edit gdb symbol table info (obsolete) */
#define LC_THREAD       0x4     /* thread */
#define LC_UNIXTHREAD   0x5     /* unix thread (includes a stack) */
#define LC_LOADFVMLIB   0x6     /* load a specified fixed VM shared library */
#define LC_IDFVMLIB     0x7     /* fixed VM shared library identification */
#define LC_IDENT        0x8     /* object identification info (obsolete) */
#define LC_FVMFILE      0x9     /* fixed VM file inclusion (internal use) */
#define LC_PREPAGE      0xa     /* prepage command (internal use) */
#define LC_DYSYMTAB     0xb     /* dynamic link-edit symbol table info */
#define LC_LOAD_DYLIB   0xc     /* load a dynamically linked shared library */
#define LC_ID_DYLIB     0xd     /* dynamically linked shared lib ident */
#define LC_LOAD_DYLINKER 0xe    /* load a dynamic linker */
#define LC_ID_DYLINKER  0xf     /* dynamic linker identification */
#define LC_PREBOUND_DYLIB 0x10  /* modules prebound for a dynamically */
#define LC_ROUTINES     0x11    /* image routines */
#define LC_SUB_FRAMEWORK 0x12   /* sub framework */
#define LC_SUB_UMBRELLA 0x13    /* sub umbrella */
#define LC_SUB_CLIENT   0x14    /* sub client */
#define LC_SUB_LIBRARY  0x15    /* sub library */
#define LC_TWOLEVEL_HINTS 0x16  /* two-level namespace lookup hints */
#define LC_PREBIND_CKSUM  0x17  /* prebind checksum */
cmd=0x88

#
# The cmdsize for 32-bit architectures
# The cmdsize for 32-bit architectures MUST be a multiple of 4 bytes
# and for 64-bit architectures MUST be a multiple of 8 bytes
# (these are forever the maximum alignment of any load commands).
#
cmdsize=0x96

section_architecture=0x64

# struct symtab_command {
#         uint32_t        cmd;            // LC_SYMTAB
#         uint32_t        cmdsize;        // sizeof(struct symtab_command)
#         uint32_t        symoff;         // symbol table offset
#         uint32_t        nsyms;          // number of symbol table entries
#         uint32_t        stroff;         // string table offset
#         uint32_t        strsize;        // string table size in bytes
# };
[SYMTAB_COMMAND]
cmd=0x2
cmdsize=0xC0
symoff=0xDFDF
nsyms=0x1
stroff=0xFF
strsize=0xDD

[SECTION_COMMAND]

#
# Section
#
# struct section { /* for 32-bit architectures */
#         char            sectname[16];   /* name of this section */
#         char            segname[16];    /* segment this section goes in */
#         uint32_t        addr;           /* memory address of this section */
#         uint32_t        size;           /* size in bytes of this section */
#         uint32_t        offset;         /* file offset of this section */
#         uint32_t        align;          /* section alignment (power of 2) */
#         uint32_t        reloff;         /* file offset of relocation entries */
#         uint32_t        nreloc;         /* number of relocation entries */
#         uint32_t        flags;          /* flags (section type and attributes)*/
#         uint32_t        reserved1;      /* reserved (for offset or index) */
#         uint32_t        reserved2;      /* reserved (for count or sizeof) */
# };
#
# struct section_64 { /* for 64-bit architectures */
#         char            sectname[16];   /* name of this section */
#         char            segname[16];    /* segment this section goes in */
#         uint64_t        addr;           /* memory address of this section */
#         uint64_t        size;           /* size in bytes of this section */
#         uint32_t        offset;         /* file offset of this section */
#         uint32_t        align;          /* section alignment (power of 2) */
#         uint32_t        reloff;         /* file offset of relocation entries */
#         uint32_t        nreloc;         /* number of relocation entries */
#         uint32_t        flags;          /* flags (section type and attributes)*/
#         uint32_t        reserved1;      /* reserved (for offset or index) */
#         uint32_t        reserved2;      /* reserved (for count or sizeof) */
#         uint32_t        reserved3;      /* reserved */
# };

#
# x64 bits values for strcuture
#

# name of this section
# It is a 16 bytes length string, you can put enpty or greater 16 bytes to
# trash garbage file
sectname[16]=

# segment this section goes in
# It is a 16 bytes length string, you can put empty or greater 16 bytes to
# trash garbage file
segname[16]=

# uint32_t
# memory address of this section
addr = 0x738

# uint32_t
# size in bytes of this section
size = 0xFF

# uint32_t
# file offset of this section
offset = 0x5465464

# uint32_t
# section alignment (power of 2)
align = 0x5465464

# uint32_t
# file offset of relocation entries
reloff = 0x5465464

# uint32_t
# number of relocation entries
nreloc = 0x5465464

# uint32_t
# flags (section type and attributes)
flags = 0x1

# uint32_t
# reserved (for offset or index)
reserved1 = 0x0

# uint32_t
# reserved (for count or sizeof)
reserved2 = 0x0

# data to fill the pointed section
data=0x0
```
