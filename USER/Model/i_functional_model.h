#ifndef I_FUNCTIONAL_MODEL_H
#define I_FUNCTIONAL_MODEL_H

#include "i_model.h"

class IFunctionalModel : public IModel {
public:
    virtual ~IFunctionalModel() = default;
	virtual void update() = 0;
    virtual void set_model_data(const ModelData& data) = 0;
};

#endif
