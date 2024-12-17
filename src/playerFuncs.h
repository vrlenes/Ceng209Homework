#ifndef PLAYERFUNCS_H
#define PLAYERFUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "game.h"
//#include "game.c"



//void move(Room **current_room, const char *direction);
void look(Room *current_room);
void attack(Player *player, Room *current_room);
void pickup(Player *player, Room *current_room);
void dropItem(Player *player, Room *current_room,int index);
void inventory(Player *player);
void show_stats(Player *player);
void show_map(Room *current_room, Room *rooms[4][4]);
void link_rooms(Room *rooms[4][4]);
#endif // PLAYERFUNCS_H
