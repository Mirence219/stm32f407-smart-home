#include "model_visitor.h"
#include "i_input_model.h"
#include "i_functional_model.h"
#include "i_output_model.h"

ModelVisitor::ModelVisitor(ModelManager *model_manager, ModelSnapShot *model_snap_shot)
    : model_manager(model_manager), model_snap_shot(model_snap_shot)
{
}

//输入类：可读可更新
void ModelVisitor::visit(IInputModel *model, ModelDataMode mode)
{
    if (mode == ModelDataMode::READ)
    {
        model_snap_shot->update(model->get_model_data());
    }
    else if (mode == ModelDataMode::UPDATE)
    {
        model->update();
    }
}

//功能类：可读可写可更新
void ModelVisitor::visit(IFunctionalModel *model, ModelDataMode mode)
{
    if (mode == ModelDataMode::READ)
    {
        model_snap_shot->update(model->get_model_data());
    }
    else if (mode == ModelDataMode::WRITE)
    {
        model->set_model_data(model_snap_shot->get(model->get_model_data().get_model_type()));
    }
    else if (mode == ModelDataMode::UPDATE)
    {
        model->update();
    }
}

//输出类：可写
void ModelVisitor::visit(IOutputModel *model, ModelDataMode mode)
{
    if (mode == ModelDataMode::WRITE)
    {
        model->set_model_data(model_snap_shot->get(model->get_model_data().get_model_type()));
    }
}

void ModelVisitor::model_snap_shot_init()
{
    read_model_data();
    //这里未来补上读取flash配置输出类控件的初值
    write_model_data();
}

void ModelVisitor::visit_models(ModelDataMode mode)
{
    IModel **models = model_manager->get_models();
    for (uint8_t i = 0; i < model_manager->get_model_count(); i++)
    {
        if (models[i] == nullptr)
        {
            break;
        }
        models[i]->accept(this, mode);
    }
}

void ModelVisitor::read_model_data()
{
    visit_models(ModelDataMode::READ);
}

void ModelVisitor::write_model_data()
{
    visit_models(ModelDataMode::WRITE);
}

void ModelVisitor::update_models()
{
    visit_models(ModelDataMode::UPDATE);
}
