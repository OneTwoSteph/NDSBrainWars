/*
 * path.h
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 */

#include <stdbool.h>

void path_init(void);
void path_draw(int direction, int color);
bool path_game(void);
void path_next(void);
void path_wrong(void);
void path_reset();
