.PHONY: refresh

refresh:

notebook.pdf: builder.py head tail ../code/config hashify.py refresh
	python3 builder.py >notebook.tex
	latexmk --pdf notebook.tex

clean:
	rm notebook.*
