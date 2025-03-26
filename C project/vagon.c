#include "vagon.h"
#include "file_ops.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Wagon* create_wagon(int wagon_id) {
    Wagon* new_wagon = (Wagon*)malloc(sizeof(Wagon));
    if (new_wagon) {
        new_wagon->wagon_id = wagon_id;
        new_wagon->max_weight = 1000.0;
        new_wagon->current_weight = 0.0;
        new_wagon->loaded_materials = NULL;
        new_wagon->next = NULL;
        new_wagon->prev = NULL;
    }
    return new_wagon;
}

void add_wagon_to_train(Train* train) {
    Wagon* new_wagon = create_wagon(train->wagon_count + 1);
    if (!train->first_wagon) {
        train->first_wagon = new_wagon;
    } else {
        Wagon* temp = train->first_wagon;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_wagon;
        new_wagon->prev = temp;
    }
    train->wagon_count++;
}


void load_material_to_wagon(Train* train, MaterialType* material, int amount, int wagon_no){//Function for loading material starting from desired wagon
    if(amount + material->loaded > material->quantity){
        printf("There is no sufficent amount of material!");
    }

    else{
        int quantity = material->loaded;
        int weight = material->weight;

        if(amount > 0){ 

            for(int i = 0; i<amount; i++){
            
                Wagon* current = train->first_wagon;

                for(int j = 1; j<wagon_no; j++){//Go to the wagon specified by wagon_no variable
                    if(current && current->next){
                        current = current->next;
                    }
                    else{//If current wagon doesnt exist
                        add_wagon_to_train(train);
                        current = train->first_wagon;
                        while(current->next){
                            current = current->next;
                        }
                    }
                }

                LoadedMaterial* last_material = get_last_material(current); //Get last material in the current wagon
                if(last_material){
                    MaterialType* last_material_type = last_material->type;
                    while (current && (current->current_weight + weight > current->max_weight || weight > last_material_type->weight )){//Checks current wagon exists and the material is proper for loading
                        current = current->next;
                        if(current){
                            last_material = get_last_material(current);
                            if(last_material){
                            last_material_type = last_material->type;
                            }
                            else{
                                break;
                            }
                        }
                    }
                }

                if (!current) {
                    add_wagon_to_train(train);
                    current = train->first_wagon;
                    while (current->next) {
                        current = current->next;
                    }
                }

                LoadedMaterial* new_material = (LoadedMaterial*)malloc(sizeof(LoadedMaterial));
                new_material->type = material;
                new_material->next = NULL;
                new_material->prev = NULL;
                if(!current->loaded_materials){
                    current->loaded_materials = new_material;
                }

                else{
                    LoadedMaterial* temp = current->loaded_materials;
                    while(temp->next){
                        temp = temp->next;
                    }
                    temp->next = new_material;
                    new_material->prev = temp;
                }

                current->current_weight += material->weight;
                material->loaded++; 
            }
        }
        printf("Loaded %s successfully!\n", material->name);
    }
}


void load_material(Train* train, MaterialType* material, int amount) {

    if(amount + material->loaded > material->quantity){
        printf("There is no sufficent amount of material!\n");
    }

    else{
        int quantity = material->loaded;
        int weight = material->weight;

        if(amount > 0){ 

            for(int i = 0; i<amount; i++){
    
                Wagon* current = train->first_wagon;
                LoadedMaterial* last_material = get_last_material(current);
                if(last_material){
                    MaterialType* last_material_type = last_material->type;
                    while (current && (current->current_weight + weight > current->max_weight || weight > last_material_type->weight )){
                        current = current->next;
                        if(current){
                            last_material = get_last_material(current);
                            if(last_material){
                            last_material_type = last_material->type;
                            }
                            else{
                                break;
                            }
                        }
                    }
                }

                if (!current) {
                    add_wagon_to_train(train);
                    current = train->first_wagon;
                    while (current->next) {
                        current = current->next;
                    }
                }

                LoadedMaterial* new_material = (LoadedMaterial*)malloc(sizeof(LoadedMaterial));
                new_material->type = material;
                new_material->next = NULL;  // Initialize next pointer
                new_material->prev = NULL;
                if(!current->loaded_materials){
                    current->loaded_materials = new_material;
                }

                else{
                    LoadedMaterial* temp = current->loaded_materials;
                    while(temp->next){
                        temp = temp->next;
                    }

                    temp->next = new_material;
                    new_material->prev = temp;
                }

                current->current_weight += material->weight;
                material->loaded++;
            }
        }
        printf("Loaded %s successfully!\n", material->name);
    }
}