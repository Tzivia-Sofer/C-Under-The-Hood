#ifndef __MATERIAL__
#define __MATERIAL__

#include "box.h"

//// Materials ////////////

enum Types {
    PLASTIC,
    METAL,
    WOOD,
    PAPER,
    OTHER
}Types;

typedef struct Materials {
    char c;
}Materials;

typedef struct Material_t{
    enum Types material;
}Material_t;

const char* getName(enum Types type);
void ctor_material_t_st(struct Material_t* mt,enum Types mat);
const char* material_mt_name_cs(const struct Material_t* const mt);



//// PhysicalBox ////////////

typedef struct PhysicalBox
{
    Box box;
    Material_t material_t;
}PhysicalBox;

void ctor_physicalBox_sddd(struct PhysicalBox*,double l, double w, double h);
void ctor_physicalBox_sddde(struct PhysicalBox*, double l, double w, double h, enum Types t);
void ctor_physicalBox_st(struct PhysicalBox*,enum Types t);
void dtor_physicalBox_s(struct PhysicalBox*);
void physicalBox_print_cs(const struct PhysicalBox* const);

//// WeightBox Defs ////////////

typedef struct WeightBox
{
     Box box;
     double weight;
}WeightBox;

void ctor_weightBox_sdddd(WeightBox*,double l, double w, double h, double wgt);
WeightBox copy_ctor_weightBox_ss(const WeightBox* const other);
void dtor_weightBox_s(WeightBox* this);
void weightBox_print_s(const WeightBox* const this);
WeightBox* weightBox_assign(WeightBox* this,const WeightBox* const other);


#endif

