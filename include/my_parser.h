/*
** EPITECH PROJECT, 2023
** argsParser
** File description:
** my_parser
*/

#ifndef MY_PARSER_H_
    #define MY_PARSER_H_

    #include <stdbool.h>
    #include <stddef.h>

    #include "my_str.h"
    #include "my_vec.h"
    #include "my_map.h"

    #define INFINITY -1


enum arg_type_e {
    ARG_INT,
    ARG_STR,
    ARG_BOOL,
    ARG_DOUBLE,
    ARG_CHAR,
    ARG_VOID
};

typedef struct args_s {
    str_t *arg_name;
    vec_str_t *possible_names;
    vec_int_t *possible_types;
    bool required;
    size_t max;
    size_t count;
} args_t;

VEC_DEF(args_t, args);

typedef struct parser_s {
    vec_args_t *args;
    map_t *values;
} parser_t;


#endif /* !MY_PARSER_H_ */
