includes	= ../../../includes
lib			= ../../../lib/
objects		= longjmp.o
name		= longjmp
cc			= clang -g

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

