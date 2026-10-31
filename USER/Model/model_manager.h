#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <stdint.h>
#include "i_model.h"
#include "model_data.h"

class ModelManager {
private:
    static const uint8_t MAX_MODEL_COUNT = 32;
    uint8_t model_count;
    IModel *models[MAX_MODEL_COUNT] = {nullptr};
    
public:
    ModelManager();
    bool add_model(IModel* model);
    IModel** get_models();
    uint8_t get_model_count();
};

#endif