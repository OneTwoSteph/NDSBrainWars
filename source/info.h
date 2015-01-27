/*
 * score.h
 *
 *  Created on: Jan 23, 2015
 *      Author: Stephanie Amati
 *
 */

#ifndef SCORE_H_
#define SCORE_H_

void info_init(int state);
void info_update(int score, int state);
int info_get_time();
void info_finish(int score, char* game, int state);
void info_save_score(int score, char* game);
int info_get_score(char* game);

#endif /* SCORE_H_ */
