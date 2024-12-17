#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"



void save_game(Player *player, Room *current_room, Room *rooms[4][4], const char *filepath);
void load_game(Player *player, Room *rooms[4][4], Room **current_room, const char *filepath);

#endif // MENU_H