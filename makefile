.PHONY :  clean help %.out docs
.ONESHELL: # Applies to every targets in the file!

all: test

## make help : show this message.
help :
	@grep -h -E '^##' ${MAKEFILE_LIST} | sed -e 's/## //g' \
		| column -t -s ':'

## make test : test all files
test:
	make clean
	for i in $$(ls *.c);do
		make $$(basename $$i .c).ihx
	done
	make clean

%.out: %.ihx
	stcgal -P stc89 $<

## make *.ihx : generate the ihx files
# https://askubuntu.com/a/522776
%.ihx: %.c
	sdcc $<
## doxygen: generate doxygen docs
doxygen:
	cd docs
	doxygen

## sphinx_html: generate sphinx docs
sphinx_html: doxygen
	cd docs
	make html

## sphinx_pdf: generate sphinx docs using latex
sphinx_pdf: doxygen
	cd docs
	make latexpdf

## doxygen_pdf: generate the docs pdf using doxygen
doxygen_pdf: doxygen
	cd docs/build/doxygen_latex
	make all

## make clean: clean the temp files
clean:
	# git ls-files --others | xargs gio trash
	git clean -fXd
