#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



// Yapılar

typedef struct{
    char *name;
    bool isAttack;
    int stats;
    bool isUsed;

}Item;

typedef struct {
    char *name;
    int health;
    int strength;
    int inventory_capacity;
    Item inventory[4];
    int inventory_count;
} Player;

typedef struct {
    char *name;
    int health;
    int strength;
} Creature;



typedef struct Room {
    char *description;
    Item *item;
    Creature *creature;
    struct Room *up;
    struct Room *down;
    struct Room *left;
    struct Room *right;
} Room;





// Fonksiyon Prototipleri
void initialize_game(Player *player, Room *rooms[4][4], Room **current_room);
void create_room(Room *room, const char *description, Item *item, Creature *creature);
void link_rooms(Room *rooms[4][4]);
void create_item(Item *item, char* name, bool isAttack, int stats);
void create_monster(Creature *creature, char* name, int health, int strength);


//PlayerFuncs

void move(Room **current_room, const char *direction);
/*void look(Room *current_room);
void attack(Player *player, Room *current_room);
void pickup(Player *player, Room *current_room);
void dropItem(Player *player, Room *current_room,int index);
void inventory(Player *player);
void show_stats(Player *player);
void show_map(Room *current_room, Room *rooms[4][4]);


//MenuFuncs

void save_game(Player *player, Room *current_room, Room *rooms[4][4], const char *filepath);
void load_game(Player *player, Room *rooms[4][4], Room **current_room, const char *filepath);



*/

#endif // GAME_H


