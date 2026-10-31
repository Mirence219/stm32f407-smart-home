#include "model_snap_shot.h"

ModelSnapShot::ModelSnapShot()
{
    for (uint8_t i = 0; i < static_cast<uint8_t>(ModelType::TYPE_COUNT); ++i)
    {
        model_data[i] = ModelData(static_cast<ModelType>(i));
    }
}

bool ModelSnapShot::update(const ModelData& data)
{
    const uint8_t model_index = static_cast<uint8_t>(data.get_model_type());
    if (model_index >= static_cast<uint8_t>(ModelType::TYPE_COUNT))
    {
        return false;
    }

    model_data[model_index] = data;
    return true;
}

ModelData ModelSnapShot::get(ModelType model_type) const
{
    const uint8_t model_index = static_cast<uint8_t>(model_type);
    if (model_index >= static_cast<uint8_t>(ModelType::TYPE_COUNT))
    {
        return ModelData();
    }

    return model_data[model_index];
}
