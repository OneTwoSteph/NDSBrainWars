/*
 * eatit.h
 *
 *  Created on: Jan 21, 2015
 *      Author: Stephanie Amati
 *
 */

#ifndef EATIT_H_
#define EATIT_H_

void eatit_init(void);
void eatit_next(void);
void eatit_draw_pacman(void);
void eatit_draw_food(void);
void eatit_draw_blinking(void);
int eatit_game(void);
void eatit_correct(void);
void eatit_wrong(void);
void eatit_reset(void);

#endif /* EATIT_H_ */