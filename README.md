# Grainfuck — The Graphical Brainfuck Interpreter
> Parce qu'il faut avoir un __grain__ pour en faire.

## Description
This program delivers a vanilla [brainfuck](https://en.wikipedia.org/wiki/Brainfuck "Wikipedia page of this language") interpreter enhanced with a ninth command merely painting a pixel on the screen.

## Licence
As it's basically useless, it's released under the GPL v3.0 because cutting edge.

## Help
The program is bundled with an English and a French manpages. Proper installation should enable you to get help with `grainfuck --help` or `grainfuck -h` or `man grainfuck`. But because I'm a lazy guy, there's no configuration so you better have a system following the same rules as mine.
To build the program, clone this repository or get the newest zip and extract the files. Then go to your newly created foler and run `make`. It requires the SFML's 2.* developpement package and `g++` installed. Then a `(sudo) make install` will complete the work. After that, your `grainfuck` commnd should be available.
