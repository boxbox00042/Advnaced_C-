#include "main.h"

int main(void)
{
    int size = 0;
    int option;
    printf("options\n");
    printf("1. loads from file\n");
    printf("2. create new partition in memory\n");
    List *head;
    List *current;
    void *ptr;
    scanf("%d", &option);
    while (getchar() != '\n')
        ;
    if (option == 2)
    {
        printf("Input size of a new partition (example 102400\n");
        scanf("%d", &size);
        while (getchar() != '\n')
            ;
        ptr = malloc(size);
        if (ptr == NULL)
        {
            printf("can't allocate memory space !\n ");
            return -1;
        }
        else
        {
            printf("partition size = %d\n", size);
            printf("\nMake new partition successful !\n");
        }
        manage_space(ptr, size);
        put_metadata_space(size);
        head = createList();
        current = head;
    }
    else
    {
        unsigned char * fs_ptr;
        long long now_location = loadDump(&fs_ptr, &size);
        if(now_location == -1) 
        {
            return 0;
        }

        long long fs_ptr_location = (long long)(fs_ptr);
        long long offset;
        int flag = 0;
        if (now_location > fs_ptr_location)
        {
            offset = now_location - fs_ptr_location;
            flag = 0;
            head = createDumpFileList(fs_ptr, offset, flag);
        }
        else
        {
            offset = fs_ptr_location - now_location;
            flag = 1;
            head = createDumpFileList(fs_ptr, offset, flag);
        }
        dump_manage_space(fs_ptr, size);
        put_dump_metadata_space(size);
        change_element_offset(size, flag, offset);

        current = head;
        ptr = fs_ptr;
    }
    int ret;
    char input[50];

    help_information();
    while (1)
    {
        print_directory(current, head);
        fgets(input, sizeof(input), stdin);

        int len = strlen(input);

        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }
        if (strncmp(input, "mkdir", 5) == 0)
        {
            ret = build_directory(current, input + 6);
            if (ret != 0)
            {
                printf("space full\n");
            }
        }
        else if (strncmp(input, "ls", 2) == 0)
        {
            list_directory(current);
        }
        else if (strncmp(input, "rmdir", 5) == 0)
        {
            ret = delete_directory(current, input + 6);
            if (ret == -1)
            {
                printf("Please delete the things in the folder first\n");
            }
            if (ret == -2)
            {
                printf("not found directory\n");
            }
        }
        else if (strncmp(input, "cd", 2) == 0)
        {

            if (strncmp(input, "cd ..", 5) == 0)
            {
                if (current->prev != NULL)
                {

                    current = current->prev;
                    free(current->next);
                }
            }
            else
            {

                ret = change_directory(current, input);
                if (ret == 0)
                {
                    current = current->next;
                }
                else
                {
                    printf("not found directory !\n");
                }
            }
        }
        else if (strncmp(input, "put", 3) == 0)
        {
            ret = put_file(current, input + 4);
            if (ret == -1)
            {
                printf("No Space\n");
            }
            else if (ret == -2)
            {
                printf("File already exists.\n");
            }
        }
        else if (strncmp(input, "get", 3) == 0)
        {
            ret = get_file(current, input + 4);
            if (ret == -1)
            {
                printf("File do not exists.\n");
            }
        }
        else if (strncmp(input, "cat", 3) == 0)
        {
            ret = show_content(current, input + 4);
            if (ret != 0)
            {
                printf("not found file\n");
            }
        }
        else if (strncmp(input, "rm", 2) == 0)
        {
            ret = remove_file(current, input + 3);
            if (ret == -2)
            {
                printf("not found file\n");
            }
        }
        else if (strcmp(input, "help") == 0)
        {
            help_information();
        }
        else if (strcmp(input, "status") == 0)
        {
            status_information(size);
        }
        else if (strncmp(input, "rename", 6) == 0)
        {
            char *old_name = strtok(input + 7, " ");
            char *new_name = strtok(NULL, " ");

            if (old_name == NULL || new_name == NULL)
            {
                printf("Invalid command format.\n");
            }
            else
            {
                ret = rename_file(current, old_name, new_name);
                if (ret == -1)
                {
                    printf("file not found.\n");
                }
            }
        }
        else if (strcmp(input, "exit and store img") == 0)
        {
            exitAndStore(ptr, size);
            break;
        }
        else if (strncmp(input, "create", 6) == 0)
        {
            ret = create_file(current, input + 7);
            if (ret == -1)
            {
                printf("No Space\n");
            }
            else if (ret == -2)
            {
                printf("File already exists.\n");
            }
        }
        else if (strncmp(input, "edit", 4) == 0)
        {
            ret = edit_file(current, input + 5);
            if (ret == -1)
            {
                printf("File do not exists.\n");
            }
        }
        else
        {
            printf("no such opreation!\n");
        }
    }
    free_total_memory_space();
    return 0;
}