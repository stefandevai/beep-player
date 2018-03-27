/*#include <stdio.h>*/
#include <fcntl.h>
#include <stropts.h>
#include <linux/kd.h>
#include <unistd.h>

int init_player(int *fd);
int close_player(int *fd);
void play_note(int *fd, int freq, int duration);

int main(int argc, char *argv[])
{
	int fd;
	init_player(&fd);
	
	play_note(&fd, 196, 1000);
	play_note(&fd, 261, 1000);

	close_player(&fd);
	return 0;
}

int init_player(int *fd) {
	*fd = open("/dev/console", O_RDONLY);
	if (*fd == -1) return -1;
	return 0;
}

int close_player(int *fd) {
	ioctl(*fd, KIOCSOUND, 0);
	return close(*fd);
}

void play_note(int *fd, int freq, int duration) {
	ioctl(*fd, KIOCSOUND, 1193180/freq);
	usleep(duration * 1000);
}

