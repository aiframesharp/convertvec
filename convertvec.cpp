// Code to convert word2vec vectors between text and binary format
// Created by Marek Rei

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>

const long long max_w = 2000;

// Convert from text format to binary
void txt2bin(char * input_path, char * output_path){
	FILE** fi = 0;
	fopen_s(fi, input_path, "rb");
	FILE** fo = 0;
	fopen_s(fo, output_path, "wb");

	long long words, size;
	fscanf_s(*fi, "%lld", &words);
	fscanf_s(*fi, "%lld", &size);
	fscanf_s(*fi, "%*[ ]");
	fscanf_s(*fi, "%*[\n]");

	fprintf(*fo, "%lld %lld\n", words, size);

	char word[max_w];
	char ch;
	float value;
	int b, a;
	for (b = 0; b < words; b++) {
		if(feof(*fi))
			break;

		word[0] = 0;
		fscanf_s(*fi, "%[^ ]", word);
		fscanf_s(*fi, "%c", &ch);
		// This kind of whitespace handling is a bit more explicit than usual.
		// It allows us to correctly handle special characters that would otherwise be skipped.

		fprintf_s(*fo, "%s ", word);

		for (a = 0; a < size; a++) {
			fscanf_s(*fi, "%s", word);
			fscanf_s(*fi, "%*[ ]");
			value = atof(word);
			fwrite(&value, sizeof(float), 1, *fo);
		}
		fscanf_s(*fi, "%*[\n]");
		fprintf_s(*fo, "\n");
	}
	
	fclose(*fi);
	fclose(*fo);
}

// Convert from binary to text format
void bin2txt(char * input_path, char * output_path){
	FILE** fi = 0;
	fopen_s(fi, input_path, "rb");
	FILE** fo = 0;
	fopen_s(fo, output_path, "wb");
	
	long long words, size;
	fscanf_s(*fi, "%lld", &words);
	fscanf_s(*fi, "%lld", &size);
	fscanf_s(*fi, "%*[ ]");
	fscanf_s(*fi, "%*[\n]");

	fprintf_s(*fo, "%lld %lld\n", words, size);

	char word[max_w];
	char ch;
	float value;
	int b, a;
	for (b = 0; b < words; b++) {
		if(feof(*fi))
			break;

		word[0] = 0;
		fscanf_s(*fi, "%[^ ]", word);
		fscanf_s(*fi, "%c", &ch);
		
		fprintf(*fo, "%s ", word);
		for (a = 0; a < size; a++) {
			fread(&value, sizeof(float), 1, *fi);
			fprintf(*fo, "%lf ", value);
		}
		fscanf_s(*fi, "%*[\n]");
		fprintf_s(*fo, "\n");
	}
	fclose(*fi);
	fclose(*fo);
}

int main(int argc, char **argv) {
	if (argc < 4) {
		printf("USAGE: convertvec method input_path output_path\n");
		printf("Method is either bin2txt or txt2bin\n");
		return 0;
	}
	
	if(strcmp(argv[1], "bin2txt") == 0)
		bin2txt(argv[2], argv[3]);
	else if(strcmp(argv[1], "txt2bin") == 0)
		txt2bin(argv[2], argv[3]);
	else
		printf("Unknown method: %s\n", argv[1]);

	return 0;
}
