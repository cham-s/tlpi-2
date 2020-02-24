includes	= ../../../includes
lib			= ../../../lib/
objects		= seek_io.o
name		= seek_io
cc			= clang

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

