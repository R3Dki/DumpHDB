#pragma once
#ifndef TYPES_LIB
#define TYPES_LIB


// Types Library Compiled Settings
#define USE_S_INSTEAD_OF_I_FOR_INTS 0       // Specifies whether ints(signed ints) are declared as i[bit count] or s[bit count].
#define DISABLE_BITWISE_TYPES 0             // Disables types that are used for bitwise operations(byte, word, dword, qword, block, page).
#define DISABLE_SPECIFIC_TYPES 0            // Disables types that are used for specific applications such as timestamps, sizes and strings.
#define DISABLE_ERRORCODE_TYPE 0            // Disables err(errorcode) type used for function execution result. WARNING: Will cause errors in some libraries if disabled. 
#define USE_ENUM_FOR_BOOLEAN_TYPE 0         // (WIP) Creates a bool enum instead of an unsigned char as bool typedef.
#define PAGE_SIZE 512                       // Page type size specifier.
// Compatibility Settings
#define SUPPORT_S_AND_I_FOR_INTS 0          // If a program uses i[bit count] or s[bit count] but the selected declaration is different, both can be enabled at the same time to support other code.
#define DISABLE_AUTO_SETTINGS_DETECTION 0   // (OVERRIDES SETTINGS BELOW) Disables Automatic Settings Detection that helps with avoiding conflicts between library definitions.

#define USING_STDLIB 1                      // Disable types that end with _t (Should be disabled by default, if stdlib.c is in use it will give errors, but if needed set the value to 0)
#define DISABLE_BOOL_DECLARATIONS 0         // Disables every boolean declaration (Set to 1 if using C++)
// Compatibility Settings
// Types Library Compiled Settings


#define TYPES_LIB_VERSION_MAJOR 1
#define TYPES_LIB_VERSION_MINOR 3
#define TYPES_LIB_VERSION_PATCH 1

#if !DISABLE_AUTO_SETTINGS_DETECTION
    #ifdef _STDLIB_H
        #undef USING_STDLIB
        #define USING_STDLIB 1
    #endif
    #ifdef __cplusplus
        #undef DISABLE_BOOL_DECLARATIONS
        #define DISABLE_BOOL_DECLARATIONS 1
    #endif
#endif


    typedef unsigned char u8;
    typedef unsigned short u16;
    typedef unsigned int u32;
    typedef unsigned long long u64; // WARNING: May not be 64 bit long in some architectures, needs to be reviewed.
     
    #if !USE_S_INSTEAD_OF_I_FOR_INTS || SUPPORT_S_AND_I_FOR_INTS
    typedef signed char i8;
    typedef signed short i16;
    typedef signed int i32;
    typedef signed long long i64; // WARNING: May not be 64 bit long in some architectures, needs to be reviewed.
    #endif

    #if USE_S_INSTEAD_OF_I_FOR_INTS || SUPPORT_S_AND_I_FOR_INTS
    typedef signed char s8;
    typedef signed short s16;
    typedef signed int s32;
    typedef signed long long s64; // WARNING: May not be 64 bit long in some architectures, needs to be reviewed.
    #endif

    typedef float f32;
    typedef double f64;
    typedef long double f128; // WARNING: May not be 128 bit long in some architectures, needs to be reviewed.
    
    #if !DISABLE_SPECIFIC_TYPES
    typedef unsigned short wchar;
    typedef unsigned long long size;
    typedef unsigned long long timestamp;
    typedef signed long long unix_time;
    typedef char* string;       // WARNING: This is an alias for char*, if the variable is not managed or used correctly it will fail.
    typedef wchar* wstring;       // WARNING: This is an alias for wchar*, if the variable is not managed or used correctly it will fail.
    #endif

    #if !DISABLE_ERRORCODE_TYPE
        typedef enum errorcode {
            SUCCESS, // Successful Execution
            FAILURE, // Generic Failure
            UNKNOWN, // Unknown Failure
            INVALID_NIBBLE, // Given Nibble is Invalid
            UNEXPECTED_DTS, // Unexpected Data Type Specifier
            NO_ARGS_TO_PARSE, // No Arguments to Parse
            EXPECTED_ARGS_MISMATCH // Received Args do not match Expected ones
        } err;
    #endif

    #if !DISABLE_BITWISE_TYPES
    typedef unsigned char nibble;   // UNSAFE: The real size of the nibble type is 8 bits, not 4, which may lead to undefined behaviour if used the wrong way.
    typedef unsigned char byte;
    typedef unsigned short word;
    typedef unsigned int dword;
    typedef unsigned long long qword; // WARNING: May not be 64 bit long in some architectures, needs to be reviewed.
    typedef word bitgroup;          // 16 bits wide group of bits.
    typedef byte block[];           // EXPERIMENTAL: Use with caution. Should be used whenever a byte sequence variable is needed.
    typedef byte page[PAGE_SIZE];   // EXPERIMENTAL: Use with caution. Should be used whenever a large and specificly sized byte sequence variable is needed.
    #endif // !DISABLE_SPECIFIC_TYPES

    #if !USING_STDLIB
    // NOT RECCOMENDED
    typedef u8  uint8_t;
    typedef u16 uint16_t;
    typedef u32 uint32_t;
    typedef u64 uint64_t;
    typedef i8  int8_t;
    typedef i16 int16_t;
    typedef i32 int32_t;
    typedef i64 int64_t;
    typedef u64 size_t;
    typedef i64 time_t;
    typedef u16 wchar_t;
    // NOT RECCOMENDED
    #endif
    
    // Returns the size of the array it receives as argument.
    // WARNING: Do not use this macro on pointers to arrays since it'll always return the size of the pointer. (This warning may need to be fixed)
    #define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

    #if !DISABLE_BOOL_DECLARATIONS
        #ifndef bool 
            #if !USE_ENUM_FOR_BOOLEAN_TYPE
                typedef u8 bool;
                #ifndef true
                    #define true 1
                #endif // true
                #ifndef false
                    #define false 0
                #endif // true
            #else
                enum boolean { FALSE, TRUE };
                typedef enum boolean bool;
            #endif // USE_ENUM_FOR_BOOLEAN_TYPE
        #endif // BOOL
    #endif // !DISABLE_BOOL_DECLARATIONS
#endif // TYPES_LIB