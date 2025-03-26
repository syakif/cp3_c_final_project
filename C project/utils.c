#include "utils.h"
#include <stdio.h>

void display_menu() {
    printf("1. Load train status from file\n");
    printf("2. Load material\n");
    printf("3. Load material to specific wagon\n");
    printf("4. Unload material\n");
    printf("5. Unload material from specific wagon\n");
    printf("6. Display train status\n");
    printf("7. Display materials status\n");
    printf("8. Empty train\n");
    printf("9. Save train status to file\n");
    printf("10. Exit\n");
}

void display_materials(){
    printf("1- Large Box, 200 kg\n");
    printf("2- Middle Box, 150 kg\n");
    printf("3- Small Box, 100 kg\n");
}