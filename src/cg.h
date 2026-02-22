#ifndef CG_H_
#define CG_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define cg_arraysize(array) (sizeof(array)/sizeof(array[0]))

typedef enum {
    CG_TYPE_KIND_SIGNED,
    CG_TYPE_KIND_UNSIGNED,
    CG_TYPE_KIND_FLOATING,
} CgTypeKind;

typedef struct {
    const char * type;
    CgTypeKind kind;
    const char * alias_lowercase;
    const char * alias_capitalized;
    const char * alias_uppercase;
    const char * min;
    const char * max;
} CgTypeInfoNumeric;

// -----------------------------------------------------------------------------
// TYPE NAMES
// -----------------------------------------------------------------------------

static const char * const cg_schar   = "signed char";
static const char * const cg_short   = "short";
static const char * const cg_int     = "int";
static const char * const cg_long    = "long";
static const char * const cg_llong   = "long long";
static const char * const cg_uchar   = "unsigned char";
static const char * const cg_ushort  = "unsigned short";
static const char * const cg_uint    = "unsigned int";
static const char * const cg_ullong  = "unsigned long long";
static const char * const cg_ulong   = "unsigned long";
static const char * const cg_int8    = "int8_t";
static const char * const cg_int16   = "int16_t";
static const char * const cg_int32   = "int32_t";
static const char * const cg_int64   = "int64_t";
static const char * const cg_uint8   = "uint8_t";
static const char * const cg_uint16  = "uint16_t";
static const char * const cg_uint32  = "uint32_t";
static const char * const cg_uint64  = "uint64_t";
static const char * const cg_intmax  = "intmax_t";
static const char * const cg_intptr  = "intptr_t";
static const char * const cg_ptrdiff = "ptrdiff_t";
static const char * const cg_size    = "size_t";
static const char * const cg_uintmax = "uintmax_t";
static const char * const cg_uintptr = "uintptr_t";
static const char * const cg_flt     = "float";
static const char * const cg_dbl     = "double";
static const char * const cg_ldbl    = "long double";

// -----------------------------------------------------------------------------
// TYPE ALIASES
// -----------------------------------------------------------------------------

// Lowercase

static const char * const cg_schar_alias_lowercase   = "schar";
static const char * const cg_short_alias_lowercase   = "short";
static const char * const cg_int_alias_lowercase     = "int";
static const char * const cg_long_alias_lowercase    = "long";
static const char * const cg_llong_alias_lowercase   = "llong";
static const char * const cg_uchar_alias_lowercase   = "uchar";
static const char * const cg_ushort_alias_lowercase  = "ushort";
static const char * const cg_uint_alias_lowercase    = "uint";
static const char * const cg_ulong_alias_lowercase   = "ulong";
static const char * const cg_ullong_alias_lowercase  = "ullong";
static const char * const cg_int8_alias_lowercase    = "int8";
static const char * const cg_int16_alias_lowercase   = "int16";
static const char * const cg_int32_alias_lowercase   = "int32";
static const char * const cg_int64_alias_lowercase   = "int64";
static const char * const cg_uint8_alias_lowercase   = "uint8";
static const char * const cg_uint16_alias_lowercase  = "uint16";
static const char * const cg_uint32_alias_lowercase  = "uint32";
static const char * const cg_uint64_alias_lowercase  = "uint64";
static const char * const cg_intmax_alias_lowercase  = "intmax";
static const char * const cg_intptr_alias_lowercase  = "intptr";
static const char * const cg_ptrdiff_alias_lowercase = "ptrdiff";
static const char * const cg_size_alias_lowercase    = "size";
static const char * const cg_uintmax_alias_lowercase = "uintmax";
static const char * const cg_uintptr_alias_lowercase = "uintptr";
static const char * const cg_flt_alias_lowercase     = "flt";
static const char * const cg_dbl_alias_lowercase     = "dbl";
static const char * const cg_ldbl_alias_lowercase    = "ldbl";

// Capitalized

