#ifndef custom_clock_hpp
#define custom_clock_hpp

#include "time.h"

void reset_clock(clock_t* clock_delta) {
    (*clock_delta) = clock() - (*clock_delta);
}

void time_taken(clock_t time_delta, double* time) {
    (*time) = ((double)time_delta) / CLOCKS_PER_SEC;
}

#endif
