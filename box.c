#include <stdio.h>
#include "box.h"

const char* const DEF_MSG = "The total volume held on the shelf is";
const char* message = "The total volume held on the shelf is";

void box_print5_s(const struct Box* const b)
{
    printf("Box: %f x %f x %f\n", b->length, b->width, b->height);
}
void box_ctor_box3_sd(struct Box* b,double dim)
{
    b->length = dim;
    b->height = dim;
    b->width = dim;
    box_print5_s(b);
}
void box_ctor_box3_sddd(struct Box* b,const double l, const double w, const double h)
{
    b->length = l;
    b->height = h;
    b->width = w;
    box_print5_s(b);
}
void box_dtor_box3_s(const struct Box* const b)
{
    printf("Box destructor, %f x %f x %f\n", b->width, b->height, b->length);
}
struct Box* box_mulEqual8_sd(struct Box* b,double mult)
{
    b->width *= mult;
    b->height *= mult;
    b->length *= mult;
    return b;
}
 struct Box box_mul3_sd(struct Box* b, double mult)
{
    struct Box *ret = b;
    return *box_mulEqual8_sd(ret ,mult);
}
 struct Box box_mul3_ds (double mult, struct Box* b)
{
    b->width *= mult;
    b->length *= mult;
    b->height *= mult;
    return *b;
}
 int box_isEqual7_ss(const struct Box* const b1, const struct Box*const b2)
{
    if(b1->width == b2->width && b1->height == b2->height && b1->length == b2->length)
        return 1;
    return 0;
}
 int box_diff4_ss(struct Box* b1, struct Box* b2)
{
    return !(box_isEqual7_ss(b1,b2));
}
void shelf_setBox11_is(struct Shelf* s, int index, struct Box* b)
{
    s->boxes[index] = *b;
}
double shelf_getVolume11_s(const struct Shelf* const  s)
{
    double vol = 0;
    for (int i = 0; i < NUM_BOXES; ++i)
        vol += s->boxes[i].width * s->boxes[i].length * s->boxes[i].height;
    return vol;
}
void shelf_print5_s(const struct Shelf* const  s)
{
    printf("%s %f\n", message, shelf_getVolume11_s(s));
}