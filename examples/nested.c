#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "profile.h"


int main(int argc, char **argv)
{
    profile_t *profiler = profile_init();
    measure_start(__LINE__, "loop");
    for (int i = 0; i < 10; i++) {
        char label[10];
        if (i < 3) {
            measure_start(__LINE__, "%d one", i);
            sleep(1);
            measure_end;
        } else if (i > 7 && i < 10) {
            measure_start(__LINE__, "%d three", i);
            sleep(1);
            measure_end;
        } else {
            measure_start(__LINE__, "%d two", i);
            sleep(1);
            measure_end;
        }
    }
    measure_end;
    profile_log(profiler, "profile.log", "nested profile");
    return 0;
    
    return 0;
}