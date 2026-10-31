#ifndef PAGE4_H
#define PAGE4_H

#include "page.h"
#include "background.h"
#include "button_widget.h"
#include "text.h"

class Page4 : public Page {
private:
    Background background;
    Text header[4];
    Text title;
    Text description[2];
    ButtonWidget automation[2];

public:
    void init(ModelSnapShot* model_snap_shot) override;
    void update(ModelSnapShot* model_snap_shot) override;
};

#endif
