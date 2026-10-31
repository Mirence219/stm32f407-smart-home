#include "wifi.h"

Wifi::Wifi()
	: model_data(ModelType::WIFI)
{
	const uint8_t empty_buffer[64] = {};
	model_data.set_bytes(ModelData::DataName::RECV_BUF, empty_buffer, sizeof(empty_buffer));
}

bool Wifi::init()
{
	return false;
	//USART6_Hardware_Init(115200);
	//Platform_Auto_Login();
	//return model_data.set(ModelData::DataName::READY, false);
}

void Wifi::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IFunctionalModel*>(this), mode);
}

void Wifi::update()
{
	model_data.set(ModelData::DataName::READY, false);
}

void Wifi::send(uint8_t* data, uint16_t length)
{
}
