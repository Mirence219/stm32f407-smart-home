#ifndef I_MODEL_H
#define I_MODEL_H

#include "i_visitor.h"
#include "model_data.h"

class IModel {
public:
	virtual ~IModel() = default;
	virtual bool init() = 0;
	virtual ModelData& get_model_data() = 0;
	virtual void accept(IVisitor* visitor, ModelDataMode mode) = 0;
};

#endif
