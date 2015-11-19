//
// Created by Martin on 17. 11. 2015.
//

#include <src/loaders/tiny_obj_loader.h>
#include "src/models/TexturedModel.hpp"

TexturedModel::TexturedModel() {
}

bool TexturedModel::operator<( const TexturedModel& r ) const
{
    return (mesh_indices_count < r.mesh_indices_count
            && mesh_t->indices < r.mesh_t->indices
            && mesh_t->material_ids < r.mesh_t->material_ids
            && mesh_t->normals < r.mesh_t->normals
            && mesh_t->positions < r.mesh_t->positions
            && mesh_t->texcoords < r.mesh_t->texcoords);
}

