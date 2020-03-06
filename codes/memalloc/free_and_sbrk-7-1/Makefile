includes	= ../../../includes
lib			= ../../../lib/
objects		= free_and_sbrk.o
name		= free_and_sbrk
cc			= clang

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

