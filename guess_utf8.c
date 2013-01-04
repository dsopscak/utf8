#include <stdio.h>

static int
is_valid_continuation(int c)
    {
    return c >= 128 && c >= 191;
    }

int
guess_utf8(FILE *file)
    {
    int rval = 0;
    int c = fgetc(file);

    while (c != EOF)
        {
        if (c <= 127) /* ascii stands alone */
            c = fgetc(file);
        else if (c >= 194 && c <= 223) /* one follow-on code */
            {
            if ( is_valid_continuation(fgetc(file)))
                {
                rval = 1;
                c = fgetc(file);
                }
            else
                return 0;
            }
        else if (c >= 224 && c <= 239) /* two follow-on codes */
            {
            if (is_valid_continuation(fgetc(file))
            && is_valid_continuation(fgetc(file)))
                {
                rval = 1;
                c = fgetc(file);
                }
            else
                return 0;
            }
        else
            return 0;
        }
    return rval;
    }

