/*
 * score.h
 *
 *  Created on: Jan 23, 2015
 *      Author: Stephanie Amati
 *
 */

#ifndef SCORE_H_
#define SCORE_H_

void info_finish(int score, char* game);
void info_init();
void info_update(int score);
void info_save_score(int score, char* game);
int info_get_score(char* game);

#endif /* SCORE_H_ */
