#include <fcntl.h>
#include <stropts.h>
#include <linux/kd.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd = open("/dev/console", O_RDONLY);
	// 65541423
	int arg = (1000<<16) | 1193180/220;
	ioctl(fd, KDMKTONE, arg);
	usleep(1000 * 1000);
	ioctl(fd, KIOCSOUND, 0);
	return 0;
}

