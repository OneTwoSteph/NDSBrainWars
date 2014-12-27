/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "path.h"

int main(void) {

    consoleDemoInit();

    path_init();

    while(1){
        swiWaitForVBlank();	
    }
}
