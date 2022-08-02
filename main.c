#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "profile.h"

typedef struct block {
    uint32_t pc_start;
    uint32_t insts;
} block_t;


int main(int argc, char **argv)
{
    profile_t *profiler = profile_init();
    block_t *blocks[10];
    for (size_t i = 0; i < 10; i++)
    {
        block_t *block = malloc(sizeof(block_t));
        block->insts = rand() % 0x10000;
        block->pc_start = rand() % 0x10000;
        blocks[i] = block;
    }
    measure_start(__LINE__, "loop");
    for (size_t i = 0; i < 10; i++)
    {
        block_t *block = blocks[i];
        measure_start(block->pc_start, "block_%u_%u", block->pc_start, block->insts);
        usleep(100 * (rand() % 10000));
        measure_end;
    }
    measure_end;

    profile_log(profiler, "profile.log", "nested profile");
    profile_delete(profiler);
    return 0;
}