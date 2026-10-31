#ifndef PAGE2_H
#define PAGE2_H

#include "page.h"
#include "background.h"
#include "text.h"

class Page2 : public Page {
private:
    Background background;
    Text header[4];
    Text title;
    Text temperature;
    Text humidity;
    Text illumination;
    Text hint;

public:
    void init(ModelSnapShot* model_snap_shot) override;
    void update(ModelSnapShot* model_snap_shot) override;
};

#endif
