#
# Makefile C++ webdev
#
# F.Morgner
#

TEXFILES = aboutme.tex \
					 webdevme.tex \
					 cpp.tex


frontg8.pdf: slides.tex $(TEXFILES)
	latexmk -pdf -deps -pdflatex="pdflatex -interactive=nonstopmode" -use-make slides.tex
	latexmk -c

clean:
	latexmk -C
