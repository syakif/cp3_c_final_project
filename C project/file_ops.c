#include "file_ops.h"
#include "train.h"
#include "vagon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LoadedMaterial* get_last_material(Wagon* wagon) {

    // Check if the wagon is null
    if (!wagon) {
        //printf("Error: Wagon is null.\n");
        return NULL;
    }

    // Check if no materials are loaded
    if (!wagon->loaded_materials) {
        printf("Wagon has no loaded materials.\n");
        return NULL;
    }

    LoadedMaterial* current = wagon->loaded_materials;
    while (current->next) {
        current = current->next;
    }
    return current;
}

MaterialType* large_box(const char* filename){ //Initialize the Large Boxes
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return NULL;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {

        if (strstr(buffer, "M:Large Box")){
            char material_name[20];
            float material_weight;
            int material_quantity;
            int material_loaded;
            sscanf(buffer, "M:%[^:]:%f:%d:%d", material_name, &material_weight, &material_quantity, &material_loaded);
            MaterialType* material = (MaterialType*)malloc(sizeof(MaterialType));
            strcpy(material->name, material_name);
            material->weight = material_weight;
            material->quantity = material_quantity;
            material->loaded = material_loaded;

            fclose(file);
            return material;
        }
    }
    fclose(file);
    return NULL;   
}

MaterialType* medium_box(const char* filename){//Initialize the Medium Boxes
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return NULL;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {

        if (strstr(buffer, "M:Medium Box")){
            char material_name[20];
            float material_weight;
            int material_quantity;
            int material_loaded;
            sscanf(buffer, "M:%[^:]:%f:%d:%d", material_name, &material_weight, &material_quantity, &material_loaded);
            MaterialType* material = (MaterialType*)malloc(sizeof(MaterialType));
            strcpy(material->name, material_name);
            material->weight = material_weight;
            material->quantity = material_quantity;
            material->loaded = material_loaded;

            fclose(file);
            return material;
        }
    }
    fclose(file);
    return NULL;  
}

MaterialType* small_box(const char* filename){//Initialize the Small Boxes
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return NULL;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {

        if (strstr(buffer, "M:Small Box")){
            char material_name[20];
            float material_weight;
            int material_quantity;
            int material_loaded;
            sscanf(buffer, "M:%[^:]:%f:%d:%d", material_name, &material_weight, &material_quantity, &material_loaded);
            MaterialType* material = (MaterialType*)malloc(sizeof(MaterialType));
            strcpy(material->name, material_name);
            material->weight = material_weight;
            material->quantity = material_quantity;
            material->loaded = material_loaded;

            fclose(file);
            return material;
        }
    }
    fclose(file);
    return NULL;   
}

void load_train_status(Train* train, const char* filename) {//Load train infos from file
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    char buffer[256];
    // Initialize train
    train->first_wagon = NULL;
    train->wagon_count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;
        printf("Read line: %s\n", buffer);

        if (strstr(buffer, "TRAIN")) {
            sscanf(buffer, "TRAIN:%[^:]:%d", train->train_id, &train->wagon_count);
        }
        
        else if (strstr(buffer, "WAGON")) {
            int wagon_id;
            float wagon_max;
            float wagon_current;
            sscanf(buffer, "WAGON:%d:%f:%f", &wagon_id, &wagon_max, &wagon_current);
            
            Wagon* vagon = (Wagon*)malloc(sizeof(Wagon));
            if (!vagon) {
                printf("Memory allocation failed for wagon\n");
                continue;
            }
            
            // Initialize all wagon fields
            vagon->wagon_id = wagon_id;
            vagon->max_weight = wagon_max;
            vagon->current_weight = wagon_current;
            vagon->loaded_materials = NULL;
            vagon->next = NULL;
            vagon->prev = NULL;

            // Add wagon to train
            if (!train->first_wagon) {
                train->first_wagon = vagon;
            } else {
                Wagon* temp = train->first_wagon;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = vagon;
                vagon->prev = temp;
            }
        }
        
        else if (strstr(buffer, "L:")) {//Find the Loaded Material section
            char material_name[20];
            int quantity; 
            sscanf(buffer, "L:%[^:]:%d", material_name, &quantity);
            
            MaterialType* material = NULL;

            if (strcmp(material_name, "Large Box") == 0) { 
                material = large_box(filename);
            } else if (strcmp(material_name, "Medium Box") == 0) {
                material = medium_box(filename);
            } else if (strcmp(material_name, "Small Box") == 0) {
                material = small_box(filename);
            }

            if (material) {
                LoadedMaterial* loaded = (LoadedMaterial*)malloc(sizeof(LoadedMaterial));
                if (!loaded) {
                    printf("Memory allocation failed for loaded material\n");
                    free(material);
                    continue;
                }
                
                // Initialize loaded materials
                loaded->type = material;
                loaded->next = NULL;
                loaded->prev = NULL;

                // Find the last wagon
                Wagon* vagon = train->first_wagon;
                while (vagon && vagon->next) {
                    vagon = vagon->next;
                }
                
                if (vagon) {
                    // Add loaded material to wagon
                    if (!vagon->loaded_materials) {
                        vagon->loaded_materials = loaded;
                    } else {
                        LoadedMaterial* temp = vagon->loaded_materials;
                        while (temp->next) {
                            temp = temp->next;
                        }
                        temp->next = loaded;
                        loaded->prev = temp;
                    }
                } else {
                    printf("No wagon available to load material\n");
                    free(loaded);
                    free(material);
                }
            } else {
                printf("Material not found: %s\n", material_name);
            }
        }
    }

    printf("Successfully loaded.\n");
    fclose(file);
}


void save_to_file(Train* train, const char* filename, MaterialType* large_box, MaterialType* medium_box, MaterialType* small_box){//save to file
    FILE* file = fopen(filename, "w");
    
    if(file){
        fprintf(file, "TRAIN:%s:%d\n", train->train_id, train->wagon_count);
        fprintf(file, "M:%s:%.2f:%d:%d\n", large_box->name, large_box->weight, large_box->quantity, large_box->loaded);
        fprintf(file, "M:%s:%.2f:%d:%d\n", medium_box->name, medium_box->weight, medium_box->quantity, medium_box->loaded);
        fprintf(file, "M:%s:%.2f:%d:%d\n", small_box->name, small_box->weight, small_box->quantity, small_box->loaded);
        Wagon* current = train->first_wagon;
        while(current){
            fprintf(file, "WAGON:%d:%.2f:%.2f\n", current->wagon_id, current->max_weight, current->current_weight);
            LoadedMaterial* current_material = current->loaded_materials;
            while(current_material){
                MaterialType* current_material_type = current_material->type;
                fprintf(file, "L:%s\n", current_material_type->name);
                current_material = current_material->next;
            }
            current = current->next;
        }
        fclose(file);
    }
    printf("Saved successfully!\n");
}