schedule.pdf: schedule.tex
	TEXINPUTS=.:`pwd`/TeX/dirtree:${TEXINPUTS:-:}&&export TEXINPUTS&&pdflatex $^
	TEXINPUTS=.:`pwd`/TeX/dirtree:${TEXINPUTS:-:}&&export TEXINPUTS&&pdflatex $^

show:
	TEXINPUTS=.:`pwd`/TeX/dirtree:${TEXINPUTS:-:}&&export TEXINPUTS&&pdflatex schedule.tex
	TEXINPUTS=.:`pwd`/TeX/dirtree:${TEXINPUTS:-:}&&export TEXINPUTS&&pdflatex schedule.tex
	evince schedule.pdf &

clean:
	rm schedule.pdf
	rm schedule.log
	rm schedule.aux
