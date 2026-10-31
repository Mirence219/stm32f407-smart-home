#ifndef DEBUG_PAGE_H
#define DEBUG_PAGE_H

#include "page.h"
#include "text.h"
#include "background.h"

class DebugPage : public Page {
private:
    static const uint8_t INPUT_FIELD_COUNT = 18;
    Background bg;
    Text title;
    Text input_fields[INPUT_FIELD_COUNT];

public:
    void init(ModelSnapShot* model_snap_shot) override;
    void update(ModelSnapShot* model_snap_shot) override;
};

#endif
