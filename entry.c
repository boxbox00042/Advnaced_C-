#include "main.h"

List *createList()
{
    List *new_list;
    new_list = (List *)malloc(sizeof(List));
    void *ptr = NULL;
    int location;
    our_malloc(1, &ptr, &location);
    if (new_list)
    {
        new_list->next = NULL;
        new_list->prev = NULL;
        new_list->content = ptr;

        ((folder *)(ptr))->type = 0;
        strcpy(((folder *)(ptr))->name, "/");
        ((folder *)(ptr))->prev = NULL;
        ((folder *)(ptr))->location = location;
        for (int i = 0; i < FOLDER_SIZE; i++)
        {
            ((folder *)(ptr))->entry_array[i] = NULL;
        }
    }

    return new_list;
}
int build_directory(List *list, char *name)
{
    void *ptr = NULL;
    int location;
    our_malloc(1, &ptr, &location);
    if (ptr == NULL)
    {
        return -1;
    }
    folder *p = ptr;
    p->location = location;
    p->type = 0;
    strcpy(p->name, name);
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        p->entry_array[i] = NULL;
    }
    p->prev = ((folder *)(list->content));

    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (((folder *)(list->content))->entry_array[i] == NULL)
        {
            ((folder *)(list->content))->entry_array[i] = p;
            break;
        }
    }
    return 0;
}

void list_directory(List *list)
{
    int flag = 0;
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (((folder *)(list->content))->entry_array[i] != NULL)
        {
            flag++;

            printf(BLU "%s " RESET, ((folder *)((folder *)(list->content))->entry_array[i])->name);
        }
    }
    if (flag)
    {
        printf("\n");
    }
}
int change_directory(List *list, char *name)
{
    List *node = (List *)malloc(sizeof(List));
    node->next = NULL;
    node->prev = NULL;
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (((folder *)(list->content))->entry_array[i] != NULL)
        {
            if (strcmp(((folder *)((folder *)(list->content))->entry_array[i])->name, name + 3) == 0)
            {
                node->content = ((folder *)(list->content))->entry_array[i];
                node->prev = list;
                list->next = node;
                return 0;
            }
        }
    }
    return -1;
}

int delete_directory(List *list, char *name)
{
    folder *current_folder = (folder *)(list->content);
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] != NULL)
        {
            if (strcmp(((folder *)(current_folder->entry_array[i]))->name, name) == 0)
            {
                folder *child_folder = (folder *)(current_folder->entry_array[i]);
                for (int j = 0; j < FOLDER_SIZE; j++)
                {
                    if (child_folder->entry_array[j] != NULL)
                    {
                        return -1;
                    }
                }
                our_free(1, ((folder *)(current_folder->entry_array[i]))->location);
                current_folder->entry_array[i] = NULL;
                return 0;
            }
        }
    }

    return -2;
}
void print_directory(List *last, List *head)
{
    List *current = head;
    if (head == last)
    {
        printf("/");
    }
    else
    {
        while (current != last)
        {
            if (strcmp(((folder *)(current->content))->name, "/") == 0)
            {
                printf("/");
            }
            else
            {
                printf("%s/", ((folder *)(current->content))->name);
            }
            current = current->next;
        }
        printf("%s/", ((folder *)(current->content))->name);
    }
    printf(" $ ");
}