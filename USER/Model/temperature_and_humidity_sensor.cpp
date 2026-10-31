#include "temperature_and_humidity_sensor.h"
#include "dht11.h"
#include "Timer.h"

TemperatureAndHumiditySensor::TemperatureAndHumiditySensor(GPIO_TypeDef *port, uint16_t pin)
	:port(port), pin(pin), last_sample_ms(0)
{
}

bool TemperatureAndHumiditySensor::init()
{
	if (DHT11_Init(port, pin) != 0)
	{
		return false;
	}
	last_sample_ms = gt_get() - 1000U;
	return true;
}

void TemperatureAndHumiditySensor::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IInputModel*>(this), mode);
}

void TemperatureAndHumiditySensor::update()
{
	model_data.set(ModelData::DataName::READY, false);
	const uint32_t now = gt_get();
	if (static_cast<uint32_t>(now - last_sample_ms) < 1000U)
	{
		return;
	}
	last_sample_ms = now;
	uint16_t temp = 0;
	uint16_t humi = 0;
	if (DHT11_Read_Data(&temp, &humi) == 0)
	{
		model_data.set(ModelData::DataName::TEMPERATURE, (float)temp / 10.0f);
		model_data.set(ModelData::DataName::HUMIDITY, (float)humi / 10.0f);
	}
}
