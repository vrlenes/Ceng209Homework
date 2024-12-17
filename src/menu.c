#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************************************************************************** */
//MenuFuncs


void save_game(Player *player, Room *current_room, Room *rooms[4][4], const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (!file) {
        perror("Failed to save game");
        return;
    }

    // Oyuncu bilgilerini kaydet
    fprintf(file, "Player:%d,%d\n", player->health, player->strength);

    // Envanter kapasitesine göre tüm slotları yazdır
for (int i = 0; i < player->inventory_capacity; i++) {
    if (i < player->inventory_count) {
        Item *item = &player->inventory[i];
        fprintf(file, "Items:%s,%d,%d,%d\n", 
                item->name ? item->name : "NULL", // Eşya ismi
                item->isAttack,                  // Saldırı özelliği (bool için int)
                item->stats,                     // İstatistik değeri
                item->isUsed);                   // Kullanılmış mı (bool için int)
    } else {
        // Eğer slot boşsa, NULL yazdır
        fprintf(file, "Items:NULL,-1,0,-1\n");
    }
}


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

    // Geçerli oda bilgilerini kaydet
    if (current_room_x != -1 && current_room_y != -1) {
        fprintf(file, "CurrentRoom:%d,%d\n", current_room_x, current_room_y);
    } else {
        fprintf(file, "CurrentRoom:NULL,NULL\n");
        printf("Warning: Current room not found in the rooms array.\n");
    }


    // Odaların durumunu kaydet
for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        Room *room = rooms[i][j];

        // Oda açıklaması
        fprintf(file, "Room:%d,%d,%s,", i, j, room->description);

        // Eşya bilgisi (Item struct)
        if (room->item) {
            fprintf(file, "%s,%d,%d,%d,", 
                    room->item->name ? room->item->name : "NULL", // Eşya adı
                    room->item->isAttack,                        // Saldırı mı?
                    room->item->stats,                           // İstatistik değeri
                    room->item->isUsed);                         // Kullanılmış mı?
        } else {
            fprintf(file, "NULL,-1,0,-1,");
        }

        // Canlının bilgisi
        if (room->creature) {
            fprintf(file, "%s,%d,%d\n", 
                    room->creature->name, 
                    room->creature->health, 
                    room->creature->strength);
        } else {
            fprintf(file, "NULL,-1,-1\n");
        }
    }
}

    fclose(file);
    printf("Game saved to %s.\n", filepath);
}

void load_game(Player *player, Room *rooms[4][4], Room **current_room, const char *filepath) {
    Item empty_item = {NULL, false, 0, false};
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char buffer[256];
    // Oyuncu bilgilerini yükle
    if (!fgets(buffer, sizeof(buffer), file)) {
        printf("Error: Unable to read player data.\n");
        fclose(file);
        return;
    }

    
    if (sscanf(buffer, "Player:%d,%d",  &player->health, &player->strength) != 2) {
        printf("Error: Invalid player data format. Data: %s\n", buffer);
        fclose(file);
        return;
    }



// Envanteri sıfırla
for (int i = 0; i < player->inventory_capacity; i++) {
    player->inventory[i].name = NULL;
}

// Her bir envanter slotunu doldur
for (int i = 0; i < player->inventory_capacity; i++) {
    char name[50];
    int stats;
    bool isAttack, isUsed;

    // Satırı oku ve "Items:" ile başlıyorsa ayrıştır
    if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, "Items:", 6) == 0) {
        if (sscanf(buffer, "Items:%[^,],%d,%d,%d", name, &isAttack, &stats, &isUsed) == 4) {
            if (strcmp(name, "NULL") != 0) {
                player->inventory[i].name = strdup(name); // Dinamik bellek ayır
                player->inventory[i].isAttack = isAttack;
                player->inventory[i].stats = stats;
                player->inventory[i].isUsed = isUsed;
                player->inventory_count++;
                
            } else {
                player->inventory[i].name = NULL; // Slot boş
                
            }
        } else {
            printf("Invalid format for inventory item at index %d.\n", i);
        }
    } else {
        printf("Error reading inventory item at index %d.\n", i);
    }
}

    // Geçerli oda bilgisi
    int current_room_x = -1, current_room_y = -1;
    if (!fgets(buffer, sizeof(buffer), file)) {
        printf("Error: Unable to read current room data.\n");
        fclose(file);
        return;
    }
    
    if (sscanf(buffer, "CurrentRoom:%d,%d", &current_room_x, &current_room_y) != 2) {
        printf("Error: Invalid current room format. Data: %s\n", buffer);
        fclose(file);
        return;
    }
    

    if (current_room_x < 0 || current_room_x >= 4 || current_room_y < 0 || current_room_y >= 4) {
        printf("Error: Current room coordinates out of bounds.\n");
        fclose(file);
        return;
    }
    
    *current_room = rooms[current_room_x][current_room_y];
    if (*current_room == NULL) {
        printf("Error: Current room not properly set.\n");
        fclose(file);
        return;
    }
    
    // Odaların durumunu yükle
    while (fgets(buffer, sizeof(buffer), file)) {
        int x = -1, y = -1;
        char description[100] , itemName[50] , creature_name[50] ;
        int creature_health = -1, creature_strength = -1;
        int isAttack = -1, stats = -1, isUsed = -1;
        
        if (sscanf(buffer, "Room:%d,%d,%[^,],%[^,],%d,%d,%d,%[^,],%d,%d",
                   &x, &y, description, itemName, &isAttack, &stats, &isUsed, creature_name, &creature_health, &creature_strength) != 10) {
            printf("Error: Invalid room data format. Data: %s\n", buffer);
            fclose(file);
            return;
        }
        Room *room = rooms[x][y];
        room->item = malloc(sizeof(Item));
        free(room->description);
        room->description = strdup(description);
        if (strcmp(itemName, "NULL") == 0 ) {
            free(room->item);
            room->item = NULL;
        } else {
            room->item->name = strdup(itemName);
            room->item->isAttack = isAttack;
            room->item->stats = stats;
            room->item->isUsed = isUsed;

        }
        if (strcmp(creature_name, "NULL") == 0 || creature_health == -1) {
            free(room->creature);
            room->creature = NULL;
        } else {
            if (!room->creature) {
                room->creature = malloc(sizeof(Creature));
            }
            room->creature->name = strdup(creature_name);
            room->creature->health = creature_health;
            room->creature->strength = creature_strength;
        }
        
    }
    

    fclose(file);
    printf("Game loaded from %s.\n", filepath);
}