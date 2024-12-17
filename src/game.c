#include "game.h"
#include <stdbool.h>



// Oyunu başlatma
void initialize_game(Player *player, Room *rooms[4][4], Room **current_room) {
    player->name = "Hero";
    player->health = 100;
    player->strength = 10;
    player->inventory_capacity = 4;
    //player->inventory = malloc(player->inventory_capacity * sizeof(Item));
    player->inventory_count = 0;

    Item empty_item = {NULL, false, 0, false};

    // Odaları oluştur
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rooms[i][j] = malloc(sizeof(Room));
            create_room(rooms[i][j], "A mysterious room", NULL, NULL);
        }
    }

    

    //Itemler
    Item *sword1 = malloc(sizeof(Item));
    create_item( sword1,"Broken Sword", true, 5);
    Item *sword2 = malloc(sizeof(Item));
    create_item( sword2,"Iron Sword", true, 10);
    Item *axe = malloc(sizeof(Item));
    create_item( axe,"War Axe", true, 15);
    Item *stone = malloc(sizeof(Item));
    create_item( stone,"Power Stone", true, 20);
    Item *poison1 = malloc(sizeof(Item));
    create_item(poison1, "Little health poison", false, 20);
    Item *poison2 = malloc(sizeof(Item));
    create_item(poison2, "Little health poison", false, 20);
    Item *poison3 = malloc(sizeof(Item));
    create_item(poison3, "Little health poison", false, 20);
    Item *poison4 = malloc(sizeof(Item));
    create_item(poison4, "Middle health poison", false, 40);
    Item *poison5 = malloc(sizeof(Item));
    create_item(poison5, "Middle health poison", false, 40);
    Item *poison6 = malloc(sizeof(Item));
    create_item(poison6, "Big health poison", false, 60);

    //Yaratıklar
    
    Creature *goblin = malloc(sizeof(Creature));
    create_monster(goblin, "Goblin", 40, 5);
    Creature *spider = malloc(sizeof(Creature));
    create_monster(spider, "Giant Spider", 40, 7);
    Creature *witch = malloc(sizeof(Creature));
    create_monster(witch, "Dark Witch", 25, 25);
    Creature *snake = malloc(sizeof(Creature));
    create_monster(snake, "Snake", 80, 10);
    Creature *vampire = malloc(sizeof(Creature));
    create_monster(vampire, "Vampire", 125, 10);
    Creature *sfenks = malloc(sizeof(Creature));
    create_monster(sfenks, "Sfenks", 150, 10);
    Creature *troll = malloc(sizeof(Creature));
    create_monster(troll, "Troll", 180, 20);
    Creature *boss = malloc(sizeof(Creature));
    create_monster(boss, "Dragon", 240, 35);

    // Özel odalar
    create_room(rooms[0][0], "A quiet starting room with worn stone walls.", NULL, NULL);
    create_room(rooms[0][1],"A narrow passage dimly lit and silent.",NULL,NULL);
    create_room(rooms[0][2], "A dark room filled with webs and a lurking giant spider.", poison1, spider);
    create_room(rooms[0][3], "A treasure room with golden chests and scattered dust.", axe, NULL);
    create_room(rooms[1][0], "A narrow path surrounded by cracked stone walls.", NULL, NULL);
    create_room(rooms[1][1], "A quiet room with an old sword resting on the floor.", sword1, NULL);
    create_room(rooms[1][2],"A dangerous room shadowed corners hiding a dark witch.",NULL,witch);
    create_room(rooms[1][3], "A dark room the silent gaze of a Sphinx filling the space.", poison4, sfenks);
    create_room(rooms[2][0], "A damp room filled with faint growls and the smell of goblins.", poison2, goblin);
    create_room(rooms[2][1], "A dark chamber with cold stone and a slithering snake.", NULL, snake);
    create_room(rooms[2][2], "A quiet room a large stone resting in the center.", stone, NULL);
    create_room(rooms[2][3],"A treasure room with poison on the table.",poison6,NULL);
    create_room(rooms[3][0], " A shadowy room faint whispers and the glint of a vampire's fangs.", sword2, vampire);
    create_room(rooms[3][1], "A treasure room full of shattered bottles and green health potion fumes.", poison5, NULL);
    create_room(rooms[3][2], "A dark room the heavy presence of a towering troll.", poison3, troll);
    create_room(rooms[3][3], "A room full of gold guarded by a dragon.(Final boss)", NULL, boss);



    // Odalar arasındaki bağlantılar
    link_rooms(rooms);

    // Başlangıç odası
    *current_room = rooms[0][0];

}
//İtem oluşturma
void create_item(Item *item, char* name, bool isAttack, int stats){
    item->name = strdup(name);
    item->isAttack = isAttack;
    item->stats = stats;
    item->isUsed = false;
}

// Bir oda oluşturma
void create_room(Room *room, const char *description, Item *item, Creature *creature) {
    room->description = strdup(description);
    room->item = item;
    room->creature = creature;
    room->up = room->down = room->left = room->right = NULL;
}

void create_monster(Creature *creature, char* name, int health, int strength){
    creature->name = strdup(name);
    creature->health = health;
    creature->strength = strength;
}

// Odaları birbirine bağlama
void link_rooms(Room *rooms[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i > 0) rooms[i][j]->up = rooms[i - 1][j];
            if (i < 3) rooms[i][j]->down = rooms[i + 1][j];
            if (j > 0) rooms[i][j]->left = rooms[i][j - 1];
            if (j < 3) rooms[i][j]->right = rooms[i][j + 1];
        }
    }
}



/***************************************************************************************************************************/
//PlayerFuncs


void move(Room **current_room, const char *direction) {
    Room *next_room = NULL;

    if (strcmp(direction, "up") == 0) {
        next_room = (*current_room)->up;
    } else if (strcmp(direction, "down") == 0) {
        next_room = (*current_room)->down;
    } else if (strcmp(direction, "left") == 0) {
        next_room = (*current_room)->left;
    } else if (strcmp(direction, "right") == 0) {
        next_room = (*current_room)->right;
    }

    if (next_room) {
        *current_room = next_room;
        printf("You moved %s.\n", direction);
    } else {
        printf("You can't move %s from here.\n", direction);
    }
}





