/*
 * leader.h
 *
 *  Created on: Jan 20, 2015
 *      Author: Nawaaz GS
 */

#ifndef LEADER_H_
#define LEADER_H_

void leader_init(int gameState);
void leader_new_order(void);
void leader_draw(void);

bool leader_game(bool player, int gameCounter);

void leader_correct(void);
void leader_wrong(void);
void leader_reset(void);


#endif /* LEADER_H_ */
