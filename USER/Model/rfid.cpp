#include "rfid.h"

Rfid::Rfid()
	: model_data(ModelType::RFID)
{
	const uint8_t empty_card_id[4] = {};
	model_data.set_bytes(ModelData::DataName::CARD_ID, empty_card_id, sizeof(empty_card_id));
}

bool Rfid::init()
{
	return model_data.set(ModelData::DataName::READY, false);
}

void Rfid::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IFunctionalModel*>(this), mode);
}

void Rfid::update()
{
	model_data.set(ModelData::DataName::READY, false);
}
