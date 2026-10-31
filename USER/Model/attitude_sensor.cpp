#include "attitude_sensor.h"

bool AttitudeSensor::init()
{
	return false;
}

void AttitudeSensor::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IInputModel*>(this), mode);
}

void AttitudeSensor::update()
{
	model_data.set(ModelData::DataName::READY, false);
}