#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <getopt.h>

#ifdef __OpenBSD__
#include <err.h>
#endif

// Define __dead for non OpenBSD platforms.
#ifndef __OpenBSD__
#define __dead __attribute__((noreturn))
#endif

#ifdef __OpenBSD__
extern char *__progname;
#endif

#if defined(_GNU_SOURCE)
const char * appname = program_invocation_name;
#endif

static void __dead usage(void);

int main(int argc, char **argv)
{
#ifdef __OpenBSD__
    if (pledge("stdio", NULL) == -1)
        err(1, "pledge");
#endif

    int c;
    char *color;

    while ((c = getopt (argc, argv, "h:r:")) != -1)
    {
        switch (c)
        {
        case 'h': {
            if (argc != 3)
                return -1;

            if ((color = rgb_to_hex(argv[2])) == NULL)
                return -1;

            puts(color);
            free(color);
            break;
        }
        case 'r':
            if ((color = hex_to_rgb(optarg)) == NULL)
                return -1;

            puts(color);
            free(color);
            break;
        default:
            usage();
            break;
        }
    }

    return 0;
}

static void __dead usage(void)
{
#ifdef __OpenBSD__
    (void) fprintf(stderr, "%s usage: [-hr]", __progname);
#endif
#if defined(_GNU_SOURCE)
    (void) fprintf(stderr, "%s usage: [-hr]", appname);
#endif
    exit(-1);
}
