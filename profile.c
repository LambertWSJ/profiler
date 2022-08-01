#include "profile.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

profile_t *profile_init()
{
    profile_t *profiler = malloc(sizeof(profile_t));
    profiler->size = 0;
    profiler->top = 0;
    return profiler;
}

static time_t duration(struct timespec start, struct timespec end)
{
    return end.tv_nsec - start.tv_nsec +
           (end.tv_sec - start.tv_sec) * 1000000000;
}

static item_t *item_init(char *label)
{
    item_t *item = malloc(sizeof(item_t));
    memset(item, 0, sizeof(item_t));
    item->time = 0;
    item->count = 1;
    item->label = label;

    return item;
}

static item_t *find_or_add_item(profile_t *profiler, char *label)
{
    item_t **items = profiler->items;
    item_t *item = NULL;
    for (int i = 0; i < profiler->size; i++) {
        if (!strcmp(items[i]->label, label)) {
            items[i]->count++;
            return items[i];
        }
    }
    item = item_init(label);
    profiler->items[profiler->size++] = item;
    return item;
}

void profile_start(profile_t *profiler, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    size_t label_len = 50 * sizeof(char);
    char *label = (char *) malloc(label_len);
    vsnprintf(label, label_len, fmt, args);
    va_end(args);

    item_t *item = find_or_add_item(profiler, label);
    profiler->stack[++profiler->top] = item;
    profiler->cur = item;
}

void profile_end(profile_t *profiler)
{
    profiler->cur->time += duration(profiler->cur->start, profiler->cur->end);
    profiler->cur = profiler->stack[--profiler->top];
}

static int cmp(const void *arg1, const void *arg2)
{
    item_t a = *(item_t *) arg1;
    item_t b = *(item_t *) arg2;
    return b.time - a.time;
}

void profile_log(profile_t *profiler, char *log_file, char *opt_prog_name)
{
    FILE *file = fopen(log_file, "w");
    size_t size = profiler->size;
    item_t *_items[size];

    memcpy(_items, profiler->items, sizeof(item_t *) * size);

    qsort(_items, size, sizeof(item_t *), cmp);
    fprintf(file, "program: %s\n", opt_prog_name);
    fprintf(file, "-------------------------------------------------\n");
    fprintf(file, "%15s%10s%13s\n", "function", "count", "time(sec)");
    fprintf(file, "-------------------------------------------------\n");

    for (size_t i = 0; i < size; i++) {
        item_t *item = _items[i];
        fprintf(file, "%-20s%-12lu%-10.9f\n", item->label, item->count,
                item->time / 1e9);
    }
    fclose(file);
}

void profile_delete(profile_t *profiler)
{
    if (!profiler)
        return;
    size_t size = profiler->size;
    for (size_t i = 0; i < size; i++) {
        free(profiler->items[i]->label);
        free(profiler->items[i]);
    }
    free(profiler);
}
