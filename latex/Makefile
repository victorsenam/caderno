notebook.pdf: builder.py head tail ../code/config
	python3 builder.py >notebook.tex
	latexmk --pdf notebook.tex

clean:
	rm notebook.*
