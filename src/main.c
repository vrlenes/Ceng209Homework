#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "playerFuncs.h"
//#include "playerFuncs.c"
#include "menu.h"
//#include "menu.c"



int main() {
    Player player;
   // player.name = "Steve";
    Room *rooms[4][4];
    Room *current_room = NULL;
    initialize_game(&player,rooms,&current_room);

    char command[50];
    int game_started = 0; // Oyun başlatıldı mı kontrol?

    while (!game_started) {
        // Ana menü
        printf("=== Dungeon Adventure Game ===\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // '\n' karakterini kaldır

        if (strcmp(command, "1") == 0) {
            // Yeni oyun başlat
            initialize_game(&player, rooms, &current_room);
            game_started = 1;
        } else if (strcmp(command, "2") == 0) {
            // Oyun yükle
            printf("Enter the file name to load: ");
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = 0; // '\n' karakterini kaldır
            load_game(&player, rooms, &current_room, command);
            game_started = 1;
        } else if (strcmp(command, "3") == 0) {
            // Oyundan çık
            printf("Exiting game. Goodbye!\n");
            return 0;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    // Oyun başladıktan sonra ana oyun döngüsü
    printf("Available commands: move <direction>, map, look, pickup, drop, attack, inventory, stats, save <filename>, load <filename>, exit\n");

    while (1) {
        if(rooms[3][3]->creature != NULL ){
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // '\n' karakterini kaldır

        if (strncmp(command, "move ", 5) == 0) {
            move(&current_room, command + 5);
        } else if (strcmp(command, "look") == 0) {
            look(current_room);
        } else if (strcmp(command, "map") == 0) {
            show_map(current_room, rooms);
        } else if (strcmp(command, "pickup") == 0) {
            pickup(&player, current_room);
        } else if (strcmp(command, "drop") == 0) {
            char input[10]; // Kullanıcının girdiği index için bir buffer
            printf("Index: ");
            fgets(input, sizeof(input), stdin); // Girdiyi al
            input[strcspn(input, "\n")] = 0; // '\n' karakterini kaldır
            int itemIndex = atoi(input);
            dropItem(&player, current_room,itemIndex);
        } else if (strcmp(command, "attack") == 0) {
            attack(&player, current_room);
        } else if (strcmp(command, "inventory") == 0) {
            inventory(&player);
        } else if (strcmp(command, "stats") == 0) {
            show_stats(&player);
        } else if (strncmp(command, "save ", 5) == 0) {
            char *filepath = command + 5;
            save_game(&player, current_room, rooms, filepath);
        } else if (strncmp(command, "load ", 5) == 0) {
            char *filepath = command + 5;
            load_game(&player, rooms, &current_room, filepath);
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting game. Goodbye!\n");
            break;
        } else {
            printf("Unknown command. Try again.\n");
        }
        }
        else{
            printf("=========================================\n");
            printf("YOU FINISHED THE GAME!! CONGRATULATIONS.\n");
            break;
        }

    }

    return 0;
}
