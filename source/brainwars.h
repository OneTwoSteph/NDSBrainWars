/*
 * brainwars.h
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati & Nawaaz GS
 *
 */

#ifndef BRAINWARS_H_
#define BRAINWARS_H_

void brainwars_start_draw(void);

void brainwars_init(void);
void brainwars_configMain(void);
void brainwars_configSub(void);

void brainwars_main_init(void);
void brainwars_main(void);
void brainwars_main_select(void);
void brainwars_main_draw(void);

void brainwars_train_init(void);
void brainwars_train(void);
void brainwars_train_select(void);
void brainwars_train_draw(void);
void brainwars_train_score_init(void);
void brainwars_train_score(void);

void brainwars_credits_init(void);
void brainwars_credits(void);

#endif /* BRAINWARS_H_ */
