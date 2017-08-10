notebook.pdf: notebook.tex builder.out head tail config
	./builder.out
	pdflatex notebook.tex
	pdflatex notebook.tex

notebook.tex: builder.out

builder.out: builder.cpp head tail config
	cc builder.cpp -o builder.out

clean:
	rm notebook.* builder.out
