#include "push_swap.h"

static void ft_free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

static int is_valid_int_str(char *str)
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static int add_number_to_stack(t_data *data, long val)
{
    t_node *new;
    t_node *tmp;

    if (val > INT_MAX || val < INT_MIN)
        return (0);

    new = (t_node *)malloc(sizeof(t_node));
    if (!new)
        return (0);
    new->value = (int)val;
    new->next = NULL;

    if (!data->a)
        data->a = new;
    else
    {
        tmp = data->a;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    data->size_a++;
    data->total_size++;
    return (1);
}

static int parse_line_of_args(t_data *data, const char *line)
{
    char **tokens;
    int i = 0;
    long val;

    ft_putstr_fd("DEBUG: parsing line: ", 2);
    ft_putstr_fd((char*)line, 2);
    ft_putstr_fd("\n", 2);

    tokens = ft_split(line, ' ');
    if (!tokens)
    {
        ft_putstr_fd("DEBUG: ft_split failed\n", 2);
        return (0);
    }

    while (tokens[i])
    {
        ft_putstr_fd("DEBUG: token: ", 2);
        ft_putstr_fd(tokens[i], 2);
        ft_putstr_fd("\n", 2);

        if (!is_valid_int_str(tokens[i]))
        {
            ft_putstr_fd("DEBUG: invalid int: ", 2);
            ft_putstr_fd(tokens[i], 2);
            ft_putstr_fd("\n", 2);
            ft_free_split(tokens);
            return (0);
        }

        val = ft_atol(tokens[i]);
        if (!add_number_to_stack(data, val))
        {
            ft_putstr_fd("DEBUG: out of range or memory fail for: ", 2);
            ft_putstr_fd(tokens[i], 2);
            ft_putstr_fd("\n", 2);
            ft_free_split(tokens);
            return (0);
        }
        i++;
    }

    ft_free_split(tokens);
    return (1);
}

int parse_args(int ac, char **av, t_data *data)
{
    int i;

    ft_putstr_fd("DEBUG: parse_args start\n", 2);
    for (i = 1; i < ac; i++)
    {
        ft_putstr_fd("DEBUG: arg line: ", 2);
        ft_putstr_fd(av[i], 2);
        ft_putstr_fd("\n", 2);
        if (!parse_line_of_args(data, av[i]))
            return (0);
    }

    rank_values(data);
    check_duplicates(data);
    ft_putstr_fd("DEBUG: parse_args complete\n", 2);
    return (1);
}

void error_exit(t_data *data)
{
    ft_putstr_fd("Error\n", 2);
    free_all(data);
    exit(1);
}
