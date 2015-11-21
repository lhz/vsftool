# vsftool
Tool for working with VICE snapshot files

## Compiling

Simply run `make` to compile the source code into an executable file `vsftool`.

## Usage

`vsftool source.vsf target.vsf file1.prg [file2.prg file3.prg ...]`

This reads an existing snapshot `source.vsf` then stores it as a new snapshot `target.vsf`, after
modifying it by loading all given PRG files (with two-byte address headers) into the corresponding
area of the `C64MEM` block.
