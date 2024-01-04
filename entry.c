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
List *createDumpFileList(unsigned char *p, long long offset, int flag)
{
    List *new_list;
    new_list = (List *)malloc(sizeof(List));

    if (new_list)
    {
        new_list->prev = NULL;
        new_list->next = NULL;
        new_list->content = p + (2 * BLOCK_SIZE);
      /*  for (int i = 0; i < FOLDER_SIZE; i++)
        {
            if (((folder *)(new_list->content))->entry_array[i] != NULL)
            {
                if (flag == 0)
                {
                    folder *entry = ((folder *)(new_list->content))->entry_array[i];
                    entry = (folder *)((long long)entry - offset);
                    ((folder *)(new_list->content))->entry_array[i] = entry;
                }
                else
                {
                    folder *entry = ((folder *)(new_list->content))->entry_array[i];
                    entry = (folder *)((long long)entry + offset);
                    ((folder *)(new_list->content))->entry_array[i] = entry;
                }
            }
        }*/
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
        }
    }
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (((folder *)(list->content))->entry_array[i] != NULL)
        {
            flag++;
            if (((folder *)((folder *)(list->content))->entry_array[i])->type == 1)
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

int remove_file(List *list, char *name)
{

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
    folder *current_folder = (folder *)(list->content);
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] != NULL)
        {
            if (strcmp(((folder *)(current_folder->entry_array[i]))->name, file_name) == 0 && ((folder *)(current_folder->entry_array[i]))->type == 1)
            {

                return -2;
            }
        }
    }
    char whole_filepath[20];
    snprintf(whole_filepath, sizeof(whole_filepath), "./%s", file_name);
    FILE *fp = fopen(whole_filepath, "r");
    if (fp == NULL)
    {
        printf("Failed to open file '%s'\n", file_name);
        return -3;
    }

    void *ptr = NULL;
    int location;
    our_malloc(5, &ptr, &location);
    if (ptr == NULL)
    {
        fclose(fp);
        return -1;
    }

    file *new_file = (file *)ptr;
    strcpy(new_file->name, file_name);
    new_file->location = location;
    new_file->prev = current_folder;
    new_file->type = 1;
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fread(new_file->content, fsize, 1, fp);
    fclose(fp);

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

int get_file(List *list, char *file_name)
{
    folder *current_folder = (folder *)(list->content);
    file *target_file;
    int file_exists = 0;
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] != NULL)
        {
            if (strcmp(((folder *)(current_folder->entry_array[i]))->name, file_name) == 0 && ((folder *)(current_folder->entry_array[i]))->type == 1)
            {
                file_exists = 1;
                target_file = ((file *)(current_folder->entry_array[i]));
            }
        }
    }
    if (!file_exists)
        return -1;

    FILE *output_file;
    char whole_filepath[20];
    sprintf(whole_filepath, "./dump/%s", file_name);

    output_file = fopen(whole_filepath, "w");
    fwrite(target_file->content, sizeof(char), sizeof(target_file->content), output_file);

    fclose(output_file);
}

int show_content(List *list, char *file_name)
{
    folder *current_folder = (folder *)(list->content);
    for (int i = 0; i < FOLDER_SIZE; i++)
    {
        if (current_folder->entry_array[i] != NULL)
        {
            if (strcmp(((file *)(current_folder->entry_array[i]))->name, file_name) == 0 && ((file *)(current_folder->entry_array[i]))->type == 1)
            {
                printf("%s\n", ((file *)(current_folder->entry_array[i]))->content);
                return 0;
            }
        }
    }

    return -1;
}

void help_information()
{

    printf("List of commands\n");
    printf("'ls' list directory\n");
    printf("'cd' change directory\n");
    printf("'rm' remove\n");
    printf("'mkdir' make directory\n");
    printf("'rmdir' remove directory\n");
    printf("'put' put file into the space\n");
    printf("'get' get file from the space\n");
    printf("'cat' show content\n");
    printf("'status' show status of the space\n");
    printf("'help'\n");
    printf("'exit and store img'\n");
}

void status_information(int size)
{
    printf("partition size: %d\n", size);
    printf("total blocks:   %d\n", size / BLOCK_SIZE);
    printf("used blocks:    %d\n", used_block());
    printf("block size:     %d\n", BLOCK_SIZE);
    printf("free space:     %d\n", size - (used_block() * BLOCK_SIZE));
}