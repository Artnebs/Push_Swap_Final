#include "push_swap.h"
#include <unistd.h>

void pb(t_data *data, int print)
{
	t_node *tmp;

	if (!data->a)
		return;
	tmp = data->a;
	data->a = data->a->next;
	tmp->next = data->b;
	data->b = tmp;
	data->size_b++;
	data->size_a--;
	if (print)
		ft_putstr_fd("pb\n", 1);
}

static void rotate_up(t_node **stack)
{
	t_node *first;
	t_node *last;

	if (!*stack || !(*stack)->next)
		return;
	first = *stack;
	*stack = (*stack)->next;
	first->next = NULL;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = first;
}

void ra(t_data *data, int print)
{
	rotate_up(&data->a);
	if (print)
		ft_putstr_fd("ra\n", 1);
}

void rb(t_data *data, int print)
{
	rotate_up(&data->b);
	if (print)
		ft_putstr_fd("rb\n", 1);
}

void rr(t_data *data, int print)
{
	rotate_up(&data->a);
	rotate_up(&data->b);
	if (print)
		ft_putstr_fd("rr\n", 1);
}
