#include "train.h"
#include "vagon.h"
#include "material.h"
#include "file_ops.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
cd "c:\Users\akifs\OneDrive\Masaüstü\C project\" ; if ($?) { x86_64-w64-mingw32-g++ main.c train.c vagon.c material.c file_ops.c utils.c -o main } ; if ($?) { .\main }

*/

int main() {
    Train* train = (Train*)malloc(sizeof(Train));
    initialize_train(train, "T123");
    load_train_status(train, "train_status.txt");
    //Global variables for materials
    MaterialType* material_large = large_box("train_status.txt");
    MaterialType* material_medium = medium_box("train_status.txt");
    MaterialType* material_small = small_box("train_status.txt");
    int choice;

    while (1) {
        display_menu();
        Wagon* wagon;
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                printf("Load train status from file\n");
                load_train_status(train, "train_status.txt");
                material_large = large_box("train_status.txt");
                material_medium = medium_box("train_status.txt");
                material_small = small_box("train_status.txt");
                break;
            case 2:
                printf("Load material\n");
                int material_no;
                int amount;
                printf("1- Large Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_large->weight, material_large->quantity, material_large->loaded);
                printf("2- Medium Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_medium->weight, material_medium->quantity, material_medium->loaded);
                printf("3- Small Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_small->weight, material_small->quantity, material_small->loaded);

                printf("Enter the material's number: \n");
                scanf("%d", &material_no);

                switch (material_no){
                case 1:
                    printf("Enter the amount: \n");
                    scanf("%d", &amount);
                    load_material(train, material_large, amount);
                    break;
                case 2:
                    printf("Enter the amount: \n");
                    scanf("%d", &amount);
                    load_material(train, material_medium, amount);
                    break;
                case 3:
                    printf("Enter the amount: \n");
                    scanf("%d", &amount);
                    load_material(train, material_small, amount);
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
                break;
            case 3:
                printf("Load material to specific wagon\n");
                int material_no_1;
                int amount_1;
                int wagon_no_1;
                printf("1- Large Box, Weight: %f, Quantity: %d, Loaded: %d\n", material_large->weight, material_large->quantity, material_large->loaded);
                printf("2- Medium Box, Weight: %f, Quantity: %d, Loaded: %d\n", material_medium->weight, material_medium->quantity, material_medium->loaded);
                printf("3- Small Box, Weight: %f, Quantity: %d, Loaded: %d\n", material_small->weight, material_small->quantity, material_small->loaded);

                printf("Enter the material's number: \n");
                scanf("%d", &material_no_1);

                printf("Enter the amount: \n");
                scanf("%d", &amount_1);

                printf("Enter the wagon number: \n");
                scanf("%d", &wagon_no_1);

                switch (material_no_1){
                case 1:
                    load_material_to_wagon(train, material_large, amount_1, wagon_no_1);
                    break;
                case 2:
                    load_material_to_wagon(train, material_medium, amount_1, wagon_no_1);
                    break;
                case 3:
                    load_material_to_wagon(train, material_small, amount_1, wagon_no_1);
                    break;
                default:
                    break;
                }
                break;
            case 4:
                printf("Unload material\n");
                int material_no_2;
                int amount_2;
                printf("1- Large Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_large->weight, material_large->quantity, material_large->loaded);
                printf("2- Medium Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_medium->weight, material_medium->quantity, material_medium->loaded);
                printf("3- Small Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_small->weight, material_small->quantity, material_small->loaded);

                printf("Enter the material's number: \n");
                scanf("%d", &material_no_2);

                switch (material_no_2){
                case 1:
                    printf("Enter the amount: \n");
                    scanf("%d", &amount_2);
                    unload_material(train, material_large, amount_2);
                    break;
                case 2:
                    printf("Enter the amount: \n");
                    scanf("%d", &amount_2);
                    unload_material(train, material_medium, amount_2);
                    break;
                case 3:
                    printf("Enter the amount: \n");
                    scanf("%d", &amount_2);
                    unload_material(train, material_small, amount_2);
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
                break;
            case 5:
                printf("Unload material from specific wagon\n");
                int material_no_3;
                int amount_3;
                int wagon_no_3;
                printf("1- Large Box, Weight: %f, Quantity: %d, Loaded: %d\n", material_large->weight, material_large->quantity, material_large->loaded);
                printf("2- Medium Box, Weight: %f, Quantity: %d, Loaded: %d\n", material_medium->weight, material_medium->quantity, material_medium->loaded);
                printf("3- Small Box, Weight: %f, Quantity: %d, Loaded: %d\n", material_small->weight, material_small->quantity, material_small->loaded);

                printf("Enter the material's number: \n");
                scanf("%d", &material_no_3);

                printf("Enter the amount: \n");
                scanf("%d", &amount_3);

                printf("Enter the wagon number: \n");
                scanf("%d", &wagon_no_3);

                switch (material_no_3){
                case 1:
                    unload_material_from_wagon(train, material_large, amount_3, wagon_no_3);
                    break;
                case 2:
                    unload_material_from_wagon(train, material_medium, amount_3, wagon_no_3);
                    break;
                case 3:
                    unload_material_from_wagon(train, material_small, amount_3, wagon_no_3);
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
                break;
            case 6:
                printf("Display train status\n");
                display_train_status(train);
                break;
            case 7:
                printf("Display materials status\n");
                display_materials_status(material_large, material_medium, material_small);
                break;
            case 8:
                printf("Empty train\n");
                free_train(train, material_large, material_medium, material_small);
                break;
            case 9:
                printf("Save train status to file\n");
                save_to_file(train, "train_status.txt", material_large, material_medium, material_small);
                break;
            case 10:
                printf("Exiting...\n");

                free_train(train, material_large, material_medium, material_small);
                free(train);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
