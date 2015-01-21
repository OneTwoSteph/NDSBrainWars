/*
 * jankenpon.h
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati
 */

#include <stdbool.h>

void jankenpon_init(void);
void jankenpon_draw(int shape, int color, int U, int M, int D);
bool jankenpon_game(void);
void jankenpon_next(void);
void jankenpon_wrong(void);
void jankenpon_reset();
