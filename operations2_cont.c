#include "push_swap.h"
#include <unistd.h>

static void rotate_down(t_node **stack)
{
	t_node *prev;
	t_node *last;

	if (!*stack || !(*stack)->next)
		return;
	prev = NULL;
	last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

void rra(t_data *data, int print)
{
	rotate_down(&data->a);
	if (print)
		ft_putstr_fd("rra\n", 1);
}

void rrb(t_data *data, int print)
{
	rotate_down(&data->b);
	if (print)
		ft_putstr_fd("rrb\n", 1);
}

void rrr(t_data *data, int print)
{
	rotate_down(&data->a);
	rotate_down(&data->b);
	if (print)
		ft_putstr_fd("rrr\n", 1);
}
