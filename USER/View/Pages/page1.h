#ifndef PAGE1_H
#define PAGE1_H

#include "page.h"
#include "background.h"
#include "button_widget.h"
#include "text.h"

class Page1 : public Page {
private:
    Background background;
    Text header[4];
    Text title;
    Text subtitle;
    ButtonWidget navigation[3];

public:
    void init(ModelSnapShot* model_snap_shot) override;
};

#endif
