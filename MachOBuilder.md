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
