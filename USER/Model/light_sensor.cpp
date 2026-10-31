#include "light_sensor.h"
#include "bh1750.h"
#include "Timer.h"

bool LightSensor::init()
{
	if (!BH1750_Init())
	{
		return false;
	}
	last_sample_ms = gt_get() - 120U;
	return true;
}

void LightSensor::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IInputModel*>(this), mode);
}

void LightSensor::update()
{
	model_data.set(ModelData::DataName::READY, false);
	const uint32_t now = gt_get();
	if (static_cast<uint32_t>(now - last_sample_ms) < 120U)
	{
		return;
	}
	last_sample_ms = now;
	float lux = 0.0f;
	if (BH1750_Read_Lux(&lux))
	{
		model_data.set(ModelData::DataName::LIGHT_INTENSITY, lux);
	}
}
