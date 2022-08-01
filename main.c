#include <stdint.h>
#include <stdio.h>
#include "profile.h"

int main(int argc, char **argv)
{
    profile_t *profiler = profile_init();
    measure_start("loop");
    for (int i = 0; i < 10; i++)
    {
        if (i < 3)
        {
            measure_start("%d less than 5", i);
            sleep(1);
            measure_end;
        }
        else
        {
            measure_start("greater than 5", i);
            sleep(2);
            measure_end;
        }
    }
    measure_end;
    profile_log(profiler, "profile.log", "nested profile");

    return 0;
}