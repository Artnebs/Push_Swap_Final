#include "push_swap.h"

int *stack_to_array(t_node *stack, int size)
{
    int *arr = (int *)malloc(sizeof(int) * size);
    int i = 0;
    t_node *tmp = stack;
    if (!arr)
        return (NULL);
    while (tmp)
    {
        arr[i++] = tmp->value;
        tmp = tmp->next;
    }
    return (arr);
}

static void sort_array(int *arr, int size)
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

int find_median(t_node *stack, int size)
{
    int *arr;
    int median;

    if (size == 0)
        return (0);
    arr = stack_to_array(stack, size);
    if (!arr)
        return (0);
    sort_array(arr, size);
    median = arr[size / 2];
    free(arr);
    return (median);
}
