/*#include <sys/ioctl.h>*/
#include <fcntl.h>
#include <stropts.h>
#include <linux/kd.h>
#include <unistd.h>

#define SEMIBREVE 2500
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
#define C03 131
#define D03 147
#define E03 164
#define F03 174
#define G03 196
#define A03 220
#define B03 247
#define C04 262
#define D04 294
#define E04 330
#define F04 349
#define G04 392
#define A04 440
#define B04 494

int init_player(int *fd);
int close_player(int *fd);
void play_note(int *fd, int freq, int duration);

int main(int argc, char *argv[])
{
	int fd;
	init_player(&fd);
	
	play_note(&fd, G03, QUAVER);
	play_note(&fd, C04, DOTTED(CROTCHET));
	play_note(&fd, B03, QUAVER);
	play_note(&fd, D04, QUAVER);
	play_note(&fd, C04, QUAVER);
	play_note(&fd, G03, QUAVER);
	play_note(&fd, E03, QUAVER);
	play_note(&fd, A03, MINIM);
	play_note(&fd, F03, CROTCHET);

	play_note(&fd, REST, QUAVER);

	play_note(&fd, A03, QUAVER);
	play_note(&fd, D04, DOTTED(CROTCHET));
	play_note(&fd, C04, QUAVER);
	play_note(&fd, B03, QUAVER);
	play_note(&fd, A03, QUAVER);
	play_note(&fd, G03, QUAVER);
	play_note(&fd, F03, QUAVER);
	play_note(&fd, E03, MINIM);

	close_player(&fd);
	return 0;
}

int init_player(int *fd)
{
	*fd = open("/dev/tty0", O_RDONLY);
	if (*fd == -1) return -1;
	return 0;
}

int close_player(int *fd)
{
	ioctl(*fd, KIOCSOUND, 0);
	return close(*fd);
}

void play_note(int *fd, int freq, int duration)
{
	freq = freq == 0 ? 0 : 1190000/freq;
	ioctl(*fd, KIOCSOUND, freq);
	usleep(duration * 1000);
}

