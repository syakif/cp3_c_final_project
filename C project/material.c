#include "material.h"
#include "file_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display_materials_status(MaterialType* material_large, MaterialType* material_medium, MaterialType* material_small) {
    printf("\n");
    printf("Large Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_large->weight, material_large->quantity, material_large->loaded);
    printf("Medium Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_medium->weight, material_medium->quantity, material_medium->loaded);
    printf("Small Box, Weight: %.2f, Quantity: %d, Loaded: %d\n", material_small->weight, material_small->quantity, material_small->loaded);
    printf("\n");
}

void remove_material_node(Wagon* wagon, LoadedMaterial* material) {
    // Update the links
    if (material->prev) {
        material->prev->next = material->next;
    } else {
        wagon->loaded_materials = material->next;
    }
    
    if (material->next) {
        material->next->prev = material->prev;
    }
    
    // Update wagon's weight
    wagon->current_weight -= material->type->weight;
    
    free(material);
}

LoadedMaterial* find_material_in_wagon(Wagon* wagon, MaterialType* material) {
    LoadedMaterial* current = wagon->loaded_materials;
    
    // Start from the end
    while (current && current->next) {
        current = current->next;
    }
    
    // Go back to find the first matching material
    while (current) {
        if (current->type->weight == material->weight) {
            return current;
        }
        current = current->prev;
    }
    
    return NULL;
}

void unload_material(Train* train, MaterialType* material, int amount) {

    if (!train || !material || amount <= 0) {
        printf("Invalid parameters for unloading!\n");
        return;
    }
    
    // Checks if there is sufficent amount of wagon to unload
    if (amount > material->loaded) {
        printf("Trying to unload %d units but only %d are loaded!\n", 
               amount, material->loaded);
        return;
    }
    
    int unloaded = 0;
    Wagon* current_wagon = train->first_wagon;
    
    // Start from the last wagon
    while (current_wagon && current_wagon->next) {
        printf("1");
        current_wagon = current_wagon->next;
    }
    
    // Process wagons from back to front
    while (current_wagon && unloaded < amount) {
        printf("2");
        LoadedMaterial* material_to_unload = find_material_in_wagon(current_wagon, material);
        
        while (material_to_unload && unloaded < amount) {
            printf("3");
            
            LoadedMaterial* next_material = material_to_unload->next;
            LoadedMaterial* prev_material = material_to_unload->prev;
            
            //Checks if there any problem in locating boxes (heavy cant load on lighter rule)
            int can_remove = 1;
            if (next_material && prev_material) {
                if (prev_material->type->weight < next_material->type->weight) {
                    can_remove = 0;
                }
            }
            
            if (can_remove) {
                remove_material_node(current_wagon, material_to_unload);
                material->loaded--;
                unloaded++;
                
                // Find next material to unload in this wagon
                material_to_unload = find_material_in_wagon(current_wagon, material);
            } else {
                // Move to previous material in wagon
                material_to_unload = material_to_unload->prev;
            }
        }
        
        // Move to previous wagon
        current_wagon = current_wagon->prev;
    }
    
    if (unloaded < amount) {
        printf("Could only unload %d of %d requested units due to weight distribution constraints.\n",
               unloaded, amount);
    } else {
        printf("Successfully unloaded %d units of %s.\n", unloaded, material->name);
    }
}


void unload_material_from_wagon(Train* train, MaterialType* material, int amount, int wagon_no) {
   
    if (!train || !material || amount <= 0 || wagon_no < 1) {
        printf("Invalid parameters for unloading!\n");
        return;
    }

    if (amount > material->loaded) {
        printf("Trying to unload %d units but only %d are loaded!\n", 
               amount, material->loaded);
        return;
    }

    // Find the target wagon
    Wagon* target_wagon = train->first_wagon;
    for (int i = 1; i < wagon_no; i++) {
        if (!target_wagon) {
            printf("Wagon %d does not exist!\n", wagon_no);
            return;
        }
        target_wagon = target_wagon->next;
    }

    if (!target_wagon) {
        printf("Wagon %d does not exist!\n", wagon_no);
        return;
    }

    int unloaded = 0;
    LoadedMaterial* current = target_wagon->loaded_materials;
    
    // Move to the last material in the wagon
    while (current && current->next) {
        current = current->next;
    }

    while (current && unloaded < amount) {
        if (current->type == material) {
            LoadedMaterial* next_material = current->next;
            LoadedMaterial* prev_material = current->prev;
            LoadedMaterial* to_remove = current;
            
            // Move to previous material before removing current
            current = current->prev;

            int can_remove = 1;
            if (next_material && prev_material) {
                if (prev_material->type->weight < next_material->type->weight) {
                    can_remove = 0;
                }
            }

            if (can_remove) {
                // Update links
                if (prev_material) {
                    prev_material->next = next_material;
                } else {
                    target_wagon->loaded_materials = next_material;
                }
                
                if (next_material) {
                    next_material->prev = prev_material;
                }

                // Update weights and counts
                target_wagon->current_weight -= material->weight;
                material->loaded--;
                unloaded++;

                free(to_remove);
            }
        } else {
            current = current->prev;
        }
    }

    if (unloaded == 0) {
        printf("No matching materials found in wagon %d!\n", wagon_no);
    } else if (unloaded < amount) {
        printf("Could only unload %d of %d requested units from wagon %d.\n",
               unloaded, amount, wagon_no);
    } else {
        printf("Successfully unloaded %d units of %s from wagon %d.\n", 
               unloaded, material->name, wagon_no);
    }
}