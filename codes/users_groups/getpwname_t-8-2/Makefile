includes	= ../../../includes
lib			= ../../../lib/
objects		= getpwnam_t.o
name		= getpwnam_t
cc			= clang -g

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -lcrypt -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

