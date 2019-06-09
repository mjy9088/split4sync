#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if(argc != 3 && (argc != 2 || strcmp(argv[1], "join")))
	{
		printf("usage :\n\t%s join - join spllitted files into stdout\n\t%s split - split stdin to multiple files\n", argv[0], argv[0]);
		return 1;
	}
	if(argc == 3)
	{
		fputs("WIP", stderr);
		return 0;
	}
	else
	{
		fputs("WIP", stderr);
		return 0;
	}
}

