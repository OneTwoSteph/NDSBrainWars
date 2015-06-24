/*
 * score.h
 *
 *  Created on: Jan 23, 2015
 *      Author: Stephanie Amati
 *
 */

#ifndef SCORE_H_
#define SCORE_H_

void info_init();
void info_update_score(int score);
void info_update_time(void);
int info_get_time(void);
void info_stop_time(void);
void info_finish(int score, int game);
void info_save_score(int score, int game);
int info_get_score(int game);

#endif /* SCORE_H_ */
