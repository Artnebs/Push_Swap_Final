#include "push_swap.h"

long ft_atol(const char *str)
{
    long sign = 1;
    long res = 0;
    int i = 0;

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] && ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - '0');
        i++;
        if (res * sign > INT_MAX || res * sign < INT_MIN)
            return ((long)INT_MAX + 1);
    }
    return (res * sign);
}

int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int stack_is_sorted(t_data *data)
{
    t_node *tmp = data->a;
    while (tmp && tmp->next)
    {
        if (tmp->value > tmp->next->value)
            return (0);
        tmp = tmp->next;
    }
    return (1);
}

void free_all(t_data *data)
{
    t_node *tmp;
    while (data->a)
    {
        tmp = data->a->next;
        free(data->a);
        data->a = tmp;
    }
    while (data->b)
    {
        tmp = data->b->next;
        free(data->b);
        data->b = tmp;
    }
    if (data->arr)
        free(data->arr);
}

int stack_len(t_node *stack)
{
    int len = 0;
    while (stack)
    {
        len++;
        stack = stack->next;
    }
    return len;
}
