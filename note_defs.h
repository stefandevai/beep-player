/**
 * note_defs.h -- defines note values and durations for beep-player.
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

/*
 * Note values
 * See: <https://en.wikipedia.org/wiki/Note_value>
 */
#define SEMIBREVE 1500 									// Base for our relative values calculations
#define DUPLEX_LONGA SEMIBREVE*8
#define LONGA SEMIBREVE*4
#define BREVE SEMIBREVE*2
#define MINIM SEMIBREVE/2
#define CROTCHET SEMIBREVE/4
#define QUAVER SEMIBREVE/8
#define SEMIQUAVER SEMIBREVE/16
#define DEMISEMIQUAVER SEMIBREVE/32
#define HEMIDEMISEMIQUAVER SEMIBREVE/64

/**
 * Note value modifier macros
 */
#define DOTTED(VALUE) (VALUE + VALUE/2) // See: <https://en.wikipedia.org/wiki/Dotted_note>

/*
 * Piano key frequencies
 * See: <https://en.wikipedia.org/wiki/Piano_key_frequencies>
 */
#define REST 0 // Rest: no sound at all
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
#define C7 2093

/**
 * Frequency modifier macros
 */
#define SHARP(VALUE) (VALUE + VALUE*0.05946)	// See: <https://en.wikipedia.org/wiki/Sharp_%28music%29>
#define FLAT(VALUE) (VALUE - VALUE*0.05946) 	// See: <https://en.wikipedia.org/wiki/Flat_(music)>
