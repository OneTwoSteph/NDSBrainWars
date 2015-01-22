/*
 * addition.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS
 */

#ifndef ADDITION_H_
#define ADDITION_H_

void addition_init(void);
void addition_new_number(void);
void addition_draw(void);

bool addition_game(void);

void addition_add_num(int num);
void addition_correct(void);
void addition_wrong(void);
void addition_reset(void);

#endif /* ADDITION_H_ */
