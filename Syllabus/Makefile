FILE ?= default

all: compile move

compile:
	pdflatex $(FILE).tex

move:
	mkdir -p $(FILE)
	mv $(FILE).aux $(FILE).log $(FILE).out $(FILE)/

clean:
	rm -rf $(FILE) $(FILE).pdf