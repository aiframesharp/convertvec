// Code to convert word2vec vectors between text and binary format
// Created by Marek Rei
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>

const long long max_w = 2000;


// Convert from binary to text format
 void bin2txt(const char * input_path, const char * output_path){
	
	FILE* fi = fopen(input_path, "rb");
	FILE* fo = fopen(output_path, "wb");

	long long words, size;
	fscanf(fi, "%lld", &words);
	fscanf(fi, "%lld", &size);
	fscanf(fi, "%*[ ]");
	fscanf(fi, "%*[\n]");

	fprintf(fo, "%lld %lld\n", words, size);

	char word[max_w];
	char ch;
	float value;
	int b, a;
	for (b = 0; b < words; b++) {
		if (feof(fi))
			break;

		word[0] = 0;
		fscanf(fi, "%[^ ]", word);
		fscanf(fi, "%c", &ch);

		fprintf(fo, "%s ", word);
		for (a = 0; a < size; a++) {
			fread(&value, sizeof(float), 1, fi);
			fprintf(fo, "%lf ", value);
		}
		fscanf(fi, "%*[\n]");
		fprintf(fo, "\n");
	}
	fclose(fi);
	fclose(fo);
}

int main(int argc, char **argv) {

	const char* inp = "input.bin";
	const char* out = "outp.txt";
	bin2txt(inp,out);

	return 0;
}
