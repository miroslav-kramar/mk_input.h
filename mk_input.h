/*
WARNING
THIS FILE IS GENERATED FROM A TEMPLATE
CHANGES MADE HERE ARE NOT PERSISTENT
GENERATED AT Feb 22 2026 16:08:52 FROM "gen.c"
*/

#ifndef MK_INPUT_H_
#define MK_INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include <ctype.h>
#include <errno.h>

typedef enum {
    MK_STATUS_OK,
    MK_STATUS_EOF,
    MK_STATUS_ERROR_SYSTEM,
    MK_STATUS_ERROR_FORMAT,
    MK_STATUS_ERROR_OUT_OF_RANGE,
} MkStatus;

typedef struct {
    FILE * istream;
    MkStatus status;
    bool newline_found;
    bool scanned_anything;
    const char * delimiter;
} MkScanner;

static const char * const MK_DEFAULT_DELIM = " \f\n\r\t\v";

static inline const char * mk_status_get_string(const MkStatus status) {
    switch (status) {
        case MK_STATUS_OK: return "MK_STATUS_OK";
        case MK_STATUS_EOF: return "MK_STATUS_EOF";
        case MK_STATUS_ERROR_SYSTEM: return "MK_STATUS_ERROR_SYSTEM";
        case MK_STATUS_ERROR_FORMAT: return "MK_STATUS_ERROR_FORMAT";
        case MK_STATUS_ERROR_OUT_OF_RANGE: return "MK_STATUS_ERROR_OUT_OF_RANGE";
        default: return "Unknown Status";
    }
}

static inline MkScanner mk_scanner_create(FILE * istream, const char * delimiter) {
    MkScanner out;
    out.istream = istream;
    out.status = MK_STATUS_OK;
    out.newline_found = false;
    out.scanned_anything = false;
    out.delimiter = delimiter;
    return out;
}

static inline MkScanner mk_scanner_create_default(void) {
    return mk_scanner_create(stdin, MK_DEFAULT_DELIM);
}

static inline MkStatus mk_scanner_get_status(MkScanner * sc) {
    return sc->status;
}

static inline void mk_scanner_clear_status(MkScanner * sc) {
    sc->status = MK_STATUS_OK;
}

static inline void mk_scanner_set_delim(MkScanner * sc, const char * delimiter) {
    sc->delimiter = delimiter;
}

static inline void mk_scanner_clear_input(MkScanner * sc) {
    if (!sc->scanned_anything) {
        return;
    }
    if (sc->newline_found) {
        return;
    }
    int c;
    do {
        c = fgetc(sc->istream);
    } while (c != '\n' && c != EOF);
    sc->newline_found = true;
}

static inline size_t mk_scanner_get_string(MkScanner * sc, char * buffer, size_t buffer_length) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (buffer_length < 2) {
        goto ERROR_INPUT_OUT_OF_RANGE;
    }
    
    sc->newline_found = false;
    sc->scanned_anything = true;
    
    size_t token_length = 0;
    while (true) {
        const int c = fgetc(sc->istream);
        if (c == EOF) {
            if (ferror(sc->istream)) {
                goto ERROR_FERROR;
            }
            if (token_length == 0) {
                goto STATE_EOF;
            }
            break;
        }
        
        const bool c_is_delimiter = strchr(sc->delimiter, c) != NULL;
        if (c_is_delimiter) {
            if (token_length > 0) {
                if (c == '\n') {
                    sc->newline_found = true;
                }                    
                break;
            }
            continue;
        }
        
        if (token_length < buffer_length - 1) {
            buffer[token_length++] = (char) c;
        }
        else {
            goto ERROR_INPUT_OUT_OF_RANGE;
        }
    }
    
    buffer[token_length] = '\0';
    return token_length;
    
    STATE_EOF:
    sc->status = MK_STATUS_EOF;
    return 0;
    
    ERROR:
    return 0;
    
    ERROR_INPUT_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
    
    ERROR_FERROR:
    sc->status = MK_STATUS_ERROR_SYSTEM;
    return 0;
}

