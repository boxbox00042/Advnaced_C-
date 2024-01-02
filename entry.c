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
            if (((folder *)((folder *)(list->content))->entry_array[i])->type == 0)
            {
                printf(BLU "%s " RESET, ((folder *)((folder *)(list->content))->entry_array[i])->name);
            }
            else
            {
                printf("%s ", ((file *)((folder *)(list->content))->entry_array[i])->name);
            }
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
            if (strcmp(((folder *)((folder *)(list->content))->entry_array[i])->name, name + 3) == 0 && ((folder *)((folder *)(list->content))->entry_array[i])->type == 0)
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
            if (strcmp(((folder *)(current_folder->entry_array[i]))->name, name) == 0 && ((folder *)(current_folder->entry_array[i]))->type == 0)
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

int remove_file(List *list, char *name){

  folder *current_folder = (folder *)(list->content);
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] != NULL)
        {
            if (strcmp(((folder *)(current_folder->entry_array[i]))->name, name) == 0 && ((file *)(current_folder->entry_array[i]))->type == 1)
            {
                
                our_free(5, ((file *)(current_folder->entry_array[i]))->location);
                current_folder->entry_array[i] = NULL;
                return 0;
            }
        }
    }

    return -2;
}

int put_file(List *list, char *file_name) // location跟size跟prev
{

    char whole_filepath[1024];
    sprintf(whole_filepath, "%s%s", "./", file_name);

    folder *current_folder = (folder *)(list->content);
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] != NULL &&
            strcmp(((file *)(current_folder->entry_array[i]))->name, file_name) == 0)
        {

            return -2;
        }
    }

    FILE *fp = fopen(whole_filepath, "r");
    if (fp == NULL)
    {
        printf("Failed to open file '%s'\n", file_name);
        return -3;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    void *ptr = NULL;
    int location;
    our_malloc(5, &ptr, &location);
    if (ptr == NULL)
    {
        return -1;
    }
    file *new_file = ptr;
    new_file->content = ptr;
    new_file->type = 1;
    fclose(fp);
    new_file->content[fsize] = 0; // 確保字符串結尾
    new_file->size = fsize;
    strcpy(new_file->name, file_name);
    new_file->location = location;
    new_file->prev = current_folder;

    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] == NULL)
        {
            current_folder->entry_array[i] = new_file;
            break;
        }
    }

    return 0;
}

int show_content(List *list, char *file_name)
{
    folder *current_folder = (folder *)(list->content);
    int file_found = 0;
    char whole_filepath[1024];
    sprintf(whole_filepath, "%s%s", ".\\", file_name);
    char buffer[1024];

    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] != NULL &&
            strcmp(((file *)(current_folder->entry_array[i]))->name, file_name) == 0)
        {
            file_found = 1;
            break;
        }
    }

    if (!file_found)
    {
        printf("File not found in the directory.\n");
        return -1;
    }

    FILE *fp = fopen(whole_filepath, "r");
    if (fp == NULL)
    {
        perror("Failed to open file");
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("%s", buffer);
    }
    printf("\n");
    fclose(fp);

    return 0;
}
