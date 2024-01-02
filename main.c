#include "main.h"

int main(void)
{
    int size = 0;
    printf("Input size of a new partition (example 102400\n");
    scanf("%d", &size);
    while (getchar() != '\n')
        ;
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("can't allocate memory space !\n ");
        return -1;
    }
    else
    {
        printf("partition size = %d\n", size);
    }
    manage_space(ptr);
    int location;
    int ret;
    List *head = createList();

    char input[20];
    List *current = head;

    while (1)
    {
        print_buffer_status();
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

        else if (strncmp(input, "cat", 3) == 0)
        {
            show_content(current, input + 4);
        }
        else if (strncmp(input, "rm", 2) == 0)
        {
            ret = remove_file(current, input + 3);
            if (ret == -2)
            {
                printf("not found file\n");
            }
        }
        else if (strncmp(input, "exit", 4) == 0)
        {
            break;
        }
        else
        {
            printf("no such opreation!\n");
        }
    }
    free_total_memory_space();
    return 0;
}