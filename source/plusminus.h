/*
 * plusminus.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Nawaaz GS
 */

#ifndef PLUSMINUS_H_
#define PLUSMINUS_H_

#define GREATER 	1
#define SMALLER 	2
#define MULTIPLY	3
#define DIVIDED 	4

void plusminus_init(void);
void plusminus_new_number(void);
void plusminus_draw(void);

bool plusminus_game(void);

void plusminus_correct(void);
void plusminus_wrong(void);
void plusminus_reset(void);

#endif /* PLUSMINUS_H_ */
