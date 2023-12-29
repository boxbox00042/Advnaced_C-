#include "main.h"

List *createList(void *ptr)
{
    List *new_list;
    new_list = (List *)malloc(sizeof(List));

    if (new_list)
    {
        folder *root = ptr;
        root->type = 0;
        strcpy(root->name, "/");
        root->prev = NULL;
        for (int i = 0; i < FOLDER_SIZE; i++)
        {
            root->entry_array[i] = NULL;
        }
        new_list->content = root;
        new_list->next = NULL;
        new_list->prev = NULL;
    }

    return new_list;
}
int build_directory(List *list, void *ptr, char *name)
{
    List *node = (List *)malloc(sizeof(List));
    folder *p = ptr;
    p->type = 0;
    strcpy(p->name, name);
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        p->entry_array[i] = NULL;
    }
    p->prev = ((folder *)(list->content));
    node->content = p;
    node->next = NULL;
    node->prev = list;
    list->next = node;
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