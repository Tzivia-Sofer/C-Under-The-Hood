#include <stdio.h>
#include "box.h"

extern const char* message;

void doBoxes()
{
    printf("\n--- Start doBoxes() ---\n\n");

    struct Box b1;
    box_ctor_box3_sd(&b1,3.0);
    struct Box b2;
    box_ctor_box3_sddd(&b2,4.0, 5.0, 6.0);

    printf("b1 volume: %f\n", b1.width * b1.length * b1.height);
    printf("b2 volume: %f\n", b2.width * b2.length * b2.height);

    box_mulEqual8_sd(&b1 ,1.5);
    box_mulEqual8_sd(&b2 ,0.5);

    printf("b1 volume: %f\n", b1.width * b1.length * b1.height);
    printf("b2 volume: %f\n", b2.width * b2.length * b2.height);

    struct Box b3 = b2;
    struct Box b4 = box_mul3_ds(3 , &b2);
    printf("b3 %s b4\n", box_isEqual7_ss(&b3, &b4) ? "equals" : "does not equal");

    box_mulEqual8_sd(&b3 ,1.5);
    box_mulEqual8_sd(&b4 ,0.5);
    printf("Now, b3 %s b4\n", box_isEqual7_ss(&b3, &b4) ? "equals" : "does not equal");

    printf("\n--- End doBoxes() ---\n\n");
    box_dtor_box3_s(&b1);
    box_dtor_box3_s(&b2);
    box_dtor_box3_s(&b3);
    box_dtor_box3_s(&b4);
}

static Box largeBox;
static Box box99;
static Box box88;

void thisFunc8_v()
{
    printf("\n--- thisFunc() ---\n\n");
    if(box99.height == 0)
    {
        box_ctor_box3_sddd(&box99,99, 99, 99);
    }
    box_mulEqual8_sd(&box99,10);
}
void thatFunc8_v()
{
    printf("\n--- thatFunc() ---\n\n");
    if(box88.height == 0)
    {
        box_ctor_box3_sddd(&box88,88, 88, 88);
    }
    box_mulEqual8_sd(&box88,10);
}
void doShelves()
{
    printf("\n--- start doShelves() ---\n\n");

    struct Box aBox;
    box_ctor_box3_sd(&aBox,5);

    struct Shelf aShelf;
    for(int i=0; i<NUM_BOXES;i++)
    {
        struct Box b1;
        box_ctor_box3_sd(&b1,1);
        aShelf.boxes[i]=b1;
    }

    shelf_print5_s(&aShelf);
    shelf_setBox11_is(&aShelf,1,&largeBox);
    shelf_setBox11_is(&aShelf,0,&aBox);

    shelf_print5_s(&aShelf);
    message = "This is the total volume on the shelf:";
    shelf_print5_s(&aShelf);
    message = "Shelf's volume:";
    shelf_print5_s(&aShelf);

    struct Box b5;
    box_ctor_box3_sddd(&b5,2.0, 4.0, 6.0);
    shelf_setBox11_is(&aShelf,1,&b5);
    box_dtor_box3_s(&b5);

    struct Box b6;
    box_ctor_box3_sd(&b6,2.0);
    shelf_setBox11_is(&aShelf,2, &b6);
    shelf_print5_s(&aShelf);
    box_dtor_box3_s(&b6);

    printf("\n--- end doShelves() ---\n\n");

    box_dtor_box3_s(&aBox);
    for(int i=0; i<NUM_BOXES;i++)
    {
        box_dtor_box3_s(&aShelf.boxes[i]);
    }
}
int main()
{
    box_ctor_box3_sddd(&largeBox,10, 20, 30);
    printf("\n--- Start main() ---\n\n");
    doBoxes();

    thisFunc8_v();
    thisFunc8_v();
    thisFunc8_v();
    thatFunc8_v();
    thatFunc8_v();

    doShelves();

    printf("\n--- End main() ---\n\n");
    box_dtor_box3_s(&largeBox);
    box_dtor_box3_s(&box99);
    box_dtor_box3_s(&box88);
    return 0;
}
