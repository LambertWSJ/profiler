#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "map.h"
#define ENABLE_PROFILE 1

typedef struct {
    char *label;
    size_t count;
    time_t time;
    struct timespec start, end;
} item_t;

typedef struct {
    map_t map;
    item_t *stack[100];
    item_t **items;
    size_t size;
    size_t capacity;
    int top;
    item_t *cur;
} profile_t;

profile_t *profile_init();
void profile_start(profile_t *profiler, uint32_t key, char *fmt, ...);
void profile_end(profile_t *profiler);
void profile_delete(profile_t *profiler);
void profile_log(profile_t *profiler, char *log_file, char *opt_prog_name);


#ifdef ENABLE_PROFILE

#define measure_start(key, fmt, ...)                  \
    profile_start(profiler, key, fmt, ##__VA_ARGS__); \
    clock_gettime(CLOCK_MONOTONIC, &profiler->cur->start);

#define measure_end                                      \
    clock_gettime(CLOCK_MONOTONIC, &profiler->cur->end); \
    profile_end(profiler);


#else

#define measure_start
#define measure_end

#endif