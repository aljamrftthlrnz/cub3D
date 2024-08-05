#include "../includes/cub3d.h"

void init_node(t_element *new)
{
    new->string = NULL; 
    new->path = NULL;
    new->rgb = NULL; 
    new->type = NULL;
    new->next = NULL; 
    //new->stat = NON; 
}

t_element *last_node(t_element *lst)
{
    t_element *curr; 

    curr = lst; 
    if(!lst)
        return (NULL); 
    while(curr->next != NULL)
    {
        curr = curr->next; 
    }
    return (curr); 
}

void add_node_to_linked_list(t_element **head, t_element *new)
{
    t_element *current; 
    
    current = (*head); 
    if(head)
    {
        if(*head == NULL)
            *head = new; 
        else 
        {
            current = last_node(*head); 
            current->next = new; 
        }
        new = NULL; 
    } 
}

t_element *init_new_node(char *arr, t_element *new)
{
    new = malloc (sizeof(t_element)); 
    if(!new)
    {
        return(free(arr), NULL); 
    }
    init_node(new); 
    new->string = ft_strdup(arr); 
    if(!new->string)
        return(free(new), NULL);
    return (new); 
}

int intialize_base_zero(char **file_arr, t_element *e)
{
    t_element *new;
    int i;  

    new = NULL;     
    i = -1; 
    if(!file_arr)
        return (1); 
    while(file_arr[++i])
    {
        new = init_new_node(file_arr[i], new); 
        if(!new)
        {
            while(file_arr[i])
            {
                free(file_arr[i]); 
                --i; 
            }
            return(free(file_arr), 1); 
        }
        free(file_arr[i]);
        add_node_to_linked_list(&e, new); 
    }
    return(free(file_arr), 0); 
}

void create_prerequisites_for_input_checker(t_data *data)
{
    
    if(data->file_arr == NULL)
    {
        data->error = MAP_EMPTY; 
        return ; 
    }
    if(intialize_base_zero(data->file_arr, data->file->elem) != 0)
        return ; 
    
}
void	print_list(t_element **head)
{
	t_element	*cmd;
    int i = 0; 

	cmd = *head;
	while (cmd != NULL)
	{
		printf("LINE [%d]: %s\n", i, cmd->string); 
        i++; 
		cmd = cmd->next;
	}
}