/*
 * addition.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS
 */

#ifndef ADDITION_H_
#define ADDITION_H_

void addition_init(int gameState);
void addition_next(void);
void addition_draw_blocks(void);
void addition_draw_block(int palette);
void addition_draw_number(void);
void addition_draw_digit(int xstart, int digit, int palette);
bool addition_game(bool player, int gameCounter);
void addition_correct(void);
void addition_wrong(void);
void addition_reset(void);

#endif /* ADDITION_H_ */
