# simple C profiler

## features
* support nested expression
* output profile data
* format profile label

## issue
sort profile item by time is not correct

## Demo
```c
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
```

save profile as profile.log

```txt
program: nested profile
-------------------------------------------------
       function     count    time(sec)
-------------------------------------------------
1 less than 5       1           1.000116053
0 less than 5       1           1.000061016
loop                1           17.000920875
2 less than 5       1           1.000090982
greater than 5      7           14.000591012
```