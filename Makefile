# "make test" Compiles everything and runs the regression tests

.PHONY : test
test : all testall.sh
	./testall.sh

# "make all" builds the executable as well as the "printbig" library designed
# to test linking external code

.PHONY : all
all : microc.native printbig.o pixel.o Album.o array2.o ImageStack.o psharplib.o 

# "make microc.native" compiles the compiler
#
# The _tags file controls the operation of ocamlbuild, e.g., by including
# packages, enabling warnings
#
# See https://github.com/ocaml/ocamlbuild/blob/master/manual/manual.adoc

microc.native :
	opam config exec -- \
	ocamlbuild -use-ocamlfind microc.native

# "make clean" removes all generated files

.PHONY : clean
clean :
	ocamlbuild -clean
	rm -rf outputs/*.jpg
	rm -rf testall.log ocamlllvm *.diff
	rm *.err *.ll *.exe *.s *.out *.o

# Testing the "printbig" example

printbig : printbig.c
	cc -o printbig -DBUILD_TEST printbig.c

psharplib: psharplib.c psharplib.h ImageStack.h pixel.h Album.h array.h
	cc -o psharplib -DBUILD_TEST psharplib.c

ImageStack: ImageStack.c ImageStack.h psharplib.h pixel.h
	cc -o ImageStack -DBUILD_TEST ImageStack.c

pixel: pixel.c pixel.h 
	cc -o pixel -DBUILD_TEST pixel.c

Album: Album.c ImageStack.h pixel.h
	cc -o Album -DBUILD_TEST Album.c

array: array2.c array2.h
	cc -o array -DBUILD_TEST array2.cpp

# Building the tarball

TESTS = \
  add1 arith1 arith2 arith3 fib float1 float2 float3 for1 for2 func1 \
  func2 func3 func4 func5 func6 func7 func8 func9 gcd2 gcd global1 \
  global2 global3 hello if1 if2 if3 if4 if5 if6 local1 local2 ops1 \
  ops2 printbig var1 var2 while1 while2

FAILS = \
  assign1 assign2 assign3 dead1 dead2 expr1 expr2 expr3 float1 float2 \
  for1 for2 for3 for4 for5 func1 func2 func3 func4 func5 func6 func7 \
  func8 func9 global1 global2 if1 if2 if3 nomain printbig printb print \
  return1 return2 while1 while2

TESTFILES = $(TESTS:%=test-%.mc) $(TESTS:%=test-%.out) \
	    $(FAILS:%=fail-%.mc) $(FAILS:%=fail-%.err)

TARFILES = ast.ml sast.ml codegen.ml Makefile _tags microc.ml microcparse.mly \
	README scanner.mll semant.ml testall.sh \
	printbig.c arcade-font.pbm font2c \
        psharplib.c \
        ImageStack.c \
        pixel.c \
        Album.c \
        array2.c \
	Dockerfile \
	$(TESTFILES:%=tests/%) 

microc.tar.gz : $(TARFILES)
	cd .. && tar czf microc/microc.tar.gz \
		$(TARFILES:%=microc/%)
