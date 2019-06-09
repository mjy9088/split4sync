#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if((argc != 4 || strcmp(argv[1], "split")) && (argc != 3 || strcmp(argv[1], "join")))
	{
		printf("usage :\n\t%s join filename - join spllitted files into stdout\n\t%s split filename size - split stdin to multiple files\n", argv[0], argv[0]);
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

