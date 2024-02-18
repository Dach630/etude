all: compile

compile:
	ocamlc partie2.ml
	ocamllex lexeur.mll
	ocamlc token.ml
	ocamlc lexeur.ml
	ocamlc Tree.ml
	ocamlc -o Interpreteur Interpreteur.ml
	ocamlc -o main lexeur.cmo token.cmo main.ml
	./main test.txt
	./Interpreteur

clean:
	rm *.cmo *.cmi
