/*
** EPITECH PROJECT, 2023
** argsParser
** File description:
** main
*/

#include "my_map.h"
#include "my_parser.h"
#include "my_str.h"
#include "my_vec.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int parse_long_arg(parser_t *parser, str_t *t)
{
    for (size_t i = 0; i < parser->args->size; i++) {
        args_t arg = parser->args->data[i];
        vec_str_t *names = str_split(arg.possible_names, STR(" "));

        for (size_t j = 0; j < names->size; j++) {
            str_t *name = names->data[j];
            if (!str_startswith(t, name)) {
                map_set(parser->values, arg.arg_name, str_split(t, STR("="))->data[1]);
                break;
            }
        }
    }
    return (0);
}

int parse_short_arg(parser_t *parser, str_t *t, str_t *next)
{
    if (str_startswith(next, STR("-")))
        return (0);
    for (size_t i = 0; i < parser->args->size; i++) {
        args_t arg = parser->args->data[i];
        vec_str_t *names = str_split(arg.possible_names, STR(" "));

        for (size_t j = 0; j < names->size; j++) {
            str_t *name = names->data[j];
            if (!str_compare(t, name)) {
                map_set(parser->values, arg.arg_name, next);
                return (1);
            }
        }
    }
    return 0;
}

int parse_arg(parser_t *parser, char **av, size_t i)
{
    str_t *tmp = str_create(av[i]);

    if (str_startswith(tmp, STR("--"))) {
        return parse_long_arg(parser, tmp);
    }
    if(av[i + 1] == NULL)
        return (0);
    return (parse_short_arg(parser, tmp, str_create(av[i + 1])));
}

map_t *parse_arguments(int ac, char **av, vec_args_t *args)
{
    parser_t parser = {args, map_create(ac)};
    int error = 0;

    for (size_t i = 1; av[i]; i++) {
        error = parse_arg(&parser, av, i);
        if (error == 84)
            return (NULL);
        if (error == 1)
            i++;
    }
    return (parser.values);
}

void setup_atgs(vec_args_t **args)
{
    str_t *name = str_create("file");
    str_t *names = str_create("-f --file");
    vec_int_t *types = vec_create(1, sizeof(int));

    vec_pushback(&types, &(int){ARG_STR});
    args_t arg = {name, names, types, true, 1, 0};
    vec_pushback(args, &arg);

    name = str_create("count");
    names = str_create("-c --count");
    types = vec_create(1, sizeof(int));
    vec_pushback(&types, &(int){ARG_INT});
    arg = (args_t){name, names, types, false, INFINITY, 0};
    vec_pushback(args, &arg);
}

int main(int ac, char **av)
{
    vec_args_t *args = vec_create(100, sizeof(args_t));

    str_t *name = str_create("file");
    str_t *names = str_create("-f --file");
    vec_int_t *types = vec_create(1, sizeof(int));

    vec_pushback(&types, &(int){ARG_STR});
    vec_pushback(&args, &(args_t){name, names, types, true, 1, 0});
    
    map_t *map = parse_arguments(ac, av, args);
    for (size_t i = 0; i < args->size; i++) {
        void *arg = map_get(map, args->data[i].arg_name);
        if (args->data[i].required && !arg) {
            printf("Error: %s is required\n", args->data[i].arg_name->data);
            return (84);
        }
    }
    return (0);
}
