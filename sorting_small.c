#include "push_swap.h"

static void sort_three(t_data *data)
{
	int a = data->a->value;
	int b = data->a->next->value;
	int c = data->a->next->next->value;

	if (a > b && b < c && a < c)
		sa(data, 1);
	else if (a > b && b > c)
	{
		sa(data, 1);
		rra(data, 1);
	}
	else if (a > b && b < c && a > c)
		ra(data, 1);
	else if (a < b && b > c && a < c)
	{
		sa(data, 1);
		ra(data, 1);
	}
	else if (a < b && b > c && a > c)
		rra(data, 1);
}

static void push_min_to_b(t_data *data)
{
    // Push the smallest element (by rank) to b
    t_node *tmp = data->a;
    int min;
    int i = 0;

    if (!tmp)
        return;

    // Initialize min to the first element's value (rank)
    min = tmp->value;
    tmp = tmp->next;

    // Find the minimal rank in the stack
    while (tmp)
    {
        if (tmp->value < min)
            min = tmp->value;
        tmp = tmp->next;
    }

    // Now find the position of this minimal element
    tmp = data->a;
    i = 0;
    while (tmp && tmp->value != min)
    {
        tmp = tmp->next;
        i++;
    }

    // Decide whether to rotate up or down
    if (i <= data->size_a / 2)
        while (data->a->value != min)
            ra(data, 1);
    else
        while (data->a->value != min)
            rra(data, 1);

    // Push the smallest element to b
    pb(data, 1);
}


static void sort_five_or_less(t_data *data)
{
    // Handle trivial cases
    if (data->size_a <= 1)
        return; // With 1 or 0 elements, it's already sorted.

    if (data->size_a == 2)
    {
        // If two elements are not sorted, just swap them
        if (!stack_is_sorted(data))
            sa(data, 1);
        return;
    }

    // For 3 to 5 elements, proceed as before
    while (data->size_a > 3)
        push_min_to_b(data);

    // Now size_a <= 3, handle the 3-element case
    if (data->size_a == 3)
        sort_three(data);

    // Push back the elements from b to a
    while (data->size_b > 0)
        pa(data, 1);
}

static void chunk_sort(t_data *data)
{
    int chunks = 5;
    if (data->total_size < 20)
        chunks = 2; 
    ft_putstr_fd("DEBUG: Using chunk sort\n", 2);
    int chunk_size = data->total_size / chunks;
    if (chunk_size == 0) 
        chunk_size = 1;
    int i, val;
    int start, end;
    for (i = 0; i < chunks; i++)
    {
        start = i * chunk_size;
        end = (i == chunks - 1) ? data->total_size - 1 : (i+1)*chunk_size - 1;
        int pushed = 0;
        int target = end - start + 1;
        while (pushed < target && data->size_a > 0)
        {
            val = data->a->value;
            if (val >= start && val <= end)
            {
                pb(data, 1);
                pushed++;
            }
            else
                ra(data, 1);
        }
    }

    // Move back to A
    while (data->b)
    {
        t_node *tmp = data->b;
        int max = tmp->value;
        int pos = 0;
        int b_len = stack_len(data->b);
        tmp = data->b;
        int idx = 0;
        while (tmp)
        {
            if (tmp->value > max)
            {
                max = tmp->value;
                pos = idx;
            }
            tmp = tmp->next;
            idx++;
        }
        if (pos <= b_len/2)
            while (data->b->value != max)
                rb(data, 1);
        else
            while (data->b->value != max)
                rrb(data, 1);
        pa(data, 1);
    }
}

void sort_small(t_data *data)
{
    ft_putstr_fd("DEBUG: sort_small called\n", 2);
    if (stack_is_sorted(data))
    {
        ft_putstr_fd("DEBUG: Already sorted in sort_small\n", 2);
        return;
    }
    if (data->total_size <= 5)
    {
        ft_putstr_fd("DEBUG: Sorting <= 5 elements\n", 2);
        sort_five_or_less(data);
        return;
    }
    ft_putstr_fd("DEBUG: Sorting with chunk strategy\n", 2);
    chunk_sort(data);
}
