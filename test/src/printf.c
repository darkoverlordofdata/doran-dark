char *custom_vasprintf(TALLOC_CTX *ctx, char const *fmt, va_list ap)
{
    char const  *p = fmt, *end = p + strlen(fmt), *fmt_p = p, *fmt_q = p;
    char        *out = NULL, *out_tmp;
    va_list     ap_p, ap_q;

    out = talloc_strdup(ctx, "");
    va_copy(ap_p, ap);
    va_copy(ap_q, ap_p);

    do {

        char        *q;
        char        *custom;
        char        len[2] = { '\0', '\0' };
        long        width = 0, group = 0, precision = 0, tmp;

        if ((*p != '%') || (*++p == '%')) {
            fmt_q = p + 1;
            continue;   /* literal char */
        }

        /*
         *  Check for parameter field
         */
        tmp = strtoul(p, &q, 10);
        if ((q != p) && (*q == '$')) {
            group = tmp;
            p = q + 1;
        }

        /*
         *  Check for flags
         */
        do {
            switch (*p) {
            case '-':
                continue;

            case '+':
                continue;

            case ' ':
                continue;

            case '0':
                continue;

            case '#':
                continue;

            default:
                goto done_flags;
            }
        } while (++p < end);
    done_flags:

        /*
         *  Check for width field
         */
        if (*p == '*') {
            width = va_arg(ap_q, int);
            p++;
        } else {
            width = strtoul(p, &q, 10);
            p = q;
        }

        /*
         *  Check for precision field
         */
        if (*p == '.') {
            p++;
            precision = strtoul(p, &q, 10);
            p = q;
        }

        /*
         *  Length modifiers
         */
        switch (*p) {
        case 'h':
        case 'l':
            len[0] = *p++;
            if ((*p == 'h') || (*p == 'l')) len[1] = *p++;
            break;

        case 'L':
        case 'z':
        case 'j':
        case 't':
            len[0] = *p++;
            break;
        }

        /*
         *  Types
         */
        switch (*p) {
        case 'i':                               /* int */
        case 'd':                               /* int */
        case 'u':                               /* unsigned int */
        case 'x':                               /* unsigned int */
        case 'X':                               /* unsigned int */
        case 'o':                               /* unsigned int */
            switch (len[0]) {
            case 'h':
                if (len[1] == 'h') {                    /* char (promoted to int) */
                    (void) va_arg(ap_q, int);
                } else {
                    (void) va_arg(ap_q, int);           /* short (promoted to int) */
                }
                break;

            case 'L':
                if ((*p == 'i') || (*p == 'd')) {
                    if (len [1] == 'L') {
                        (void) va_arg(ap_q, long);      /* long */
                    } else {
                        (void) va_arg(ap_q, long long);     /* long long */
                    }
                } else {
                    if (len [1] == 'L') {
                        (void) va_arg(ap_q, unsigned long); /* unsigned long */
                    } else {
                        (void) va_arg(ap_q, unsigned long long);/* unsigned long long */
                    }
                }
                break;

            case 'z':
                (void) va_arg(ap_q, size_t);                /* size_t */
                break;

            case 'j':
                (void) va_arg(ap_q, intmax_t);              /* intmax_t */
                break;

            case 't':
                (void) va_arg(ap_q, ptrdiff_t);             /* ptrdiff_t */
                break;

            case '\0':  /* no length modifier */
                if ((*p == 'i') || (*p == 'd')) {
                    (void) va_arg(ap_q, int);           /* int */
                } else {
                    (void) va_arg(ap_q, unsigned int);      /* unsigned int */
                }
            }
            break;

        case 'f':                               /* double */
        case 'F':                               /* double */
        case 'e':                               /* double */
        case 'E':                               /* double */
        case 'g':                               /* double */
        case 'G':                               /* double */
        case 'a':                               /* double */
        case 'A':                               /* double */
            switch (len[0]) {
            case 'L':
                (void) va_arg(ap_q, long double);           /* long double */
                break;

            case 'l':   /* does nothing */
            default:    /* no length modifier */
                (void) va_arg(ap_q, double);                /* double */
            }
            break;

        case 's':
            (void) va_arg(ap_q, char *);                    /* char * */
            break;

        case 'c':
            (void) va_arg(ap_q, int);                   /* char (promoted to int) */
            break;

        case 'p':
            (void) va_arg(ap_q, void *);                    /* void * */
            break;

        case 'n':
            (void) va_arg(ap_q, int *);                 /* int * */
            break;

        /*
         *  Custom types
         */
        case 'v':
        {
            value_box_t const *value = va_arg(ap_q, value_box_t const *);

            /*
             *  Allocations that are not part of the output
             *  string need to occur in the NULL ctx so we don't fragment
             *  any pool associated with it.
             */
            custom = value_box_asprint(NULL, value->type, value->datum.enumv, value, '"');
            if (!custom) {
                talloc_free(out);
                return NULL;
            }

        do_splice:
            /*
             *  Pass part of a format string to printf
             */
            if (fmt_q != fmt_p) {
                char *sub_fmt;

                sub_fmt = talloc_strndup(NULL, fmt_p, fmt_q - fmt_p);
                out_tmp = talloc_vasprintf_append_buffer(out, sub_fmt, ap_p);
                talloc_free(sub_fmt);
                if (!out_tmp) {
                oom:
                    fr_strerror_printf("Out of memory");
                    talloc_free(out);
                    talloc_free(custom);
                    va_end(ap_p);
                    va_end(ap_q);
                    return NULL;
                }
                out = out_tmp;

                out_tmp = talloc_strdup_append_buffer(out, custom);
                TALLOC_FREE(custom);
                if (!out_tmp) goto oom;
                out = out_tmp;

                va_end(ap_p);       /* one time use only */
                va_copy(ap_p, ap_q);    /* already advanced to the next argument */
            }

            fmt_p = p + 1;
        }
            break;

        case 'b':
        {
            uint8_t const *bin = va_arg(ap_q, uint8_t *);

            /*
             *  Only automagically figure out the length
             *  if it's not specified.
             *
             *  This allows %b to be used with stack buffers,
             *  so long as the length is specified in the format string.
             */
            if (precision == 0) precision = talloc_array_length(bin);

            custom = talloc_array(NULL, char, (precision * 2) + 1);
            if (!custom) goto oom;
            fr_bin2hex(custom, bin, precision);

            goto do_splice;
        }

        default:
            break;
        }
        fmt_q = p + 1;
    } while (++p < end);

    /*
     *  Print out the rest of the format string.
     */
    if (*fmt_p) {
        out_tmp = talloc_vasprintf_append_buffer(out, fmt_p, ap_p);
        if (!out_tmp) goto oom;
        out = out_tmp;
    }

    va_end(ap_p);
    va_end(ap_q);

    return out;
}