/*
** EPITECH PROJECT, 2023
** argsParser
** File description:
** main
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

#include "my_parser.h"

bool find_arg_and_update(parser_t *parser, str_t *key, str_t *value)
{
    for (size_t i = 0; i < parser->args->size; i++) {
        args_t arg = parser->args->data[i];
        vec_str_t *names = arg.possible_names;

        for (size_t j = 0; j < names->size; j++) {
            if (str_eq(key, names->data[j])) {
                map_set(parser->values, arg.arg_name, value);
                return true;
            }
        }
    }
    return false;
}

bool parse_arg(parser_t *parser, char **av, size_t *i)
{
    str_t *tmp = str_create(av[*i]);
    int value_start = 0;

    if (str_startswith(tmp, STR("--"))) {
        value_start = str_find(tmp, STR("="), 0);

        if (value_start == -1) {
            // `=` not found so it's the next argv
            ++*i;
        } else {
            // skip the `=` char
            value_start++;
        }
    } else {
        ++*i;
    }

    if (*i >= parser->args->size) // TODO: handle void args (or bool)
        return false;

    str_t *key = str_substr(tmp, 0, (value_start == 0) ? 0 : value_start - 1);
    str_t *value = str_create(av[*i] + value_start);

    bool found = find_arg_and_update(parser, key, value);

    free(key);
    return found;
}

map_t *parse_arguments(int ac, char **av, vec_args_t *args)
{
    parser_t parser = {
        args,
        map_create(ac * 10), // *10 -> prevent collisions in hashmap
    };

    for (size_t i = 1; av[i]; ++i)
        if (parse_arg(&parser, av, &i) == false)
            return NULL;

    return parser.values;
}

bool check_required_params(map_t *param_map, vec_args_t *args)
{
    for (size_t i = 0; i < args->size; i++) {
        void *arg = map_get(param_map, args->data[i].arg_name);

        if (args->data[i].required && arg == NULL) {
            dprintf(2, "Error: %s is required\n", args->data[i].arg_name->data);
            return 84;
        }
    }
}

int main(int ac, char **av)
{
    vec_args_t *args = vec_create(100, sizeof(args_t));

    str_t *name = STR("file");
    vec_str_t *names = str_split(STR("-f --file"), STR(" "));
    vec_int_t *types = vec_create(1, sizeof(int));

    vec_pushback(&types, &(int){ARG_STR});
    vec_pushback(&args, &(args_t){name, names, types, true, 1, 0});

    map_t *map = parse_arguments(ac, av, args);

    if (check_required_params(map, args) == false)
        return 84;

    // free agrs after
    return 0;
}
