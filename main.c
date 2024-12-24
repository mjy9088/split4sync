#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	if((argc != 4 || strcmp(argv[1], "split")) && (argc != 3 || strcmp(argv[1], "join")) && (argc != 2 || strcmp(argv[1], "help")))
	{
		printf("See '%s help'\n", argv[0]);
		return 1;
	}
	if(argc == 2)
	{
		printf("usage :"
			"\n\t%s help - this"
			"\n\t%s join filename - join spllitted files into stdout"
			"\n\t%s split filename size - split stdin to multiple files"
		"\n", argv[0], argv[0], argv[0]);
		return 0;
	}
	else if(argc == 3)
	{
		char filename[1024];
		char buffer[1024];
		char *tmp;
		size_t read;
		FILE *fp = fopen(argv[2], "rb");
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
			for(tmp = filename; *tmp; tmp++)
			{
				if(*tmp == '\n')
				{
					*tmp = '\0';
					break;
				}
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
		if(strlen(argv[3]) > 15)
		{
			fprintf(stderr, "File size is too long : %s\n", argv[3]);
			return 2;
		}
		uint64_t filesize = 0;
		char *tmp;
		for(tmp = argv[3]; *tmp; tmp++)
		{
			if(*tmp < '0' || *tmp > '9')
			{
				fprintf(stderr, "File size %s is not valid number\n", argv[3]);
				return 3;
			}
			filesize = filesize * 10 + (unsigned)(*tmp - '0');
		}
		char filename[1024];
		char buffer[1024];
		uint64_t remain = filesize;
		size_t file_seq = 0, read;
		FILE *fp = fopen(argv[2], "w");
		if(!fp)
		{
			fprintf(stderr, "Failed to open file : %s\n", argv[2]);
			return -8;
		}
		sprintf(filename, "%s.%zu", argv[2], file_seq);
		fprintf(fp, "%s", filename);
		if(ferror(fp))
		{
			fclose(fp);
			fputs("Error writing file list", stderr);
			return -9;
		}
		FILE *f = fopen(filename, "wb");
		if(!f)
		{
			fprintf(stderr, "Failed to open file : %s\n", filename);
			return -10;
		}
		while(!feof(stdin))
		{
			if(!remain)
			{
				fclose(f);
				sprintf(filename, "%s.%zu", argv[2], ++file_seq);
				fprintf(fp, "\n%s", filename);
				if(ferror(fp))
				{
					fclose(fp);
					fputs("Error writing file list", stderr);
					return -9;
				}
				f = fopen(filename, "wb");
				if(!f)
				{
					fprintf(stderr, "Failed to open file : %s\n", filename);
					return -10;
				}
				remain = filesize;
			}
			read = fread(buffer, sizeof(char), remain < 1024 ? remain : 1024, stdin);
			if(ferror(stdin))
			{
				fclose(fp);
				fclose(f);
				fputs("Error reading stdin", stderr);
				return -11;
			}
			if(fwrite(buffer, sizeof(char), read, f) != read || ferror(f))
			{
				fclose(fp);
				fclose(f);
				fputs("Error writing file", stderr);
				return -12;
			}
			remain -= read;
		}
		fclose(fp);
		fclose(f);
		if(ferror(stdin))
		{
			fputs("Error reading stdin", stderr);
			return -13;
		}
		return 0;
	}
}

