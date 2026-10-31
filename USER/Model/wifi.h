#ifndef WIFI_H
#define WIFI_H

#include <stdint.h>

#include "i_functional_model.h"
#include "model_data.h"
#include "mqtt_handle.h"
#include "timer.h"
#include "esp8266.h"
//#include "usart6.h"

class Wifi : public IFunctionalModel {
private:
	ModelData model_data;

public:
	Wifi();
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override
	{
		if (data.get_model_type() == model_data.get_model_type())
		{
			model_data = data;
		}
	}
	void update() override;
	void send(uint8_t* data, uint16_t length);
};

#endif
