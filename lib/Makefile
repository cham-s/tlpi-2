objects		= error_functions.o get_num.o ugid_functions.o
cc     		= clang
includes	= ../includes
name		= libtlpi.a

$(name): $(objects)
	ar rc $(name) $(objects)
	ranlib $(name)

%.o: %.c
	$(cc) -c -o $@ -I$(includes) $<

.PHONY		: clean fclean re
clean:
	rm *.o

fclean: clean
	rm $(name)

re: fclean
