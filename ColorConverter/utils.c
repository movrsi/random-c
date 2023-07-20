#include "utils.h"

static const size_t RGB_SIZE = 12;
static const size_t HEX_SIZE = 8;
static char *DELIMITER = ",";
static const long long COLOR_MIN = 0LL;
static const long long COLOR_MAX = 255LL;

// Based slightly on the routine found in OpenBSD's libc.
#ifndef __OpenBSD__
static long strtonum(const char *numstr, const long long minval, const long long maxval)
{
    long value = 0;

    if (minval > maxval)
        return 0;

    if ((value = strtol(numstr, NULL, 10)) == 0)
        return 0;

    return value;
}
#endif

char *hex_to_rgb(const char *color)
{
    long value;
    char *ret;

    if ((ret = malloc(RGB_SIZE)) == NULL)
        return NULL;

    memset(ret, 0, RGB_SIZE);

    // increment the pointer if the hashtag is present.
    if (*color == '#')
        (void) *color++;

    if ((value = strtol(color, NULL, 16)) == 0) {
        free(ret);
        return NULL;
    }

    (void) snprintf(ret, RGB_SIZE, "%d,%d,%d", ((value >> 16) & 0xFF), ((value >> 8) & 0xFF), (value & 0xFF));
    return ret;
}

char *rgb_to_hex(char color[])
{
    char *ret, *pt;
    unsigned int hex, colors[3];
    int i;

    if ((ret = malloc(8)) == NULL)
        return NULL;

    memset(ret, 0, 8);

    if ((pt = strtok(color, ",")) == NULL) {
        free(ret);
        return NULL;
    }

    for (i = 0; i < 3; i++)
    {
        colors[i] = strtonum(pt, 0, 255);

        if ((pt = strtok(NULL, ",")) == NULL)
            break;
    }

    hex = colors[0] << 16 | colors[1] << 8 | colors[2];

    (void) snprintf(ret, 8, "#%06x", hex);

    return ret;
}
