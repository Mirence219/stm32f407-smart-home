#ifndef MODEL_READER_H
#define MODEL_READER_H

#include "model_manager.h"
#include "i_visitor.h"
#include "model_snap_shot.h"

class ModelVisitor : public IVisitor {
private:
    ModelManager *model_manager;
    ModelSnapShot *model_snap_shot;
    void visit_models(ModelDataMode mode);
public:
    ModelVisitor(ModelManager *model_manager, ModelSnapShot *model_snap_shot);
    void visit(IInputModel* model, ModelDataMode mode) override;
    void visit(IFunctionalModel* model, ModelDataMode mode) override;
    void visit(IOutputModel* model, ModelDataMode mode) override;
    void model_snap_shot_init();
    void read_model_data();
    void write_model_data();
    void update_models();
};

#endif