static const char * const cg_schar_alias_capitalized   = "Schar";
static const char * const cg_short_alias_capitalized   = "Short";
static const char * const cg_int_alias_capitalized     = "Int";
static const char * const cg_long_alias_capitalized    = "Long";
static const char * const cg_llong_alias_capitalized   = "Llong";
static const char * const cg_uchar_alias_capitalized   = "Uchar";
static const char * const cg_ushort_alias_capitalized  = "Ushort";
static const char * const cg_uint_alias_capitalized    = "Uint";
static const char * const cg_ulong_alias_capitalized   = "Ulong";
static const char * const cg_ullong_alias_capitalized  = "Ullong";
static const char * const cg_int8_alias_capitalized    = "Int8";
static const char * const cg_int16_alias_capitalized   = "Int16";
static const char * const cg_int32_alias_capitalized   = "Int32";
static const char * const cg_int64_alias_capitalized   = "Int64";
static const char * const cg_uint8_alias_capitalized   = "Uint8";
static const char * const cg_uint16_alias_capitalized  = "Uint16";
static const char * const cg_uint32_alias_capitalized  = "Uint32";
static const char * const cg_uint64_alias_capitalized  = "Uint64";
static const char * const cg_intmax_alias_capitalized  = "Intmax";
static const char * const cg_intptr_alias_capitalized  = "Intptr";
static const char * const cg_ptrdiff_alias_capitalized = "Ptrdiff";
static const char * const cg_size_alias_capitalized    = "Size";
static const char * const cg_uintmax_alias_capitalized = "Uintmax";
static const char * const cg_uintptr_alias_capitalized = "Uintptr";
static const char * const cg_flt_alias_capitalized     = "Flt";
static const char * const cg_dbl_alias_capitalized     = "Dbl";
static const char * const cg_ldbl_alias_capitalized    = "Ldbl";

// Uppercase

static const char * const cg_schar_alias_uppercase   = "SCHAR";
static const char * const cg_short_alias_uppercase   = "SHORT";
static const char * const cg_int_alias_uppercase     = "INT";
static const char * const cg_long_alias_uppercase    = "LONG";
static const char * const cg_llong_alias_uppercase   = "LLONG";
static const char * const cg_uchar_alias_uppercase   = "UCHAR";
static const char * const cg_ushort_alias_uppercase  = "USHORT";
static const char * const cg_uint_alias_uppercase    = "UINT";
static const char * const cg_ulong_alias_uppercase   = "ULONG";
static const char * const cg_ullong_alias_uppercase  = "ULLONG";
static const char * const cg_int8_alias_uppercase    = "INT8";
static const char * const cg_int16_alias_uppercase   = "INT16";
static const char * const cg_int32_alias_uppercase   = "INT32";
static const char * const cg_int64_alias_uppercase   = "INT64";
static const char * const cg_uint8_alias_uppercase   = "UINT8";
static const char * const cg_uint16_alias_uppercase  = "UINT16";
static const char * const cg_uint32_alias_uppercase  = "UINT32";
static const char * const cg_uint64_alias_uppercase  = "UINT64";
static const char * const cg_intmax_alias_uppercase  = "INTMAX";
static const char * const cg_intptr_alias_uppercase  = "INTPTR";
static const char * const cg_ptrdiff_alias_uppercase = "PTRDIFF";
static const char * const cg_size_alias_uppercase    = "SIZE";
static const char * const cg_uintmax_alias_uppercase = "UINTMAX";
static const char * const cg_uintptr_alias_uppercase = "UINTPTR";
static const char * const cg_flt_alias_uppercase     = "FLT";
static const char * const cg_dbl_alias_uppercase     = "DBL";
static const char * const cg_ldbl_alias_uppercase    = "LDBL";

// -----------------------------------------------------------------------------
// NUMERIC TYPE MIN
// -----------------------------------------------------------------------------

