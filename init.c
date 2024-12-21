#include "push_swap.h"

static void sort_int_array(int *arr, int size)
{
	int i, j, tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void init_data(t_data *data)
{
	data->a = NULL;
	data->b = NULL;
	data->size_a = 0;
	data->size_b = 0;
	data->total_size = 0;
	data->arr = NULL;
}

void rank_values(t_data *data)
{
	int     i;
	t_node  *tmp;
	int     *copy;

	copy = (int *)malloc(sizeof(int) * data->total_size);
	if (!copy)
		error_exit(data);
	tmp = data->a;
	i = 0;
	while (tmp)
	{
		copy[i++] = tmp->value;
		tmp = tmp->next;
	}
	sort_int_array(copy, data->total_size);
	data->arr = (int *)malloc(sizeof(int) * data->total_size);
	if (!data->arr)
	{
		free(copy);
		error_exit(data);
	}
	tmp = data->a;
	while (tmp)
	{
		int rank = 0;
		int val = tmp->value;
		for (i = 0; i < data->total_size; i++)
		{
			if (copy[i] == val)
			{
				rank = i;
				break;
			}
		}
		tmp->value = rank; 
		tmp = tmp->next;
	}
	for (i = 0; i < data->total_size; i++)
		data->arr[i] = copy[i];
	free(copy);

	ft_putstr_fd("DEBUG: rank_values complete. Stack A (ranks): ", 2);
	tmp = data->a;
	while (tmp)
	{
		ft_putnbr_fd(tmp->value, 2);
		ft_putstr_fd(" ", 2);
		tmp = tmp->next;
	}
	ft_putstr_fd("\n", 2);
}

void check_duplicates(t_data *data)
{
	int i;
	for (i = 0; i < data->total_size - 1; i++)
	{
		if (data->arr[i] == data->arr[i + 1])
		{
			ft_putstr_fd("DEBUG: Duplicate found\n", 2);
			error_exit(data);
		}
	}
	ft_putstr_fd("DEBUG: No duplicates found\n", 2);
}
