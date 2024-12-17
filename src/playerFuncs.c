#include "playerFuncs.h"

// Odayı inceleme
void look(Room *current_room) {
    if (current_room) {
        printf("Room description: %s\n", current_room->description);
        if (current_room->item) {
            printf("You see an item here: %s\n", current_room->item->name);
        }
        if (current_room->creature) {
            printf("A creature is here: %s (Health: %d)\n",
                   current_room->creature->name, current_room->creature->health);
        }
    } else {
        printf("You are nowhere. Something is wrong.\n");
    }
}




// Saldırı
void attack(Player *player, Room *current_room) {
    if (current_room->creature) {
        while (current_room->creature->health > 0 && player->health > 0) {
            printf("You attack the %s!\n", current_room->creature->name);
            current_room->creature->health -= player->strength;

            if (current_room->creature->health > 0) {
                printf("The %s attacks you!\n", current_room->creature->name);
                player->health -= current_room->creature->strength;
            }
        }

        if (player->health <= 0) {
            printf("You have been defeated. Game over.\n");
            exit(0);
        } else if (current_room->creature->health <= 0) {
            printf("You defeated the %s!\n", current_room->creature->name);
            free(current_room->creature);
            current_room->creature = NULL;
        }
    } else {
        printf("There is nothing to attack here.\n");
    }
}




// Eşya toplama
void pickup(Player *player, Room *current_room) {
    if (current_room->item) {
        if (player->inventory_count < player->inventory_capacity) {
            player->inventory[player->inventory_count] = *current_room->item;
            player->inventory_count++;
            if(current_room->item->isAttack){
                if(!(current_room->item->isUsed)){
                    player->strength += current_room->item->stats;
                    player->inventory[player->inventory_count-1].isUsed = true;
                }
            }
            else{
                player->health += current_room->item->stats;
                player->inventory[player->inventory_count-1].isUsed = true;
            }
            printf("You picked up %s.\n", current_room->item->name);
            //free(current_room->item);
            current_room->item = NULL;
        } else {
            printf("Your inventory is full.\n");
        }
    } else {
        printf("There is nothing to pick up here.\n");
    }
}

// Eşya bırakma
void dropItem(Player *player, Room *current_room, int index) {

    Item *empty_item = malloc(sizeof(Item));
    create_item(empty_item,NULL, false, 0);
    // Geçerli bir envanter indeksi kontrolü
    
    if (index < 0 || index >= player->inventory_count || &player->inventory[index].name == NULL) {
        printf("Invalid inventory index or no item at this slot.\n");
        return;
    }
    // Oda zaten bir eşya içeriyorsa
    if (current_room->item) {
        printf("The room already has an item. You can't drop here.\n");
        return;
    }
    
    if (current_room->item != NULL) {
        free(current_room->item);
    }
    current_room->item = malloc(sizeof(Item));
    
// Eşyayı odaya bırak
     current_room->item->name = strdup(player->inventory[index].name);
     current_room->item->isAttack = player->inventory[index].isAttack;
     current_room->item->stats = player->inventory[index].stats;
     current_room->item->isUsed= player->inventory[index].isUsed;

    
    // Envanterden sil
    //free(player->inventory[index]);
    player->inventory[index] = *empty_item;
    
    // Envanterdeki diğer eşyaları kaydır
    for (int i = index; i < player->inventory_count - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventory[player->inventory_count - 1] = *empty_item;

    // Envanter sayacını güncelle
    player->inventory_count--;

    printf("You dropped the item into the room.\n");
}



// Envanteri gösterme
void inventory(Player *player) {
    printf("Your inventory:\n");
    if (&player->inventory[0] == NULL || &player->inventory[0].name == NULL) {
        printf("Empty.\n");
    } else {
        for (int i = 0; i < player->inventory_count; i++) {
            if(&player->inventory[i]!=NULL || &player->inventory[0].name == NULL){
                 printf("- %s\n", player->inventory[i].name);
            }
               
        }
    }
}



void show_stats(Player *player){
        printf("Health:%d\n",player->health);
        printf("Strength:%d\n",player->strength);
}

void show_map(Room *current_room, Room *rooms[4][4]){
    // Geçerli oda koordinatlarını bul
    int current_room_x = -1, current_room_y = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rooms[i][j] == current_room) {
                current_room_x = i;
                current_room_y = j;
                break;
            }
        }
        if (current_room_x != -1) break;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(i == current_room_x && j == current_room_y){
                printf("X ");
            }else{
                printf("# ");
            }
            }
            printf("\n");
        }
        
    

}
