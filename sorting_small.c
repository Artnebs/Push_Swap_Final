#include "push_swap.h"

// Find maximum value in a stack
int find_max_in_stack(t_node *stack)
{
    t_node *tmp = stack;
    int max = tmp->value;

    while (tmp)
    {
        if (tmp->value > max)
            max = tmp->value;
        tmp = tmp->next;
    }

    return max;
}

// Validate final stack state
void validate_sort(t_data *data)
{
    if (stack_is_sorted(data) && data->size_b == 0)
    {
        ft_putstr_fd("DEBUG: Validation passed - Stack A is sorted, and Stack B is empty\n", 2);
    }
    else
    {
        ft_putstr_fd("DEBUG: Validation failed\n", 2);
        if (!stack_is_sorted(data))
            ft_putstr_fd("DEBUG: Stack A is not sorted\n", 2);
        if (data->size_b > 0)
            ft_putstr_fd("DEBUG: Stack B is not empty\n", 2);
    }
}

// Rotate stack to bring the target to the top
void rotate_stack_to_top(t_data *data, t_node **stack, int target, int size, int print)
{
    int pos = 0, idx = 0;
    t_node *tmp = *stack;

    while (tmp)
    {
        if (tmp->value == target)
        {
            pos = idx;
            break;
        }
        tmp = tmp->next;
        idx++;
    }

    if (pos <= size / 2)
    {
        while ((*stack)->value != target)
        {
            if (stack == &data->b)
                rb(data, print);
            else
                ra(data, print);
        }
    }
    else
    {
        while ((*stack)->value != target)
        {
            if (stack == &data->b)
                rrb(data, print);
            else
                rra(data, print);
        }
    }
}

// Count values in a given range
static int count_values_in_chunk(t_node *stack, int start, int end)
{
    int count = 0;
    while (stack)
    {
        if (stack->value >= start && stack->value <= end)
            count++;
        stack = stack->next;
    }
    return count;
}

// Process a single chunk
static void process_chunk(t_data *data, int start, int end)
{
    int chunk_count = count_values_in_chunk(data->a, start, end);

    while (chunk_count > 0 && data->size_a > 0)
    {
        int val = data->a->value;

        if (val >= start && val <= end)
        {
            pb(data, 1); // Push to B
            chunk_count--;
        }
        else
        {
            ra(data, 1); // Rotate stack A
        }
    }
}

// Chunk sorting
void chunk_sort(t_data *data)
{
    int num_chunks;
    if (data->total_size <= 100)
        num_chunks = 8; // More chunks for smaller sizes
    else if (data->total_size <= 200)
        num_chunks = 12; // Moderate number of chunks for up to 200 elements
    else
        num_chunks = 24; // Default for larger sizes

    int chunk_size = data->total_size / num_chunks;
    int start, end;

    if (chunk_size < 1)
        chunk_size = 1;

    for (int i = 0; i < num_chunks; i++)
    {
        start = i * chunk_size;
        end = (i == num_chunks - 1) ? data->total_size - 1 : (i + 1) * chunk_size - 1;

        process_chunk(data, start, end);
    }

    while (data->size_b > 0)
    {
        int max = find_max_in_stack(data->b);
        rotate_stack_to_top(data, &data->b, max, data->size_b, 1);
        pa(data, 1);
    }
}

// Sort three elements
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

// Push minimum value to stack B
static void push_min_to_b(t_data *data)
{
    t_node *tmp = data->a;
    int min = tmp->value;
    int pos = 0, idx = 0;

    while (tmp)
    {
        if (tmp->value < min)
        {
            min = tmp->value;
            pos = idx;
        }
        tmp = tmp->next;
        idx++;
    }

    if (pos <= data->size_a / 2)
        while (data->a->value != min)
            ra(data, 1);
    else
        while (data->a->value != min)
            rra(data, 1);

    pb(data, 1);
}

// Sort five or fewer elements
static void sort_five_or_less(t_data *data)
{
    if (data->size_a <= 1)
        return;

    if (data->size_a == 2)
    {
        if (!stack_is_sorted(data))
            sa(data, 1);
        return;
    }

    while (data->size_a > 3)
        push_min_to_b(data);

    if (data->size_a == 3)
        sort_three(data);

    while (data->size_b > 0)
        pa(data, 1);
}

// Main sorting function
void sort_small(t_data *data)
{
    if (stack_is_sorted(data))
        return;

    if (data->total_size <= 5)
    {
        sort_five_or_less(data);
        return;
    }

    chunk_sort(data);
    validate_sort(data); // Final validation
}
