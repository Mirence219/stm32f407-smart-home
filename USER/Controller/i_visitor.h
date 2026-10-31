#ifndef I_VISITOR_H
#define I_VISITOR_H

#include "model_data.h"

class IInputModel;
class IFunctionalModel;
class IOutputModel;

enum class ModelDataMode {
	READ,
	WRITE,
	UPDATE
};

class IVisitor {
public:
	virtual ~IVisitor() = default;
	virtual void visit(IInputModel* model, ModelDataMode mode) = 0;
	virtual void visit(IFunctionalModel* model, ModelDataMode mode) = 0;
	virtual void visit(IOutputModel* model, ModelDataMode mode) = 0;
};

#endif