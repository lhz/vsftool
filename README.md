# vsftool
Tool for working with snapshot files created by `x64` or `x64sc` from the [VICE emulator project](http://vice-emu.sourceforge.net/).

## Compiling

Simply run `make` to compile the source code into an executable file `vsftool`.

## Usage

`vsftool source.vsf target.vsf file1.prg [file2.prg file3.prg ...]`

This reads an existing snapshot file `source.vsf`, then stores it to a new file `target.vsf` after
modifying it by loading all given PRG files (with two-byte address headers) into the corresponding
area of the `C64MEM` block.
