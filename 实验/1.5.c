#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE *source, *target;
	char const *source_file;
	char const *target_file;
	char ch;

	source_file = argv[1];
	target_file = argv[2];

	source = fopen(source_file, "r");

	if (source == NULL)
	{
		printf("the source is NULL\n");
		return 0;
	}

	target = fopen(target_file, "w");
	while((ch = fgetc(source)) != EOF) {
		fputc(ch, target);
	}
	fclose(source);
	fclose(target);

	return 0;
}
