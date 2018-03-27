#include <stdio.h>
#include <fcntl.h>
#include <stropts.h>
#include <linux/kd.h>
#include <unistd.h>

#include "note_defs.h"

int init_player(int *fd);
int close_player(int *fd);
void play_from_file(int *fd, const char *path);
void play_note(int *fd, int freq, int duration);
void play_note_from_file(int *fd, int note, int duration);

int main(int argc, char *argv[])
{

	int fd;
	init_player(&fd);

	play_from_file(&fd, "internationale2.bn");

	close_player(&fd);
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
	return close(*fd);
}

void play_from_file(int *fd, const char *path)
{
	FILE *fr = fopen(path, "rb");

	if (fr != NULL) {
	short note, duration;
	note = duration = -1;

	while (duration != 0 || note != 0) {
		fread(&note, sizeof(short), 1, fr);
		fread(&duration, sizeof(short), 1, fr);
		printf("%d Hz, %d ms\n", note != 0 ? 1193180/note : 0, duration);
		play_note_from_file(fd, note, duration);
	}

	fclose(fr);
	}
}

void play_note(int *fd, int freq, int duration)
{
	freq = freq == 0 ? 0 : 1193180/freq;
	int arg = (duration<<16) | freq;
	ioctl(*fd, KDMKTONE, arg);
	usleep(duration * 1000);
}

void play_note_from_file(int *fd, int note, int duration) {
	int arg = (duration << 16) | note;
	ioctl(*fd, KDMKTONE, arg);
	usleep(duration * 1000);
}