static const char * const cg_schar_min   = "SCHAR_MIN";
static const char * const cg_short_min   = "SHRT_MIN";
static const char * const cg_int_min     = "INT_MIN";
static const char * const cg_long_min    = "LONG_MIN";
static const char * const cg_llong_min   = "LLONG_MIN";
static const char * const cg_ullong_min  = "0";
static const char * const cg_ulong_min   = "0";
static const char * const cg_uint_min    = "0";
static const char * const cg_uchar_min   = "0";
static const char * const cg_ushort_min  = "0";
static const char * const cg_int8_min    = "INT8_MIN";
static const char * const cg_int16_min   = "INT16_MIN";
static const char * const cg_int32_min   = "INT32_MIN";
static const char * const cg_int64_min   = "INT64_MIN";
static const char * const cg_uint8_min   = "0";
static const char * const cg_uint16_min  = "0";
static const char * const cg_uint32_min  = "0";
static const char * const cg_uint64_min  = "0";
static const char * const cg_intmax_min  = "INTMAX_MIN";
static const char * const cg_intptr_min  = "INTPTR_MIN";
static const char * const cg_ptrdiff_min = "PTRDIFF_MIN";
static const char * const cg_size_min    = "0";
static const char * const cg_uintmax_min = "0";
static const char * const cg_uintptr_min = "0";
static const char * const cg_flt_min     = "-FLT_MAX";
static const char * const cg_dbl_min     = "-DBL_MAX";
static const char * const cg_ldbl_min    = "-LDBL_MAX";

// -----------------------------------------------------------------------------
// NUMERIC TYPE MAX
// -----------------------------------------------------------------------------

static const char * const cg_schar_max   = "SCHAR_MAX";
static const char * const cg_short_max   = "SHRT_MAX";
static const char * const cg_int_max     = "INT_MAX";
static const char * const cg_long_max    = "LONG_MAX";
static const char * const cg_llong_max   = "LLONG_MAX";
static const char * const cg_uchar_max   = "UCHAR_MAX";
static const char * const cg_ushort_max  = "USHRT_MAX";
static const char * const cg_uint_max    = "UINT_MAX";
static const char * const cg_ulong_max   = "ULONG_MAX";
static const char * const cg_ullong_max  = "ULLONG_MAX";
static const char * const cg_int8_max    = "INT8_MAX";
static const char * const cg_int16_max   = "INT16_MAX";
static const char * const cg_int32_max   = "INT32_MAX";
static const char * const cg_int64_max   = "INT64_MAX";
static const char * const cg_uint8_max   = "UINT8_MAX";
static const char * const cg_uint16_max  = "UINT16_MAX";
static const char * const cg_uint32_max  = "UINT32_MAX";
static const char * const cg_uint64_max  = "UINT64_MAX";
static const char * const cg_intmax_max  = "INTMAX_MAX";
static const char * const cg_intptr_max  = "INTPTR_MAX";
static const char * const cg_ptrdiff_max = "PTRDIFF_MAX";
static const char * const cg_size_max    = "SIZE_MAX";
static const char * const cg_uintmax_max = "UINTMAX_MAX";
static const char * const cg_uintptr_max = "UINTPTR_MAX";
static const char * const cg_flt_max     = "FLT_MAX";
static const char * const cg_dbl_max     = "DBL_MAX";
static const char * const cg_ldbl_max    = "LDBL_MAX";

// -----------------------------------------------------------------------------
// TYPE INFOS
// -----------------------------------------------------------------------------

