#include "stdlib.h"
#include "../utils.h"

static char TEST_VECTOR_HEX[] = "255,255,255";
static char TEST_VECTOR_RGB[] = "#FFFFFF";

unsigned int str_equals(const char *src, const char *test)
{
    while (*src && *test)
    {
        // 1 ^ 1 = 0
        if ((*src ^ *test) != 0)
            return 0;

        (void) *src++;
        (void) *test++;
    }

    return 1;
}

int main()
{
    unsigned int ret = 0;

    char *hex_test = rgb_to_hex(TEST_VECTOR_HEX);
    char *rgb_test = hex_to_rgb(TEST_VECTOR_RGB);

    ret |= str_equals(hex_test, TEST_VECTOR_RGB);
    ret |= str_equals(rgb_test, TEST_VECTOR_HEX);

    free(hex_test);
    free(rgb_test);
    return ret;
}
