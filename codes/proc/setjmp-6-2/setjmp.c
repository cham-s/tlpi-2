#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf env;

void f1()
{
	if (setjmp(env) == 0)
		printf("setting the first jump mark\n");
	else
		printf("what happened when a long jump is called after the function returns?\n");
}

void f2()
{
	longjmp(env, 1);
}

int
main(int argc, char *argv[])
{
	f1();
	f2();
	exit(EXIT_SUCCESS);
}