static const CgTypeInfoNumeric cg_type_info_schar   = {.type = cg_schar,   .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_schar_alias_lowercase,   .alias_capitalized = cg_schar_alias_capitalized,   .alias_uppercase = cg_schar_alias_uppercase,   .min = cg_schar_min,   .max = cg_schar_max};
static const CgTypeInfoNumeric cg_type_info_short   = {.type = cg_short,   .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_short_alias_lowercase,   .alias_capitalized = cg_short_alias_capitalized,   .alias_uppercase = cg_short_alias_uppercase,   .min = cg_short_min,   .max = cg_short_max};
static const CgTypeInfoNumeric cg_type_info_int     = {.type = cg_int,     .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_int_alias_lowercase,     .alias_capitalized = cg_int_alias_capitalized,     .alias_uppercase = cg_int_alias_uppercase,     .min = cg_int_min,     .max = cg_int_max};
static const CgTypeInfoNumeric cg_type_info_long    = {.type = cg_long,    .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_long_alias_lowercase,    .alias_capitalized = cg_long_alias_capitalized,    .alias_uppercase = cg_long_alias_uppercase,    .min = cg_long_min,    .max = cg_long_max};
static const CgTypeInfoNumeric cg_type_info_llong   = {.type = cg_llong,   .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_llong_alias_lowercase,   .alias_capitalized = cg_llong_alias_capitalized,   .alias_uppercase = cg_llong_alias_uppercase,   .min = cg_llong_min,   .max = cg_llong_max};
static const CgTypeInfoNumeric cg_type_info_uchar   = {.type = cg_uchar,   .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uchar_alias_lowercase,   .alias_capitalized = cg_uchar_alias_capitalized,   .alias_uppercase = cg_uchar_alias_uppercase,   .min = cg_uchar_min,   .max = cg_uchar_max};
static const CgTypeInfoNumeric cg_type_info_ushort  = {.type = cg_ushort,  .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_ushort_alias_lowercase,  .alias_capitalized = cg_ushort_alias_capitalized,  .alias_uppercase = cg_ushort_alias_uppercase,  .min = cg_ushort_min,  .max = cg_ushort_max};
static const CgTypeInfoNumeric cg_type_info_uint    = {.type = cg_uint,    .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uint_alias_lowercase,    .alias_capitalized = cg_uint_alias_capitalized,    .alias_uppercase = cg_uint_alias_uppercase,    .min = cg_uint_min,    .max = cg_uint_max};
static const CgTypeInfoNumeric cg_type_info_ulong   = {.type = cg_ulong,   .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_ulong_alias_lowercase,   .alias_capitalized = cg_ulong_alias_capitalized,   .alias_uppercase = cg_ulong_alias_uppercase,   .min = cg_ulong_min,   .max = cg_ulong_max};
static const CgTypeInfoNumeric cg_type_info_ullong  = {.type = cg_ullong,  .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_ullong_alias_lowercase,  .alias_capitalized = cg_ullong_alias_capitalized,  .alias_uppercase = cg_ullong_alias_uppercase,  .min = cg_ullong_min,  .max = cg_ullong_max};
static const CgTypeInfoNumeric cg_type_info_int8    = {.type = cg_int8 ,   .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_int8_alias_lowercase,    .alias_capitalized = cg_int8_alias_capitalized,    .alias_uppercase = cg_int8_alias_uppercase,    .min = cg_int8_min,    .max = cg_int8_max};
static const CgTypeInfoNumeric cg_type_info_int16   = {.type = cg_int16,   .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_int16_alias_lowercase,   .alias_capitalized = cg_int16_alias_capitalized,   .alias_uppercase = cg_int16_alias_uppercase,   .min = cg_int16_min,   .max = cg_int16_max};
static const CgTypeInfoNumeric cg_type_info_int32   = {.type = cg_int32,   .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_int32_alias_lowercase,   .alias_capitalized = cg_int32_alias_capitalized,   .alias_uppercase = cg_int32_alias_uppercase,   .min = cg_int32_min,   .max = cg_int32_max};
static const CgTypeInfoNumeric cg_type_info_int64   = {.type = cg_int64,   .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_int64_alias_lowercase,   .alias_capitalized = cg_int64_alias_capitalized,   .alias_uppercase = cg_int64_alias_uppercase,   .min = cg_int64_min,   .max = cg_int64_max};
static const CgTypeInfoNumeric cg_type_info_uint8   = {.type = cg_uint8,   .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uint8_alias_lowercase,   .alias_capitalized = cg_uint8_alias_capitalized,   .alias_uppercase = cg_uint8_alias_uppercase,   .min = cg_uint8_min,   .max = cg_uint8_max};
static const CgTypeInfoNumeric cg_type_info_uint16  = {.type = cg_uint16,  .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uint16_alias_lowercase,  .alias_capitalized = cg_uint16_alias_capitalized,  .alias_uppercase = cg_uint16_alias_uppercase,  .min = cg_uint16_min,  .max = cg_uint16_max};
static const CgTypeInfoNumeric cg_type_info_uint32  = {.type = cg_uint32,  .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uint32_alias_lowercase,  .alias_capitalized = cg_uint32_alias_capitalized,  .alias_uppercase = cg_uint32_alias_uppercase,  .min = cg_uint32_min,  .max = cg_uint32_max};
static const CgTypeInfoNumeric cg_type_info_uint64  = {.type = cg_uint64,  .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uint64_alias_lowercase,  .alias_capitalized = cg_uint64_alias_capitalized,  .alias_uppercase = cg_uint64_alias_uppercase,  .min = cg_uint64_min,  .max = cg_uint64_max};
static const CgTypeInfoNumeric cg_type_info_intmax  = {.type = cg_intmax,  .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_intmax_alias_lowercase,  .alias_capitalized = cg_intmax_alias_capitalized,  .alias_uppercase = cg_intmax_alias_uppercase,  .min = cg_intmax_min,  .max = cg_intmax_max};
static const CgTypeInfoNumeric cg_type_info_intptr  = {.type = cg_intptr,  .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_intptr_alias_lowercase,  .alias_capitalized = cg_intptr_alias_capitalized,  .alias_uppercase = cg_intptr_alias_uppercase,  .min = cg_intptr_min,  .max = cg_intptr_max};
static const CgTypeInfoNumeric cg_type_info_ptrdiff = {.type = cg_ptrdiff, .kind = CG_TYPE_KIND_SIGNED,   .alias_lowercase = cg_ptrdiff_alias_lowercase, .alias_capitalized = cg_ptrdiff_alias_capitalized, .alias_uppercase = cg_ptrdiff_alias_uppercase, .min = cg_ptrdiff_min, .max = cg_ptrdiff_max};
static const CgTypeInfoNumeric cg_type_info_size    = {.type = cg_size,    .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_size_alias_lowercase,    .alias_capitalized = cg_size_alias_capitalized,    .alias_uppercase = cg_size_alias_uppercase,    .min = cg_size_min,    .max = cg_size_max};
static const CgTypeInfoNumeric cg_type_info_uintmax = {.type = cg_uintmax, .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uintmax_alias_lowercase, .alias_capitalized = cg_uintmax_alias_capitalized, .alias_uppercase = cg_uintmax_alias_uppercase, .min = cg_uintmax_min, .max = cg_uintmax_max};
static const CgTypeInfoNumeric cg_type_info_uintptr = {.type = cg_uintptr, .kind = CG_TYPE_KIND_UNSIGNED, .alias_lowercase = cg_uintptr_alias_lowercase, .alias_capitalized = cg_uintptr_alias_capitalized, .alias_uppercase = cg_uintptr_alias_uppercase, .min = cg_uintptr_min, .max = cg_uintptr_max};
static const CgTypeInfoNumeric cg_type_info_flt     = {.type = cg_flt,     .kind = CG_TYPE_KIND_FLOATING, .alias_lowercase = cg_flt_alias_lowercase,     .alias_capitalized = cg_flt_alias_capitalized,     .alias_uppercase = cg_flt_alias_uppercase,     .min = cg_flt_min,     .max = cg_flt_max};
static const CgTypeInfoNumeric cg_type_info_dbl     = {.type = cg_dbl,     .kind = CG_TYPE_KIND_FLOATING, .alias_lowercase = cg_dbl_alias_lowercase,     .alias_capitalized = cg_dbl_alias_capitalized,     .alias_uppercase = cg_dbl_alias_uppercase,     .min = cg_dbl_min,     .max = cg_dbl_max};
static const CgTypeInfoNumeric cg_type_info_ldbl    = {.type = cg_ldbl,    .kind = CG_TYPE_KIND_FLOATING, .alias_lowercase = cg_ldbl_alias_lowercase,    .alias_capitalized = cg_ldbl_alias_capitalized,    .alias_uppercase = cg_ldbl_alias_uppercase,    .min = cg_ldbl_min,    .max = cg_ldbl_max};

