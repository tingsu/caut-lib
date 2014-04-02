# This Makefile creates sqlite3 library related files.
# Sqlite3 version : 3.7.7.1 (sqlite3.c/sqlite3.h) Ocaml-sqlite3 binding version : 1.6.1 (sqlite3.ml, sqlite3.mli ,sqlite3_stubs.c)
# Copyright (c) 2011 Krave Su <suting1989@gmail.com>

OCAML_BYTECODE_COMPILER = ocamlc
OCAML_NATIVECODE_COMPILER = ocamlopt
OCAML_LIBER = ocamlmklib
CC=gcc -fPIC

all: obj_file lib_file sqlite3.cmi sqlite3.cmo sqlite3.cmx sqlite3.cma sqlite3.cmxa

lib_file : sqlite3.o sqlite3_stubs.o
	$(OCAML_LIBER) -o sqlite3 $^

sqlite3.cma : sqlite3.cmo
	$(OCAML_LIBER) -o sqlite3 $< 

sqlite3.cmxa : sqlite3.cmx
	$(OCAML_LIBER) -o sqlite3 $< 
	
sqlite3.cmo : sqlite3.ml
	$(OCAML_BYTECODE_COMPILER) -c $<
	
sqlite3.cmi : sqlite3.mli
	$(OCAML_BYTECODE_COMPILER) -c $<
	
sqlite3.cmx : sqlite3.ml
	$(OCAML_NATIVECODE_COMPILER) -c $<

obj_file : sqlite3_stubs.c sqlite3.c
#	$(OCAML_BYTECODE_COMPILER) -c $^
	$(CC) -c $^

install	:
	cp sqlite3.cmo sqlite3.cmi sqlite3.cmx sqlite3.mli sqlite3.cma sqlite3.cmxa libsqlite3.a dllsqlite3.so sqlite3.a /usr/lib/ocaml

clean :
	rm -rf *.cm[oiax] *.cmxa *.o *.so *.a 
