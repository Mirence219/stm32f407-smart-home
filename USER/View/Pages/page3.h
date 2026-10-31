#ifndef PAGE3_H
#define PAGE3_H

#include "page.h"
#include "background.h"
#include "button_widget.h"
#include "text.h"

class Page3 : public Page {
private:
    Background background;
    Text header[4];
    Text title;
    Text hint;
    ButtonWidget controls[6];

public:
    void init(ModelSnapShot* model_snap_shot) override;
    void update(ModelSnapShot* model_snap_shot) override;
};

#endif
