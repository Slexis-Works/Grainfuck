# Makefile for the Grainfuck program

SHELL = /bin/sh
GCC = g++ -std=c++11

prefix = /usr/local
exec_prefix = $(prefix)
datarootdir = $(prefix)/share
mandir = $(datarootdir)/man

grainfuck: grainfuck.o
	$(GCC) grainfuck.o -o grainfuck -lsfml-graphics -lsfml-window -lsfml-system

grainfuck.o: main.cpp main.hpp Buffer.hpp errorCodes.hpp samples.hpp
	$(GCC) -c main.cpp -o grainfuck.o

debug:
	make clean
	make GCC="g++ -std=c++11 -Wall -Wextra -g"
	gdb grainfuck

clean:
	rm -f *.o
	rm -f ./grainfuck
.PHONY : clean

install: grainfuck
	@echo Checking man directory
	@test -d $(mandir) || (echo 'Manual directory not found. Ensure $(mandir) is the folder your local programs install their manpages in or use make mandir="/other/path" install.' && false)

	cp grainfuck $(exec_prefix)/bin/
	
	# Adding manual entries
	# Preparing folders
	mkdir -p $(mandir)/man1 $(mandir)/en/man1 $(mandir)/fr/man1
	# For tab to work and language fallback
	cp grainfuck-man-en.1 $(mandir)/man1/grainfuck.1
	# Locales
	cp grainfuck-man-en.1 $(mandir)/en/man1/grainfuck.1
	cp grainfuck-man-fr.1 $(mandir)/fr/man1/grainfuck.1
	@echo ""
	@echo "Successful installation! Try \`grainfuck --sample HelloWorld\` to test it."
.PHONY : install

uninstall:
	rm -fI $(exec_prefix)/bin/grainfuck $(mandir)/man1/grainfuck.1 $(mandir)/en/man1/grainfuck.1 $(mandir)/fr/man1/grainfuck.1
.PHONY : uninstall
