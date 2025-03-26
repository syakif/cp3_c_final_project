#ifndef FILE_OPS_H
#define FILE_OPS_H
#include "train.h"

LoadedMaterial* get_last_material(Wagon* wagon);
MaterialType* large_box(const char* filename);
MaterialType* medium_box(const char* filename);
MaterialType* small_box(const char* filename);
void load_train_status(Train* train, const char* filename);
void save_to_file(Train* train, const char* filename, MaterialType* large_box, MaterialType* medium_box, MaterialType* small_box);

#endif