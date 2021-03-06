/**
 * convert2bn -- converts .ss file format to .bn file format used by beep-player.
 *
 * AUTHOR: Stefan Devai
 * Created in March 27, 2018
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include "note_defs.h"

int convert(const char* sn_path);
int get_note(const char* line);
int get_duration(const char* line);

int main(int argc, char *argv[])
{
	return convert(argv[1]);
}

int convert(const char* sn_path)
{
	FILE *fb, *fs;
	char ch;

	fs = fopen(sn_path, "r");
	if (fs == NULL) {
		// TODO: Deal with not existing source files
		printf("It was not possible to open %s\n", sn_path);
		return -1;
	}

	fb = fopen("sound.bn", "wb");
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
	}

	if (line)
		free(line);

	int end = 0;
	fwrite(&end, sizeof(end), 1, fb);
	fclose(fb);
	fclose(fs);
	return 0;
}

int get_note(const char* line) {
	int flat = 0, sharp = 0;
	float frequency = (float)0;

	if (line[2] == '#') 
		sharp = 1;
	else if (line[2] == 'b') 
		flat = 1;

	switch(line[0]) {
		case 'A':
			switch(line[1]) {
				case '3':
					frequency = (float)A3;
					break;
				case '4':
					frequency = (float)A4;
					break;
				case '5':
					frequency = (float)A5;
					break;
				case '6':
					frequency = (float)A6;
					break;
			}
			break;
		case 'B':
			switch(line[1]) {
				case '3':
					frequency = (float)B3;
					break;
				case '4':
					frequency = (float)B4;
					break;
				case '5':
					frequency = (float)B5;
					break;
				case '6':
					frequency = (float)B6;
					break;
			}
			break;
		case 'C':
			switch(line[1]) {
				case '3':
					frequency = (float)C3;
					break;
				case '4':
					frequency = (float)C4;
					break;
				case '5':
					frequency = (float)C5;
					break;
				case '6':
					frequency = (float)C6;
					break;
			}
			break;
		case 'D':
			switch(line[1]) {
				case '3':
					frequency = (float)D3;
					break;
				case '4':
					frequency = (float)D4;
					break;
				case '5':
					frequency = (float)D5;
					break;
				case '6':
					frequency = (float)D6;
					break;
			}
			break;
		case 'E':
			switch(line[1]) {
				case '3':
					frequency = (float)E3;
					break;
				case '4':
					frequency = (float)E4;
					break;
				case '5':
					frequency = (float)E5;
					break;
				case '6':
					frequency = (float)E6;
					break;
			}
			break;
		case 'F':
			switch(line[1]) {
				case '3':
					frequency = (float)F3;
					break;
				case '4':
					frequency = (float)F4;
					break;
				case '5':
					frequency = (float)F5;
					break;
				case '6':
					frequency = (float)F6;
					break;
			}
			break;
		case 'G':
			switch(line[1]) {
				case '3':
					frequency = (float)G3;
					break;
				case '4':
					frequency = (float)G4;
					break;
				case '5':
					frequency = (float)G5;
					break;
				case '6':
					frequency = (float)G6;
					break;
			}
			break;
	}

	if (sharp) 
		frequency = SHARP(frequency);
	else if (flat) 
		frequency = FLAT(frequency);

	return (int)frequency;
}
int get_duration(const char* line) {
	int dotted = 0, 
			offset = 3, 
			duration = 0;

	if (line[offset-1] != ' ')
		offset += 1;

	if (line[offset] == 'D') {
		dotted = 1;
		offset += 1;
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

