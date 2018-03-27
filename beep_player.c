/**
 * beep-player -- plays simple mono-channel melody using pc speaker.
 *
 * AUTHOR: Stefan Devai
 * Created in March 27, 2018
 *
 * FEATURES:
 * 		- C3-C7# range for playing notes
 * 		- Mono-channel
 * 		- Uses PC Speaker for playing notes
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
#include <fcntl.h>
#include <stropts.h>
#include <linux/kd.h>
#include <unistd.h>

#include "note_defs.h"

/**
 * Opens /dev/console in readonly mode 
 *
 * @param fd  a pointer to a int where we will
 * 							point the file descriptor for console.
 *
 * @return -1 if there was an error opening the console 
 * 							or 0 if the operation was successful.
 */
int init_player(int *fd);

/**
 * Stops any sound playing and closes the console.
 *
 * @param fd  a pointer to the file descriptor.
 *
 * @return -1 if there was an error closing the console 
 * 							or 0 if the operation was successful.
 */
int close_player(int *fd);

/**
 * Plays a melody from a .sn file.
 *
 * @param fd 	  a	pointer to the file descriptor.
 * @param path  a string containing the .sn file path.
 *
 */
void play_from_file(int *fd, const char *path);

/**
 * Plays during a certain time a note defined in 
 * note_def.h header file. The note has to be
 * read from a .sn file.
 *
 * @param fd 	  		a	pointer to the file descriptor.
 * @param note  		note format read from file.
 * @param duration  duration in milliseconds of the sound that will be played.
 *
 * @see note_defs.h
 * @see play_from_file()
 * @see play_note()
 *
 */
void play_note_from_file(int *fd, int note, int duration);

/**
 * Plays during a certain time a note defined in
 * note_def.h header file.
 *
 * @param fd 	  		a	pointer to the file descriptor.
 * @param freq  		frequency in Hz of the sound that will be played.
 * @param duration  duration in milliseconds of the sound that will be played.
 *
 * @see note_defs.h
 * @see play_note_from_file()
 *
 */
void play_note(int *fd, int freq, int duration);

int main(int argc, char *argv[])
{
	int fd;
	init_player(&fd);

	play_from_file(&fd, "sound.bn");

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

void play_note_from_file(int *fd, int note, int duration)
{
	int arg = (duration << 16) | note;
	ioctl(*fd, KDMKTONE, arg);
	usleep(duration * 1000);
}

void play_note(int *fd, int freq, int duration)
{
	freq = freq == 0 ? 0 : 1193180/freq;
	int arg = (duration<<16) | freq;
	ioctl(*fd, KDMKTONE, arg);
	usleep(duration * 1000);
}

