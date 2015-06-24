/*
 * brainwars.h
 *
 *  Created on: Dec 28, 2014
 *      Author: Stephanie Amati & Nawaaz GS
 *
 */

#ifndef BRAINWARS_H_
#define BRAINWARS_H_

void brainwars_start_init(void);
void brainwars_start_configMain(void);
void brainwars_start_configSub(void);
void brainwars_start(void);

void brainwars_main_init(void);
void brainwars_main(void);
void brainwars_main_select(void);
void brainwars_main_draw(void);

void brainwars_train_init(void);
void brainwars_train(void);
void brainwars_train_select(void);
void brainwars_train_draw(void);

void brainwars_p_init(void);
void brainwars_p(void);
void brainwars_p_sel_init(void);
void brainwars_p_sel(void);
void brainwars_p_show_init(void);
void brainwars_p_show(void);
void brainwars_p_play_init(void);
void brainwars_p_play(void);
void brainwars_p_result_init(void);
void brainwars_p_result(void);
void brainwars_p_final_init(void);
void brainwars_p_final(void);
void brainwars_p_draw_block(int game, int pos);
void brainwars_p_draw_block_sel(int pos);
void brainwars_p_draw(int xim, int yim, int w, int h, int x, int y, int pal);

void brainwars_score_init(void);
void brainwars_score(void);

void brainwars_credits_init(void);
void brainwars_credits(void);

#endif /* BRAINWARS_H_ */
