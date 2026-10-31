#include "model_manager.h"

ModelManager::ModelManager() {
    model_count = 0;
}

bool ModelManager::add_model(IModel* model) {
    if (model == nullptr || model_count >= MAX_MODEL_COUNT)
    {
        return false;
    }

    models[model_count++] = model;
    return true;
}

IModel** ModelManager::get_models()
{
    return models;
}

uint8_t ModelManager::get_model_count()
{
    return model_count;
}