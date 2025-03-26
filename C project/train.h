#ifndef TRAIN_H
#define TRAIN_H

// Struct for materials
typedef struct MaterialType {
    char name[20];  // e.g., "Large Box"
    float weight;   // Weight in kg
    int quantity;   // Total quantity available
    int loaded;     // Quantity currently loaded onto wagons
} MaterialType;

// Struct for loaded materials (doubly linked list)
typedef struct LoadedMaterial {
    MaterialType* type;              // Pointer to MaterialType
    struct LoadedMaterial *next, *prev; // Pointers for doubly linked list
} LoadedMaterial;

// Struct for wagons
typedef struct Wagon {
    int wagon_id;                     // Sequential ID for wagons
    float max_weight;                 // Maximum capacity of the wagon
    float current_weight;             // Current loaded weight
    LoadedMaterial* loaded_materials; // Linked list of loaded materials //first material in a wagon
    //LoadedMaterial* loaded_tail;
    struct Wagon *next, *prev;        // Pointers for doubly linked list
} Wagon;

typedef struct Train {
    char train_id[20];    
    Wagon* first_wagon;   
    int wagon_count;      
}Train;

void initialize_train(Train* train, const char* train_id);
void free_train(Train* train, MaterialType* material_large, MaterialType* material_medium, MaterialType* material_small);
void display_train_status(const Train* train);

#endif
