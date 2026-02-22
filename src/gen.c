#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "cg.h"

int main() {
    const char * filename = "mk_input.h";
    FILE * file = fopen(filename, "w");
    assert(file != NULL);
    
    const char * include_guard_token = "MK_INPUT_H_";
    const char * includes[] = {
        "stdio.h",
        "stdlib.h",
        "stdbool.h",
        "stdint.h",
        "limits.h",
        "string.h",
        "float.h",
        "ctype.h",
        "errno.h"
    };
    
    const char * status[] = {
        "MK_STATUS_OK",
        "MK_STATUS_EOF",
        "MK_STATUS_ERROR_SYSTEM",
        "MK_STATUS_ERROR_FORMAT",
        "MK_STATUS_ERROR_OUT_OF_RANGE",
    };

    cg_print_warning(file);
    fprintf(file, "\n");    
    cg_print_include_guard_open(file, include_guard_token);
    fprintf(file, "\n");
    cg_print_includes_global(file, includes, cg_arraysize(includes));
    fprintf(file, "\n");

    fprintf(file, "typedef enum {\n");
    for (size_t i = 0; i < cg_arraysize(status); i++) {
    fprintf(file, "    %s,\n", status[i]);
    }
    fprintf(file, "} MkStatus;\n");
    fprintf(file, "\n");
    
    fprintf(file, "typedef struct {\n");
    fprintf(file, "    FILE * istream;\n");
    fprintf(file, "    MkStatus status;\n");
    fprintf(file, "    bool newline_found;\n");
    fprintf(file, "    bool scanned_anything;\n");
    fprintf(file, "    const char * delimiter;\n");
    fprintf(file, "} MkScanner;\n");
    fprintf(file, "\n");
    
    fprintf(file, "static const char * const MK_DEFAULT_DELIM = \" \\f\\n\\r\\t\\v\";\n");
    fprintf(file, "\n");

    fprintf(file, "static inline const char * mk_status_get_string(const MkStatus status) {\n");
    fprintf(file, "    switch (status) {\n");
    for (size_t i = 0; i < cg_arraysize(status); i++) {
    fprintf(file, "        case %s: return \"%s\";\n", status[i], status[i]);
    }    
    fprintf(file, "        default: return \"Unknown Status\";\n");
    fprintf(file, "    }\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");
    
    fprintf(file, "static inline MkScanner mk_scanner_create(FILE * istream, const char * delimiter) {\n");
    fprintf(file, "    MkScanner out;\n");
    fprintf(file, "    out.istream = istream;\n");
    fprintf(file, "    out.status = MK_STATUS_OK;\n");
    fprintf(file, "    out.newline_found = false;\n");
    fprintf(file, "    out.scanned_anything = false;\n");
    fprintf(file, "    out.delimiter = delimiter;\n");
    fprintf(file, "    return out;\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");

    fprintf(file, "static inline MkScanner mk_scanner_create_default(void) {\n");
    fprintf(file, "    return mk_scanner_create(stdin, MK_DEFAULT_DELIM);\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");
    
    fprintf(file, "static inline MkStatus mk_scanner_get_status(MkScanner * sc) {\n");
    fprintf(file, "    return sc->status;\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");

    fprintf(file, "static inline void mk_scanner_clear_status(MkScanner * sc) {\n");
    fprintf(file, "    sc->status = MK_STATUS_OK;\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");
    
    fprintf(file, "static inline void mk_scanner_set_delim(MkScanner * sc, const char * delimiter) {\n");
    fprintf(file, "    sc->delimiter = delimiter;\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");

    fprintf(file, "static inline void mk_scanner_clear_input(MkScanner * sc) {\n");
    fprintf(file, "    if (!sc->scanned_anything) {\n");
    fprintf(file, "        return;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    if (sc->newline_found) {\n");
    fprintf(file, "        return;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    int c;\n");
    fprintf(file, "    do {\n");
    fprintf(file, "        c = fgetc(sc->istream);\n");
    fprintf(file, "    } while (c != '\\n' && c != EOF);\n");
    fprintf(file, "    sc->newline_found = true;\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");
    
    fprintf(file, "static inline size_t mk_scanner_get_string(MkScanner * sc, char * buffer, size_t buffer_length) {\n");
    fprintf(file, "    if (sc->status != MK_STATUS_OK) {\n");
    fprintf(file, "        goto ERROR;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    if (buffer_length < 2) {\n");
    fprintf(file, "        goto ERROR_INPUT_OUT_OF_RANGE;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    \n");
    fprintf(file, "    sc->newline_found = false;\n");
    fprintf(file, "    sc->scanned_anything = true;\n");
    fprintf(file, "    \n");
    fprintf(file, "    size_t token_length = 0;\n");
    fprintf(file, "    while (true) {\n");
    fprintf(file, "        const int c = fgetc(sc->istream);\n");
    fprintf(file, "        if (c == EOF) {\n");
    fprintf(file, "            if (ferror(sc->istream)) {\n");
    fprintf(file, "                goto ERROR_FERROR;\n");
    fprintf(file, "            }\n");
    fprintf(file, "            if (token_length == 0) {\n");
    fprintf(file, "                goto STATE_EOF;\n");
    fprintf(file, "            }\n");
    fprintf(file, "            break;\n");
    fprintf(file, "        }\n");
    fprintf(file, "        \n");
    fprintf(file, "        const bool c_is_delimiter = strchr(sc->delimiter, c) != NULL;\n");
    fprintf(file, "        if (c_is_delimiter) {\n");
    fprintf(file, "            if (token_length > 0) {\n");
    fprintf(file, "                if (c == '\\n') {\n");
    fprintf(file, "                    sc->newline_found = true;\n");
    fprintf(file, "                }                    \n");
    fprintf(file, "                break;\n");
    fprintf(file, "            }\n");
    fprintf(file, "            continue;\n");
    fprintf(file, "        }\n");
    fprintf(file, "        \n");
    fprintf(file, "        if (token_length < buffer_length - 1) {\n");
    fprintf(file, "            buffer[token_length++] = (char) c;\n");
    fprintf(file, "        }\n");
    fprintf(file, "        else {\n");
    fprintf(file, "            goto ERROR_INPUT_OUT_OF_RANGE;\n");
    fprintf(file, "        }\n");
    fprintf(file, "    }\n");
    fprintf(file, "    \n");
    fprintf(file, "    buffer[token_length] = '\\0';\n");
    fprintf(file, "    return token_length;\n");
    fprintf(file, "    \n");
    fprintf(file, "    STATE_EOF:\n");
    fprintf(file, "    sc->status = MK_STATUS_EOF;\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "    \n");
    fprintf(file, "    ERROR:\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "    \n");
    fprintf(file, "    ERROR_INPUT_OUT_OF_RANGE:\n");
    fprintf(file, "    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "    \n");
    fprintf(file, "    ERROR_FERROR:\n");
    fprintf(file, "    sc->status = MK_STATUS_ERROR_SYSTEM;\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");
    
    fprintf(file, "char mk_scanner_get_char(MkScanner * sc) {\n");
    fprintf(file, "    if (sc->status != MK_STATUS_OK) {\n");
    fprintf(file, "        goto ERROR;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    \n");
    fprintf(file, "    sc->newline_found = false;\n");
    fprintf(file, "    sc->scanned_anything = true;\n");
    fprintf(file, "    \n");
    fprintf(file, "    char out;\n");
    fprintf(file, "    int c;\n");
    fprintf(file, "    \n");
    fprintf(file, "    while (true) {\n");
    fprintf(file, "        int c = fgetc(sc->istream);\n");
    fprintf(file, "        if (c == EOF) {\n");
    fprintf(file, "            if (ferror(sc->istream)) {\n");
    fprintf(file, "                goto ERROR_SYSTEM;\n");
    fprintf(file, "            }\n");
    fprintf(file, "            goto STATE_EOF;\n");
    fprintf(file, "        }\n");
    fprintf(file, "        else if (strchr(sc->delimiter, c) == NULL) {\n");
    fprintf(file, "            out = (char)c;\n");
    fprintf(file, "            break;\n");
    fprintf(file, "        }\n");
    fprintf(file, "        else if (c == '\\n') {\n");
    fprintf(file, "            sc->newline_found = true;\n");
    fprintf(file, "        }\n");
    fprintf(file, "    }\n");
    fprintf(file, "    if (strcmp(sc->delimiter, \"\") == 0) {\n");
    fprintf(file, "        goto DONE;\n");
    fprintf(file, "    }   \n");
    fprintf(file, "    c = fgetc(sc->istream);\n");
    fprintf(file, "    if (strchr(sc->delimiter, c) == NULL) {\n");
    fprintf(file, "        goto ERROR_INPUT_OUT_OF_RANGE;\n");
    fprintf(file, "    }\n");
    fprintf(file, "    \n");
    fprintf(file, "    DONE:\n");
    fprintf(file, "    return out;\n");
    fprintf(file, "    \n");
    fprintf(file, "    STATE_EOF:\n");
    fprintf(file, "    sc->status = MK_STATUS_EOF;\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "    \n");
    fprintf(file, "    ERROR:\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "    \n");
    fprintf(file, "    ERROR_INPUT_OUT_OF_RANGE:\n");
    fprintf(file, "    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "    \n");
    fprintf(file, "    ERROR_SYSTEM:\n");
    fprintf(file, "    sc->status = MK_STATUS_ERROR_SYSTEM;\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");
    
    const CgTypeInfoNumeric types[] = {
        CG_TYPE_INFO_LIST_NUMERIC_NATIVE
    };
    
    for (size_t i = 0; i < cg_arraysize(types); i++) {
        fprintf(file, "static inline %s mk_scanner_get_%s(MkScanner * sc) {\n", types[i].type, types[i].alias_lowercase);
        fprintf(file, "    if (sc->status != MK_STATUS_OK) {\n");
        fprintf(file, "        goto ERROR;\n");
        fprintf(file, "    }\n");
        fprintf(file, "    \n");
        fprintf(file, "    char buffer[512] = {0};\n");
        fprintf(file, "    const size_t token_length = mk_scanner_get_string(sc, buffer, sizeof(buffer));\n");
        fprintf(file, "    if (sc->status != MK_STATUS_OK) {\n");
        fprintf(file, "        goto ERROR;\n");
        fprintf(file, "    }\n");
        fprintf(file, "    if (token_length == 0) {\n");
        fprintf(file, "        goto ERROR_INVALID_TOKEN;\n");
        fprintf(file, "    }\n");
        fprintf(file, "    const char * token_start_pointer = NULL;\n");
        fprintf(file, "    const char * token_end_pointer   = NULL;\n");
        fprintf(file, "    for (size_t i = 0; buffer[i] != '\\0'; i++) {\n");
        fprintf(file, "        if (!isspace((unsigned char)buffer[i])) {\n");
        fprintf(file, "            if (token_start_pointer == NULL) {\n");
        fprintf(file, "                token_start_pointer = buffer + i;\n");
        fprintf(file, "            }\n");
        fprintf(file, "            token_end_pointer = buffer + i;\n");
        fprintf(file, "        }\n");
        fprintf(file, "    }\n");
        fprintf(file, "    if (token_start_pointer == NULL) {\n");
        fprintf(file, "        goto ERROR_INVALID_TOKEN;\n");
        fprintf(file, "    }\n");
        fprintf(file, "    \n");
        fprintf(file, "    const char * parse_end_pointer = NULL;\n");
        fprintf(file, "    errno = 0;\n");
        switch (types[i].kind) {
        case CG_TYPE_KIND_SIGNED:
        fprintf(file, "    const long long parsed_value = strtoll(token_start_pointer, (char **)&parse_end_pointer, 0);\n");
        break;
        case CG_TYPE_KIND_UNSIGNED:
        fprintf(file, "    const unsigned long long parsed_value = strtoull(token_start_pointer, (char **)&parse_end_pointer, 0);\n");
        break;
        case CG_TYPE_KIND_FLOATING:
        fprintf(file, "    const long double parsed_value = strtold(token_start_pointer, (char **)&parse_end_pointer);\n");
        break;
        }
        fprintf(file, "    if (parse_end_pointer <= token_end_pointer) {\n");
        fprintf(file, "        goto ERROR_INVALID_TOKEN;\n");
        fprintf(file, "    }\n");
        if (types[i].kind == CG_TYPE_KIND_SIGNED || types[i].kind == CG_TYPE_KIND_FLOATING) {
        fprintf(file, "    if (errno == ERANGE || (parsed_value < %s || parsed_value > %s)) {\n", types[i].min, types[i].max);
        }
        else if (types[i].kind == CG_TYPE_KIND_UNSIGNED) {
        fprintf(file, "    if (errno == ERANGE || parsed_value > %s || *token_start_pointer == '-') {\n", types[i].max);
        }
        fprintf(file, "        goto ERROR_VALUE_OUT_OF_RANGE;\n");
        fprintf(file, "    }\n");
        fprintf(file, "    \n");
        fprintf(file, "    return (%s) parsed_value;\n", types[i].type);
        fprintf(file, "    \n");
        fprintf(file, "    ERROR:\n");
        fprintf(file, "    return 0;\n");
        fprintf(file, "    \n");
        fprintf(file, "    ERROR_INVALID_TOKEN:\n");
        fprintf(file, "    sc->status = MK_STATUS_ERROR_FORMAT;\n");
        fprintf(file, "    return 0;\n");
        fprintf(file, "    \n");
        fprintf(file, "    ERROR_VALUE_OUT_OF_RANGE:\n");
        fprintf(file, "    sc->status = MK_STATUS_ERROR_OUT_OF_RANGE;\n");
        fprintf(file, "    return 0;\n");
        fprintf(file, "}\n");
        fprintf(file, "\n");
    }    
    cg_print_include_guard_close(file, include_guard_token);
    fclose(file);
    cg_check_compileability(filename);
    return 0;
}
