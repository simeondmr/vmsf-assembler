#include <stdio.h>
#include "../../include/parser/parser.h"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
		return 1;
	}
	init_parser(argv[1]);
	start(argv[2]);
	return 0;
}
