/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2023, movrsi
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *convert_remote_to_url(char *p)
{
    char *ret;
    size_t size;
    int i;

    if (p == NULL)
        return NULL;

    switch (*p) {
        case 'g': // indicates git@github.com
            size = strlen(p);
            if ((ret = malloc(size)) == NULL)
                return NULL;

            ret[0] = 'h';
            ret[1] = ret[2] = 't';
            ret[3] = 'p';
            ret[4] = 's';
            ret[5] = ':';
            ret[6] = ret[7] = '/';
            strncpy(ret + 8, p + 4, size - 4);

            for (i = 5; i < size; i++) {
               switch (ret[i]) {
                case ':':
                    ret[i] = '/';
                    break;
                default:
                    continue;
                }
            }

            ret[size] = '\0';
            break;
        case 'h': // indicates https
            size = strlen(p) - 4;
            if ((ret = malloc(size + 1)) == NULL)
                return NULL;

            strncpy(ret, p, size);
            ret[size + 1] = '\0';
            break;
    }

    return ret;
}

const char *TEST_VECTOR = "https://github.com/movrsi/Nuked-MD";

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
    char *git_remote = convert_remote_to_url("git@github.com:movrsi/Nuked-MD.git");
    char *git_https = convert_remote_to_url("https://github.com/movrsi/Nuked-MD.git");
    unsigned int ret = 0;

    ret |= str_equals(git_remote, TEST_VECTOR);
    ret |= str_equals(git_https, TEST_VECTOR);

    free(git_remote);
    free(git_https);
    return ret;
}
