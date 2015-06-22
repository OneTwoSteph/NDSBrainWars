/*
 * plusminus.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS modified by Stephanie Amati
 */

#ifndef PLUSMINUS_H_
#define PLUSMINUS_H_

void plusminus_init(void);
void plusminus_start(void);
void plusminus_new_number(void);
void plusminus_draw_number(int palette);
void plusminus_draw_digit(int start, int digit, int palette);
int plusminus_game(void);
void plusminus_correct(void);
void plusminus_wrong(void);
void plusminus_reset(void);

#endif /* PLUSMINUS_H_ */
