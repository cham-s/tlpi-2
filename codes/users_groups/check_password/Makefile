includes	= ../../../includes
lib			= ../../../lib/
objects		= check_password.o
name		= check_password
cc			= clang -g

$(name): $(objects)
	$(cc) -I$(includes) $(objects) -L$(lib) -ltlpi -o $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $(lib) $<

.PHONY: clean

clean:
	rm *.o $(name)

