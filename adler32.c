#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

//#define __debug__
#define BUFFLEN		128
static int adler32(FILE *fp, uint32_t *result);

int main(int argc, char **argv)
{
	FILE *adler;
	uint32_t res;
	char buffer[BUFFLEN];

	if(argc != 2){
		fprintf(stderr, "please give a stream or file for input.\n");
		exit(EXIT_FAILURE);
	}

	adler = fopen(argv[1], "r");
	if(adler == NULL){
		snprintf(buffer, BUFFLEN, "%s", argv[1]);
		perror(buffer);
		exit(EXIT_FAILURE);
	}

	if(adler32(adler, &res) != 0){
		fprintf(stderr, "adler32 checksum failure.\n");
		exit(EXIT_FAILURE);
	}

	printf("adler32 checksum for %s is %#x\n", argv[1], res);
	return 0;
}

static int adler32(FILE *adler, uint32_t *result)
{
	int c;
	uint32_t A;
	uint32_t B;

	if(adler == NULL){
		fprintf(stderr, "invalid function parameter.\n");
		return -1;
	}

	A = 1;
	B = 0;

	while((c = fgetc(adler)) != EOF){
		#ifdef __debug__
		printf("c: %u\t\t\tA: %u\t\t\tB:%u\n", c, A, B);
		#endif
		A = (A + c) % 65521;
		B = (A + B) % 65521;
	}

	if(!feof(adler)){
		perror("[!] adler32 check failure");
		return -1;
	}

	*result = (B << 16) | A;
	return 0;
}

//0x4a3bfc25