// -----------------------------------------------------------------------------
// TYPE INFO LISTS
// -----------------------------------------------------------------------------

#define CG_TYPE_INFO_LIST_NUMERIC \
cg_type_info_schar, \
cg_type_info_short, \
cg_type_info_int, \
cg_type_info_long, \
cg_type_info_llong, \
cg_type_info_uchar, \
cg_type_info_ushort, \
cg_type_info_uint, \
cg_type_info_ulong, \
cg_type_info_ullong, \
cg_type_info_int8, \
cg_type_info_int16, \
cg_type_info_int32, \
cg_type_info_int64, \
cg_type_info_uint8, \
cg_type_info_uint16, \
cg_type_info_uint32, \
cg_type_info_uint64, \
cg_type_info_intmax, \
cg_type_info_intptr, \
cg_type_info_ptrdiff, \
cg_type_info_size, \
cg_type_info_uintmax, \
cg_type_info_uintptr, \
cg_type_info_flt, \
cg_type_info_dbl, \
cg_type_info_ldbl

#define CG_TYPE_INFO_LIST_NUMERIC_NATIVE \
cg_type_info_schar, \
cg_type_info_short, \
cg_type_info_int, \
cg_type_info_long, \
cg_type_info_llong, \
cg_type_info_uchar, \
cg_type_info_ushort, \
cg_type_info_uint, \
cg_type_info_ulong, \
cg_type_info_ullong, \
cg_type_info_flt, \
cg_type_info_dbl, \
cg_type_info_ldbl

