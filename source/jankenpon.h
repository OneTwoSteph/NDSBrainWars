/*
 * jankenpon.h
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati
 *
 */

#ifndef JANKENPON_H_
#define JANKENPON_H_

void jankenpon_init(void);
void jankenpon_next(void);
void jankenpon_draw(int pal);
int jankenpon_game(void);
void jankenpon_correct(void);
void jankenpon_wrong(void);
void jankenpon_reset(void);

#endif /* JANKENPON_H_ */
