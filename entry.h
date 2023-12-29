#ifndef __ENTRY__
#define __ENTRY__

typedef struct type_folder
{
    int type;
    char name[10];
    struct type_folder *prev;
    void *entry_array[FOLDER_SIZE];
} folder;

typedef struct type_file
{
    int type;
    char name[10];
    struct type_folder *prev;
    char *content;
} file;

typedef struct node_info
{
    void *content;
    struct node_info *prev;
    struct node_info *next;
} List;
List *createList(void *ptr);

int build_directory(List *list, void *ptr, char *name);
void list_directory(List *list);
int change_directory(List *list,char *name);
void print_directory(List *last, List *head);
#endif