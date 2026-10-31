#include "pressure_sensor.h"

bool PressureSensor::init()
{
	return false;
}

void PressureSensor::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IInputModel*>(this), mode);
}

void PressureSensor::update()
{
	model_data.set(ModelData::DataName::READY, false);
}
