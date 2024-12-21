#include "push_swap.h"
#include <unistd.h>

static void swap_top(t_node **stack)
{
	t_node *first;
	t_node *second;

	if (!*stack || !(*stack)->next)
		return;
	first = *stack;
	second = (*stack)->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void sa(t_data *data, int print)
{
	swap_top(&data->a);
	if (print)
		ft_putstr_fd("sa\n", 1);
}

void sb(t_data *data, int print)
{
	swap_top(&data->b);
	if (print)
		ft_putstr_fd("sb\n", 1);
}

void ss(t_data *data, int print)
{
	swap_top(&data->a);
	swap_top(&data->b);
	if (print)
		ft_putstr_fd("ss\n", 1);
}

void pa(t_data *data, int print)
{
	t_node *tmp;

	if (!data->b)
		return;
	tmp = data->b;
	data->b = data->b->next;
	tmp->next = data->a;
	data->a = tmp;
	data->size_a++;
	data->size_b--;
	if (print)
		ft_putstr_fd("pa\n", 1);
}
