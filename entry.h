#ifndef __ENTRY__
#define __ENTRY__

typedef struct type_folder
{
    int type;
    char name[10];
    int location;
    struct type_folder *prev;
    void *entry_array[FOLDER_SIZE];
} folder;

typedef struct type_file
{
    int type;
    char name[10];
    int location;
    struct type_folder *prev;
    char content[BLOCK_SIZE * 4];
} file;

typedef struct node_info
{
    struct node_info *prev;
    struct node_info *next;
    void *content;
} List;
List *createList();

int build_directory(List *list, char *name);
void list_directory(List *list);
int change_directory(List *list, char *name);
int delete_directory(List *list, char *name);
void print_directory(List *last, List *head);
int remove_file(List *list, char *file_name);
int put_file(List *list, char *file_name);
int show_content(List *list, char *file_name);
void help_information();
void status_information(int size);
#endif