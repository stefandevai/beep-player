#include <stdio.h>
#include <stdlib.h>

#include "note_defs.h"

int get_note(const char* line);
int get_duration(const char* line);

int main(int argc, char *argv[])
{
	FILE *fb, *fs;
	char ch;
	const char* sn_path = "internationale.sn";

	fs = fopen(sn_path, "r");
	if (fs == NULL) {
		// TODO: Deal with not existing source files
		printf("It was not possible to open %s\n", sn_path);
		return -1;
	}

	fb = fopen("internationale2.bn", "wb");
	if (fb == NULL) {
		// TODO: Deal with not opening destination file
		printf("It was not possible to open destination file\n");
		fclose(fs);
		return -1;
	}

	char *line;
	size_t len = 0;
	ssize_t read;
	while((read = getline(&line, &len, fs)) != -1)
	{
		int note, duration;
		note = get_note(line);
		duration = get_duration(line);

		note = note == 0 ? 0 : 1193180/note;
		int arg = (duration<<16) | note;
		fwrite(&arg, sizeof(arg), 1, fb);
		
		/*printf("%d Hz, %d ms\n", note, duration);*/
	}

	if (line)
		free(line);

	int end = 0;
	fwrite(&end, sizeof(end), 1, fb);
	fclose(fb);
	fclose(fs);
	/*if (fb != NULL) {*/
		/*fwrite(&arg, sizeof(arg), 1, fb);*/
	/*}*/
	/*FILE *fb = fopen("file.sb", "wb");*/
	/*if (fb != NULL) {*/
		/*int note = A3;*/
		/*int duration = CROTCHET;*/

		/*fwrite(&note, sizeof(note), 1, fb);*/
		/*fwrite(&duration, sizeof(duration), 1, fb);*/
		/*fclose(fb);*/
	/*}*/
	return 0;
}

int get_note(const char* line) {
	switch(line[0]) {
		case 'A':
			switch(line[1]) {
				case '3':
					return A3;
					break;
				case '4':
					return A4;
					break;
				case '5':
					return A5;
					break;
				case '6':
					return A6;
					break;
			}
			break;
		case 'B':
			switch(line[1]) {
				case '3':
					return B3;
					break;
				case '4':
					return B4;
					break;
				case '5':
					return B5;
					break;
				case '6':
					return B6;
					break;
			}
			break;
		case 'C':
			switch(line[1]) {
				case '3':
					return C3;
					break;
				case '4':
					return C4;
					break;
				case '5':
					return C5;
					break;
				case '6':
					return C6;
					break;
			}
			break;
		case 'D':
			switch(line[1]) {
				case '3':
					return D3;
					break;
				case '4':
					return D4;
					break;
				case '5':
					return D5;
					break;
				case '6':
					return D6;
					break;
			}
			break;
		case 'E':
			switch(line[1]) {
				case '3':
					return E3;
					break;
				case '4':
					return E4;
					break;
				case '5':
					return E5;
					break;
				case '6':
					return E6;
					break;
			}
			break;
		case 'F':
			switch(line[1]) {
				case '3':
					return F3;
					break;
				case '4':
					return F4;
					break;
				case '5':
					return F5;
					break;
				case '6':
					return F6;
					break;
			}
			break;
		case 'G':
			switch(line[1]) {
				case '3':
					return G3;
					break;
				case '4':
					return G4;
					break;
				case '5':
					return G5;
					break;
				case '6':
					return G6;
					break;
			}
			break;
	}
	return REST;
}
int get_duration(const char* line) {
	int dotted = 0, 
			offset = 3, 
			duration = 0;

	if (line[3] == 'D') {
		dotted = 1;
		offset = 4;
	}

	switch(line[offset]) {
		// SB, DL, BR, MN, CR, QV, SQ, DQ, HQ
		case 'S':
			if (line[offset+1] == 'B')
				duration = SEMIBREVE;
			else if (line[offset+1] == 'Q')
				duration = SEMIQUAVER;
			break;
		case 'D':
			if (line[offset+1] == 'L')
				duration = DUPLEX_LONGA;
			else if (line[offset+1] == 'Q')
				duration = DEMISEMIQUAVER;
			break;
		case 'B':
			duration = BREVE;
			break;
		case 'M':
			duration = MINIM;
			break;
		case 'C':
			duration = CROTCHET;
			break;
		case 'Q':
			duration = QUAVER;
			break;
		case 'H':
			duration = HEMIDEMISEMIQUAVER;
			break;
	}

	if (dotted)
		duration = DOTTED(duration);
	return duration;
}

