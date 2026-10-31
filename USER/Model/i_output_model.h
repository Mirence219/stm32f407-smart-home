#ifndef I_OUTPUT_MODEL_H
#define I_OUTPUT_MODEL_H

#include "i_model.h"

class IOutputModel : public IModel {
public:
    virtual ~IOutputModel() = default;
    virtual void set_model_data(const ModelData& data) = 0;
};

#endif
