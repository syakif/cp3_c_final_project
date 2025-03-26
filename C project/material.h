#ifndef MATERIAL_H
#define MATERIAL_H

#include "train.h"

void display_materials_status(MaterialType* material_large, MaterialType* material_medium, MaterialType* material_small);
void remove_material_node(Wagon* wagon, LoadedMaterial* material);
LoadedMaterial* find_material_in_wagon(Wagon* wagon, MaterialType* material);
void unload_material(Train* train, MaterialType* material, int amount);
void unload_material_from_wagon(Train* train, MaterialType* material, int amount, int wagon_no);

#endif
