#include <stdio.h>
#include <fcntl.h>
#include <stropts.h>
#include <linux/kd.h>
#include <unistd.h>

#define SEMIBREVE 1500
#define DUPLEX_LONGA SEMIBREVE*8
#define LONGA SEMIBREVE*4
#define BREVE SEMIBREVE*2
#define MINIM SEMIBREVE/2
#define CROTCHET SEMIBREVE/4
#define CROTCHET_DOTTED SEMIBREVE/4+QUAVER
#define QUAVER SEMIBREVE/8
#define SEMIQUAVER SEMIBREVE/16
#define DEMISEMIQUAVER SEMIBREVE/32
#define HEMIDEMISEMIQUAVER SEMIBREVE/64
#define DOTTED(VALUE) (VALUE + VALUE/2)

#define REST 0
#define C3 131
#define D3 147
#define E3 164
#define F3 174
#define G3 196
#define A3 220
#define B3 247
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define B5 989
#define C6 1046
#define D6 1175
#define E6 1319
#define F6 1397
#define G6 1568
#define A6 1760
#define B6 1976

int init_player(int *fd);
int close_player(int *fd);
void play_note(int *fd, int freq, int duration);
FILE *fb;


int main(int argc, char *argv[])
{
	fb = fopen("file.sb", "wb");

	/*FILE *fb = fopen("file.sb", "wb");*/
	/*if (fb != NULL) {*/
		/*int note = A3;*/
		/*int duration = CROTCHET;*/

		/*fwrite(&note, sizeof(note), 1, fb);*/
		/*fwrite(&duration, sizeof(duration), 1, fb);*/
		/*fclose(fb);*/
	/*}*/

	int fd;
	init_player(&fd);

	play_note(&fd, G3, QUAVER);
	play_note(&fd, C4, DOTTED(CROTCHET));
	play_note(&fd, B3, QUAVER);
	play_note(&fd, D4, QUAVER);
	play_note(&fd, C4, QUAVER);
	play_note(&fd, G3, QUAVER);
	play_note(&fd, E3, QUAVER);
	play_note(&fd, A3, MINIM);
	play_note(&fd, F3, CROTCHET);

	play_note(&fd, REST, QUAVER);

	play_note(&fd, A3, QUAVER);
	play_note(&fd, D4, DOTTED(CROTCHET));
	play_note(&fd, C4, QUAVER);
	play_note(&fd, B3, QUAVER);
	play_note(&fd, A3, QUAVER);
	play_note(&fd, G3, QUAVER);
	play_note(&fd, F3, QUAVER);
	play_note(&fd, E3, MINIM);

	close_player(&fd);

	FILE *fr = fopen("file.sb", "rb");

	if (fr != NULL) {
	short noter, durationr;
	noter = durationr = -1;

		while (durationr != 0) {
			fread(&noter, sizeof(short), 1, fr);
			fread(&durationr, sizeof(short), 1, fr);
			printf("%d Hz, %d ms\n", noter, durationr);
		}

		fclose(fr);
	}

	return 0;
}

int init_player(int *fd)
{
	*fd = open("/dev/console", O_RDONLY);
	if (*fd == -1) return -1;
	return 0;
}

int close_player(int *fd)
{
	ioctl(*fd, KIOCSOUND, 0);
	if (fb != NULL) 
		fclose(fb);
	return close(*fd);
}

void play_note(int *fd, int freq, int duration)
{
	freq = freq == 0 ? 0 : 1193180/freq;
	int arg = (duration<<16) | (freq);
	/*ioctl(*fd, KDMKTONE, arg);*/
	/*usleep(duration * 1000);*/
	if (fb != NULL) {
		fwrite(&freq, sizeof(freq), 1, fb);
		fwrite(&duration, sizeof(duration), 1, fb);
	}
}