#define CG_TYPE_INFO_LIST_NUMERIC_INT_NATIVE \
cg_type_info_schar, \
cg_type_info_short, \
cg_type_info_int, \
cg_type_info_long, \
cg_type_info_llong, \
cg_type_info_uchar, \
cg_type_info_ushort, \
cg_type_info_uint, \
cg_type_info_ulong, \
cg_type_info_ullong

#define CG_TYPE_INFO_LIST_NUMERIC_INT_FIXED \
cg_type_info_int8, \
cg_type_info_int16, \
cg_type_info_int32, \
cg_type_info_int64, \
cg_type_info_uint8, \
cg_type_info_uint16, \
cg_type_info_uint32, \
cg_type_info_uint64

#define CG_TYPE_INFO_LIST_NUMERIC_INT_SPECIAL \
cg_type_info_intmax, \
cg_type_info_intptr, \
cg_type_info_ptrdiff, \
cg_type_info_size, \
cg_type_info_uintmax, \
cg_type_info_uintptr

#define CG_TYPE_INFO_LIST_NUMERIC_INT_SIGNED \
cg_type_info_schar, \
cg_type_info_short, \
cg_type_info_int, \
cg_type_info_long, \
cg_type_info_llong, \
cg_type_info_int8, \
cg_type_info_int16, \
cg_type_info_int32, \
cg_type_info_int64, \
cg_type_info_intmax, \
cg_type_info_intptr, \
cg_type_info_ptrdiff

#define CG_TYPE_INFO_LIST_NUMERIC_INT_SIGNED_NATIVE \
cg_type_info_schar, \
cg_type_info_short, \
cg_type_info_int, \
cg_type_info_long, \
cg_type_info_llong

#define CG_TYPE_INFO_LIST_NUMERIC_INT_SIGNED_FIXED \
cg_type_info_int8, \
cg_type_info_int16, \
cg_type_info_int32, \
cg_type_info_int64

#define CG_TYPE_INFO_LIST_NUMERIC_INT_SIGNED_SPECIAL \
cg_type_info_intmax, \
cg_type_info_intptr, \
cg_type_info_ptrdiff

