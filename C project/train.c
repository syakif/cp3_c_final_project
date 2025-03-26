#include "train.h"
//#include "vagon.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void initialize_train(Train* train, const char* train_id) {
    strcpy(train->train_id, train_id);
    train->first_wagon = NULL;
    train->wagon_count = 0;
}

void free_train(Train* train, MaterialType* material_large, MaterialType* material_medium, MaterialType* material_small) {
    Wagon* current = train->first_wagon;
    while (current) {
        Wagon* to_free = current;
        current = current->next;
        free(to_free);
    }
    train->first_wagon = NULL;
    train->wagon_count = 0;
    material_large->loaded = 0;
    material_medium->loaded = 0;
    material_small->loaded = 0;
}

void display_train_status(const Train* train) {
    printf("Train ID: %s\n", train->train_id);
    printf("Number of wagons: %d\n", train->wagon_count);

    Wagon* current = train->first_wagon;
    if(current){
        LoadedMaterial* loaded_material = current->loaded_materials;

        while(current){
            printf("Wagon ID: %d, Current Weight: %.2f\n", current->wagon_id, current->current_weight);
            loaded_material = current->loaded_materials;
            while(loaded_material){
                MaterialType* type = loaded_material->type;
                printf("%s\n", type->name);
                loaded_material = loaded_material->next;
            }
            current = current->next;
        }
    }
}

