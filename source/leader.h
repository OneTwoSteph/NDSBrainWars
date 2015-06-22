/*
 * leader.h
 *
 *  Created on: Jan 20, 2015
 *      Author: Nawaaz GS modified by Stephanie Amati
 */

#ifndef LEADER_H_
#define LEADER_H_

void leader_init(void);
void leader_new_config(void);
void leader_draw_blocks(void);
void leader_draw_block(int x, int y, int color);
void leader_draw_blinking(void);
int leader_game(void);
void leader_correct(void);
void leader_wrong(void);
void leader_reset(void);

#endif /* LEADER_H_ */
