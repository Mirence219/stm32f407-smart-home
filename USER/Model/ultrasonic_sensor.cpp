#include "ultrasonic_sensor.h"

bool UltrasonicSensor::init()
{
	return false;
}

void UltrasonicSensor::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IInputModel*>(this), mode);
}

void UltrasonicSensor::update()
{
	model_data.set(ModelData::DataName::READY, false);
}
