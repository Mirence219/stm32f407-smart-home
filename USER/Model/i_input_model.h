#ifndef I_INPUT_MODEL_H
#define I_INPUT_MODEL_H

#include "i_model.h"

class IInputModel : public IModel {
public:
    virtual ~IInputModel() = default;
    virtual void update() = 0;
};

#endif
