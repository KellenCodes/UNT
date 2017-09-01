start: main.cpp graphs.cpp
	g++ main.cpp graphs.cpp -o NCubedRace2017

run: NCubedRace2017
	./NCubedRace2017

zip: main.cpp graphs.cpp algoRACE.h makefile README
	zip mkm0222 main.cpp graphs.cpp algoRACE.h makefile README

submit: mkm0222.zip
	project submit 4110s001 sp17proj -force mkm0222.zip

view:
	project view 4110s001 sp17proj

clean:
	rm mkm0222.zip; rm NCubedRace2017
