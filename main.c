#include "push_swap.h"

int main(int ac, char **av)
{
    t_data data;

    ft_putstr_fd("DEBUG: Starting push_swap\n", 2);
    if (ac < 2)
        return (0);
    init_data(&data);
    if (!parse_args(ac, av, &data))
        error_exit(&data);
    ft_putstr_fd("DEBUG: Finished parsing and ranking\n", 2);
    if (stack_is_sorted(&data))
    {
        ft_putstr_fd("DEBUG: Already sorted!\n", 2);
        free_all(&data);
        return (0);
    }
    if (data.total_size <= 200)
        sort_small(&data);
    else
        sort_large(&data);
    free_all(&data);
    ft_putstr_fd("DEBUG: Done!\n", 2);
    return (0);
}
