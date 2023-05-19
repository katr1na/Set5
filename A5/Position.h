#ifndef POSITION_H
#define POSITION_H

struct Position {
    unsigned int r; // row
    unsigned int c; // column
    Position() {
        r = 0;
        c = 0;
    }
    Position(unsigned int i, unsigned int j) {
        r = i;
        c = j;
    }
};

#endif