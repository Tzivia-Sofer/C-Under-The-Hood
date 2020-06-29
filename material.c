#include <stdio.h>
#include "material.h"
#include "box.h"


const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };

const char* getName(enum Types type)
{
    return names[type];
}
void ctor_material_t_st(struct Material_t* mt ,enum Types mat )
{
     mt->material= mat;
     printf("Material created, set to %s\n", material_mt_name_cs(mt));
}
const char* material_mt_name_cs(const struct Material_t* const mt)
{
    return getName(mt->material);
}
void physicalBox_print_cs(const struct PhysicalBox* const this)
{
    printf("PhysicalBox, made of %s; ", material_mt_name_cs(&this->material_t));
    box_print5_s(&this->box);
}
void ctor_physicalBox_sddd(struct PhysicalBox* this,double l, double w, double h)
{
    box_ctor_box3_sddd(&this->box,l,w,h);
    ctor_material_t_st(&this->material_t,OTHER);
    physicalBox_print_cs(this);
}
void ctor_physicalBox_sddde(struct PhysicalBox* this, double l, double w, double h, enum Types t)
{
    box_ctor_box3_sddd(&this->box,l,w,h);
    ctor_material_t_st(&this->material_t,t);
    physicalBox_print_cs(this);
}
void ctor_physicalBox_st(struct PhysicalBox* this,enum Types t)
{
    box_ctor_box3_sd(&(this->box),1);
    ctor_material_t_st(&this->material_t,t);
    physicalBox_print_cs(this);
}
void dtor_physicalBox_s(struct PhysicalBox* this)
{
    printf("PhysicalBox dtor, %f x %f x %f, %s; ",
           this->box.length, this->box.width, this->box.height,
            material_mt_name_cs(&this->material_t));
    box_dtor_box3_s(&this->box);
}
void ctor_weightBox_sdddd(WeightBox* this,double l, double w, double h, double wgt)
{
    box_ctor_box3_sddd(&this->box,l,w,h);
    this->weight = wgt;
    weightBox_print_s(this);
}
WeightBox copy_ctor_weightBox_ss(const WeightBox* const other)
{
    WeightBox wb;
    box_ctor_box3_sd(&wb.box,1);
    wb.weight =other->weight;
    weightBox_print_s(&wb);
    return wb;
}

WeightBox* weightBox_assign(WeightBox* this,const WeightBox* const other)
{
    this->weight = other->weight;
    return this;
}
void dtor_weightBox_s(WeightBox* this)
{
    printf("Destructing WeightBox; ");
    weightBox_print_s(this);
    box_dtor_box3_s(&this->box);
}
void weightBox_print_s(const WeightBox* const this)
{
    printf("WeightBox, weight: %f; ", this->weight);
    box_print5_s(&this->box);
}


