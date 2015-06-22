/*
 * musical.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Stephanie Amati
 *
 */

#ifndef MUSICAL_H_
#define MUSICAL_H_

void musical_init(void);
void musical_next(void);
void musical_draw_play(void);
void musical_play_tone(void);
void musical_draw_tones(void);
void musical_draw_tone(int tone, int palette);
int musical_game(void);
void musical_correct(void);
void musical_wrong();
void musical_reset(void);

#endif /* MUSICAL_H_ */
