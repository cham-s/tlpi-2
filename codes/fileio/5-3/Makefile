includes	= ../../../includes
lib			= ../../../lib/
objects		= atomic_append.o
name		= atomic_append
cc			= clang

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

