#ifndef _FREDRIC_POINT_H_
#define _FREDRIC_POINT_H_

struct point_t {
    float x;
    float y;
};

struct parking_lot_t {
    point_t p0;
    point_t p1;
    point_t p2;
    point_t p3;
};
#endif