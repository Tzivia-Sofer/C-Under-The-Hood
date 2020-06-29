#include <stdio.h>
#include "material.h"


void doMaterials()
{
    printf("\n--- Start doMaterials() ---\n\n");

    Materials mat;
    printf("Size of Materials: %lu\n", sizeof(Materials));
    printf("Size of mat: %lu\n", sizeof(mat));
    printf("Size of Materials::Types: %lu\n",sizeof(enum Types));
    printf("Size of Material_t: %lu\n", sizeof(Material_t));

    struct MatTest { Materials mat; Material_t mat_t; };
    printf("Size of Materials + Material_t: %lu\n", sizeof(struct MatTest));

    Material_t mat1;
    ctor_material_t_st(&mat1, OTHER);
    Material_t mat2;
    ctor_material_t_st(&mat2,METAL);

    printf("\n--- End doMaterials() ---\n\n");
}
void doPhysicalBox()
{
    printf("\n--- Start doPhysicalBox() ---\n\n");

    PhysicalBox pb1;
    ctor_physicalBox_sddde(&pb1,8, 6, 4, PLASTIC);
    PhysicalBox pb2;
    ctor_physicalBox_st(&pb2,WOOD);
    PhysicalBox pb3;
    ctor_physicalBox_sddd(&pb3,7, 7, 7);

    printf("\npb4 is copy-constructed from pb1\n");
    PhysicalBox pb4 = pb1;
    physicalBox_print_cs(&pb4);
    physicalBox_print_cs(&pb1);
    printf("pb4 %s pb1\n", box_isEqual7_ss((const Box*)&pb4,(const Box*)&pb1)&&
    (pb1.material_t.material==pb4.material_t.material) ? "equals" : "does not equal");

    printf("\npb4 is copy-assigned from pb3\n");
    pb4 = pb3;
    physicalBox_print_cs(&pb4);
    physicalBox_print_cs(&pb3);
    printf("pb4 %s pb3\n",  box_isEqual7_ss((const Box*)&pb4,(const Box*)&pb3)&&
    (pb3.material_t.material==pb4.material_t.material) ? "equals" : "does not equal");

    printf("\n--- End doPhysicalBox() ---\n\n");
    dtor_physicalBox_s(&pb1);
    dtor_physicalBox_s(&pb2);
    dtor_physicalBox_s(&pb3);
    dtor_physicalBox_s(&pb4);
}
void doWeightBox()
{
    printf("\n--- Start doWeightBox() ---\n\n");

    WeightBox pw1;
    ctor_weightBox_sdddd(&pw1,8, 6, 4, 25);
    WeightBox pw2;
    ctor_weightBox_sdddd(&pw2, 1,2, 3,0);
    WeightBox pw3;
    ctor_weightBox_sdddd(&pw3,10, 20, 30, 15);

    printf("\npw4 is copy-constructed from pw1\n");
    WeightBox pw4 =copy_ctor_weightBox_ss(&pw1);
    weightBox_print_s(&pw4);
    weightBox_print_s(&pw1);
    printf("pw4 %s pw1\n", box_isEqual7_ss((const Box*)&pw1,(const Box*)&pw4)&&(pw1.weight==pw4.weight)
    ? "equals" : "does not equal");

    printf("\npw4 is copy-assigned from pw3\n");
    weightBox_assign(&pw4, &pw3);
    weightBox_print_s(&pw4);
    weightBox_print_s(&pw3);
    printf("pw4 %s pw3\n", box_isEqual7_ss((const Box*)&pw3,(const Box*)&pw4)&&(pw3.weight==pw4.weight) ? "equals" : "does not equal");

    printf("\n--- End doWeightBox() ---\n\n");
    dtor_weightBox_s(&pw1);
    dtor_weightBox_s(&pw2);
    dtor_weightBox_s(&pw3);
    dtor_weightBox_s(&pw4);
}


int main()
{
    printf("\n--- Start main() ---\n\n");

    doMaterials();

    doPhysicalBox();

    doWeightBox();

    printf("\n--- End main() ---\n\n");

}
