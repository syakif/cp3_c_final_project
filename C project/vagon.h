#ifndef VAGON_H
#define VAGON_H
#include "train.h"

Wagon* create_wagon(int wagon_id);
void add_wagon_to_train(Train* train);
void load_material_to_wagon(Train* train, MaterialType* material, int amount, int wagon_no);
void load_material(Train* train, MaterialType* material, int amount);

#endif
