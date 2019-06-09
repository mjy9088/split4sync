#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	if((argc != 4 || strcmp(argv[1], "split")) && (argc != 3 || strcmp(argv[1], "join")))
	{
		printf("usage :\n\t%s join filename - join spllitted files into stdout\n\t%s split filename size - split stdin to multiple files\n", argv[0], argv[0]);
		return 1;
	}
	char filename[1024];
	char buffer[1024];
	int read;
	if(argc == 3)
	{
		FILE *fp = fopen(argv[2], "r");
		if(!fp)
		{
			fprintf(stderr, "Failed to open file : %s\n", argv[2]);
			return -1;
		}
		while(fgets(filename, 1024, fp))
		{
			if(ferror(fp))
			{
				fclose(fp);
				fputs("Error reading file list", stderr);
				return -2;
			}
			FILE *f = fopen(filename, "rb");
			if(!f)
			{
				fprintf(stderr, "Failed to open file : %s\n", filename);
				return -3;
			}
			while(!feof(f))
			{
				read = fread(buffer, sizeof(char), 1024, f);
				if(ferror(f))
				{
					fclose(fp);
					fclose(f);
					fputs("Error reading file", stderr);
					return -4;
				}
				if(fwrite(buffer, sizeof(char), read, stdout) != read || ferror(f))
				{
					fclose(fp);
					fclose(f);
					fputs("Error writing file", stderr);
					return -5;
				}
			}
			if(ferror(f))
			{
				fclose(fp);
				fclose(f);
				fputs("Error reading file", stderr);
				return -6;
			}
			fclose(f);
		}
		if(ferror(fp))
		{
			fclose(fp);
			fputs("Error reading file list", stderr);
			return -7;
		}
		fclose(fp);
		return 0;
	}
	else
	{
		fputs("WIP", stderr);
		return 0;
	}
}

