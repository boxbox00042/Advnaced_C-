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
        return 0;
    }
    else
    {
        printf("partition size = %d\n", size);
    }
    List *head = createList(ptr);
    ptr = (char *)ptr + BLOCK_SIZE;
    char input[20];
    int ret = 0;
    List *current = head;

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
            ret = build_directory(current, ptr, input + 6);
            ptr = (char *)ptr + BLOCK_SIZE;
            if (ret != 0)
            {
                printf("build failed\n");
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
        else
        {
            printf("no such opreation!\n");
        }
    }

    return 0;
}