char mk_scanner_get_char(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    sc->newline_found = false;
    sc->scanned_anything = true;
    
    char out;
    int c;
    
    while (true) {
        int c = fgetc(sc->istream);
        if (c == EOF) {
            if (ferror(sc->istream)) {
                goto ERROR_SYSTEM;
            }
            goto STATE_EOF;
        }
        else if (strchr(sc->delimiter, c) == NULL) {
            out = (char)c;
            break;
        }
        else if (c == '\n') {
            sc->newline_found = true;
        }
    }
    if (strcmp(sc->delimiter, "") == 0) {
        goto DONE;
    }   
    c = fgetc(sc->istream);
    if (strchr(sc->delimiter, c) == NULL) {
        goto ERROR_INPUT_OUT_OF_RANGE;
    }
    
    DONE:
    return out;
    
    STATE_EOF:
    sc->status = MK_STATUS_EOF;
    return 0;
    
    ERROR:
    return 0;
    
    ERROR_INPUT_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
    
    ERROR_SYSTEM:
    sc->status = MK_STATUS_ERROR_SYSTEM;
    return 0;
}

static inline signed char mk_scanner_get_schar(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long long parsed_value = strtoll(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < SCHAR_MIN || parsed_value > SCHAR_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (signed char) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline short mk_scanner_get_short(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long long parsed_value = strtoll(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < SHRT_MIN || parsed_value > SHRT_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (short) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline int mk_scanner_get_int(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long long parsed_value = strtoll(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < INT_MIN || parsed_value > INT_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (int) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline long mk_scanner_get_long(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long long parsed_value = strtoll(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < LONG_MIN || parsed_value > LONG_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (long) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline long long mk_scanner_get_llong(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long long parsed_value = strtoll(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < LLONG_MIN || parsed_value > LLONG_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (long long) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline unsigned char mk_scanner_get_uchar(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const unsigned long long parsed_value = strtoull(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || parsed_value > UCHAR_MAX || *token_start_pointer == '-') {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (unsigned char) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline unsigned short mk_scanner_get_ushort(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const unsigned long long parsed_value = strtoull(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || parsed_value > USHRT_MAX || *token_start_pointer == '-') {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (unsigned short) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline unsigned int mk_scanner_get_uint(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const unsigned long long parsed_value = strtoull(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || parsed_value > UINT_MAX || *token_start_pointer == '-') {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (unsigned int) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline unsigned long mk_scanner_get_ulong(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const unsigned long long parsed_value = strtoull(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || parsed_value > ULONG_MAX || *token_start_pointer == '-') {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (unsigned long) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline unsigned long long mk_scanner_get_ullong(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const unsigned long long parsed_value = strtoull(token_start_pointer, (char **)&parse_end_pointer, 0);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || parsed_value > ULLONG_MAX || *token_start_pointer == '-') {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (unsigned long long) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline float mk_scanner_get_flt(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long double parsed_value = strtold(token_start_pointer, (char **)&parse_end_pointer);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < -FLT_MAX || parsed_value > FLT_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (float) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline double mk_scanner_get_dbl(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long double parsed_value = strtold(token_start_pointer, (char **)&parse_end_pointer);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < -DBL_MAX || parsed_value > DBL_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (double) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

static inline long double mk_scanner_get_ldbl(MkScanner * sc) {
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    
    char buffer[512] = {0};
    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));
    if (sc->status != MK_STATUS_OK) {
        goto ERROR;
    }
    if (token_length == 0) {
        goto ERROR_INVALID_TOKEN;
    }
    const char * token_start_pointer = NULL;
    const char * token_end_pointer   = NULL;
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            if (token_start_pointer == NULL) {
                token_start_pointer = buffer + i;
            }
            token_end_pointer = buffer + i;
        }
    }
    if (token_start_pointer == NULL) {
        goto ERROR_INVALID_TOKEN;
    }
    
    const char * parse_end_pointer = NULL;
    errno = 0;
    const long double parsed_value = strtold(token_start_pointer, (char **)&parse_end_pointer);
    if (parse_end_pointer <= token_end_pointer) {
        goto ERROR_INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < -LDBL_MAX || parsed_value > LDBL_MAX)) {
        goto ERROR_VALUE_OUT_OF_RANGE;
    }
    
    return (long double) parsed_value;
    
    ERROR:
    return 0;
    
    ERROR_INVALID_TOKEN:
    sc->status = MK_STATUS_ERROR_FORMAT;
    return 0;
    
    ERROR_VALUE_OUT_OF_RANGE:
    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;
    return 0;
}

#endif // MK_INPUT_H_