#define CG_TYPE_INFO_LIST_NUMERIC_INT_UNSIGNED \
cg_type_info_uchar, \
cg_type_info_ushort, \
cg_type_info_uint, \
cg_type_info_ulong, \
cg_type_info_ullong, \
cg_type_info_uint8, \
cg_type_info_uint16, \
cg_type_info_uint32, \
cg_type_info_uint64, \
cg_type_info_size, \
cg_type_info_uintmax, \
cg_type_info_uintptr

#define CG_TYPE_INFO_LIST_NUMERIC_INT_UNSIGNED_NATIVE \
cg_type_info_uchar, \
cg_type_info_ushort, \
cg_type_info_uint, \
cg_type_info_ulong, \
cg_type_info_ullong

#define CG_TYPE_INFO_LIST_NUMERIC_INT_UNSIGNED_FIXED \
cg_type_info_uint8, \
cg_type_info_uint16, \
cg_type_info_uint32, \
cg_type_info_uint64

#define CG_TYPE_INFO_LIST_NUMERIC_INT_UNSIGNED_SPECIAL \
cg_type_info_size, \
cg_type_info_uintmax, \
cg_type_info_uintptr

#define CG_TYPE_INFO_LIST_NUMERIC_FLOATING \
cg_type_info_flt, \
cg_type_info_dbl, \
cg_type_info_ldbl

// -----------------------------------------------------------------------------
// MIN MAX WIDTH TYPES
// -----------------------------------------------------------------------------

static const CgTypeInfoNumeric cg_type_info_numeric_width_max[] = {
    [CG_TYPE_KIND_SIGNED]   = cg_type_info_llong,
    [CG_TYPE_KIND_UNSIGNED] = cg_type_info_ullong,
    [CG_TYPE_KIND_FLOATING] = cg_type_info_ldbl,
};

static const CgTypeInfoNumeric cg_type_info_numeric_width_min[] = {
    [CG_TYPE_KIND_SIGNED]   = cg_type_info_schar,
    [CG_TYPE_KIND_UNSIGNED] = cg_type_info_uchar,
    [CG_TYPE_KIND_FLOATING] = cg_type_info_flt,
};

// -----------------------------------------------------------------------------
// FUNCTIONS
// -----------------------------------------------------------------------------

static inline void cg_print_warning_(FILE * file, const char * filename) {
    fprintf(file, "/*\n");
    fprintf(file, "WARNING\n");
    fprintf(file, "THIS FILE IS GENERATED FROM A TEMPLATE\n");
    fprintf(file, "CHANGES MADE HERE ARE NOT PERSISTENT\n");
    fprintf(file, "GENERATED AT %s %s FROM \"%s\"\n", __DATE__, __TIME__, filename);
    fprintf(file, "*/\n");
    assert(!ferror(file));
}

#define cg_print_warning(file) cg_print_warning_((file), __FILE__)

static inline void cg_print_include_guard_open(FILE * file, const char * token) {
    fprintf(file, "#ifndef %s\n", token);
    fprintf(file, "#define %s\n", token);
    assert(!ferror(file));
}

static inline void cg_print_include_guard_close(FILE * file, const char * token) {
    fprintf(file, "#endif // %s\n", token);
    assert(!ferror(file));
}

static inline void cg_print_includes_global(FILE * file, const char ** includes, const size_t n_includes) {
    for (size_t i = 0; i < n_includes; i++) {
        fprintf(file, "#include <%s>\n", includes[i]);
    }
    assert(!ferror(file));
}

static inline void cg_print_includes_local(FILE * file, const char ** includes, const size_t n_includes) {
    for (size_t i = 0; i < n_includes; i++) {
        fprintf(file, "#include \"%s\"\n", includes[i]);
    }
    assert(!ferror(file));
}

static inline void cg_check_compileability(const char * filename) {
    char * outfilename = "compileability_test.out";
    char buffer[1024];
    sprintf(buffer, "gcc %s -Wall -Wextra -Wpedantic -std=c99 -o %s", filename, outfilename);
    int status = system(buffer);
    if (status == 0) {
        printf("File '%s' is compileable.\n", filename);
        remove(outfilename);
    }
    else {
        printf("File '%s' is not compileable!\n", filename);
    }
}

#endif // CG_H_