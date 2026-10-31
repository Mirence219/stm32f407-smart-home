#ifndef MODEL_SNAP_SHOT_H
#define MODEL_SNAP_SHOT_H

#include "model_data.h"

class ModelSnapShot
{
private:
    ModelData model_data[static_cast<uint8_t>(ModelType::TYPE_COUNT)];

public:
    ModelSnapShot();
    bool update(const ModelData& data);
    ModelData get(ModelType model_type) const;
};

#endif
