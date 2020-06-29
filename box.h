#ifndef __BOX__
#define __BOX__

#define NUM_BOXES 3

typedef struct Box{
    double length;
    double width;
    double height;
}Box;

void box_dtor_box3_s(const struct Box* const b);
struct Box* box_mulEqual8_sd(struct Box* b,double mult);
void box_ctor_box3_sd(struct Box* b,double dim);
void box_ctor_box3_sddd(struct Box* b,const double l, const double w, const double h);
void box_print5_s(const struct Box* const b);
struct Box box_mul3_sd(struct Box* b, double mult);
struct Box box_mul3_ds (double mult, struct Box* b);
int box_isEqual7_ss(const struct Box* const b1, const struct Box*const b2);
int box_diff4_ss(struct Box* b1, struct Box* b2);

typedef struct Shelf{
    Box boxes[NUM_BOXES];
}Shelf;

void shelf_setBox11_is(struct Shelf* s,int index, struct Box* b);
double shelf_getVolume11_s(const struct Shelf* const  s);
void shelf_print5_s(const struct Shelf* const  s);

#endif