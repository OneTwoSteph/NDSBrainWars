/*
 * path.h
 *
 *  Created on: Dec 27, 2014
 *      Author: Stephanie Amati
 *
 */

#ifndef PATH_H_
#define PATH_H_

void path_init(void);
void path_next(void);
void path_draw(int pal);
int path_game(void);
void path_correct(void);
void path_wrong(void);
void path_reset(void);

#endif /* PATH_H_ */
