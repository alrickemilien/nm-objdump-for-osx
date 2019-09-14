# nm - objdump for OSX

Rewrite the tools nm and otool that you can find on OSX.
These provides the same functionnalities as objdump on Linux softwares.

This project provides three binaries :
```bash
# This program read mach o files
./build/ft_nm
```
```bash
# This program displays segment text of mach o files
./build/ft_otool
```
```bash
# This program generate a mach o file from a config
./build/mach-o-builder mach-o-builder.conf 1> mach-o-object.gen.o
```

## Test
Requires **ruby >= 2.3.7** and **unit-test gem**

### Advice: use rbenv
Install rbenv as following
```
brew install rbenv ruby-build

# Suggest you to use goinfre
export PATH_TO_RBENV=/path/to/rbenv

# bash
echo 'export PATH="$PATH_TO_RBENV:$PATH"' >> ~/.bash_profile
echo 'eval "$(rbenv init -)"' >> ~/.bash_profile  

# zsh
echo 'export PATH="$PATH_TO_RBENV:$PATH"' >> ~/.zprofile
echo 'eval "$(rbenv init -)"' >> ~/.zprofile  

# list all available versions:
rbenv install -l

# install a Ruby version:
rbenv install 2.3.7

# set ruby version for a specific dir
rbenv local 2.3.7

# set ruby version globally
rbenv global 2.3.7

rbenv rehash
```

**Reopen** the terminal.
Check the location where gems are being installed with gem env:
```
$ gem env home
# => $PATH_TO_RBENV/versions/<ruby-version>/lib/ruby/gems/...
```
Install unit-test with `gem install unit-test`.
And then run `ruby test/[nm|otool].rb`.

## External sources
- [Get started](https://lowlevelbits.org/parsing-mach-o-files/)
- [loader.h](https://opensource.apple.com/source/cctools/cctools-795/include/mach-o/loader.h)
- [nlist.h](https://opensource.apple.com/source/xnu/xnu-201/EXTERNAL_HEADERS/mach-o/nlist.h)
- [Must have => MachOView](https://sourceforge.net/projects/machoview/)
