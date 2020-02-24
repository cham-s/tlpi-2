includes	= ../../../includes
lib			= ../../../lib/
objects		= t_readv.o
name		= t_readv
cc			= clang

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

