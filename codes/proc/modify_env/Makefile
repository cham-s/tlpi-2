includes	= ../../../includes
lib			= ../../../lib/
objects		= modify_env.o
name		= modify_env
cc			= clang

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

