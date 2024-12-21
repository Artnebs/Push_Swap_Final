#include "push_swap.h"

static int get_max_bits(t_data *data)
{
    int max = data->total_size - 1; 
    int bits = 0;
    while ((max >> bits) != 0)
        bits++;
    return (bits);
}

void sort_large(t_data *data)
{
    int i, j;
    int size = data->total_size;
    int bits = get_max_bits(data);

    i = 0;
    while (i < bits)
    {
        j = 0;
        while (j < size)
        {
            int top_val = data->a->value;
            if (((top_val >> i) & 1) == 0)
                pb(data, 1);
            else
                ra(data, 1);
            j++;
        }
        while (data->size_b > 0)
            pa(data, 1);
        i++;
    }
}
