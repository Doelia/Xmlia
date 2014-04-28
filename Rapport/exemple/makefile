all: refman listing
	pdflatex compte-rendu.tex && pdflatex compte-rendu.tex

listing:
	./extracteur-implementation.py

refman: doc
	./extracteur-refman.py

doc: doc-update
	cd .. && doxygen doc && cd rapport

doc-update:
	cd .. && doxygen -u doc && cd rapport

clean: doc-clean refman-clean listing-clean
	rm *.aux *.log *.toc *.out *.pdf *.fdb_latexmk

doc-clean:
	rm -Rf latex html

refman-clean:
	rm manuel-de-reference.tex

listing-clean:
	rm listing.tex
