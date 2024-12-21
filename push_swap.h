#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "Libft_GNL_Printf/includes/libft.h"  // Ensure this is correct path to your libft headers.

typedef struct s_node
{
	int             value;
	struct s_node   *next;
}   t_node;

typedef struct s_data
{
	t_node  *a;
	t_node  *b;
	int     size_a;
	int     size_b;
	int     total_size;
	int     *arr; // used for ranking and reference
}   t_data;

/* parse_args.c */
int     parse_args(int ac, char **av, t_data *data);
void    error_exit(t_data *data);

/* init.c */
void    init_data(t_data *data);
void    rank_values(t_data *data);
void    check_duplicates(t_data *data);

/* operations.c */
void    sa(t_data *data, int print);
void    sb(t_data *data, int print);
void    ss(t_data *data, int print);
void    pa(t_data *data, int print);
void    pb(t_data *data, int print);

/* operations2.c */
void    ra(t_data *data, int print);
void    rb(t_data *data, int print);
void    rr(t_data *data, int print);
void    rra(t_data *data, int print);
void    rrb(t_data *data, int print);
void    rrr(t_data *data, int print);

/* utils.c */
long    ft_atol(const char *str);
int     ft_isdigit(int c);
int     stack_is_sorted(t_data *data);
void    free_all(t_data *data);
int     stack_len(t_node *stack);

/* sorting_small.c */
void    sort_small(t_data *data);

/* sorting_large.c */
void    sort_large(t_data *data);

/* costs_and_median.c */
int     find_median(t_node *stack, int size);
int     *stack_to_array(t_node *stack, int size);

/* main.c */
int     main(int ac, char **av);

#endif
