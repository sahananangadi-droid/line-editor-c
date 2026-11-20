#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 256

char lines[MAX_LINES][MAX_LEN];
int count = 0;

/* Print all lines with line numbers */
void display(void)
{
    if (count == 0)
    {
        printf("(document is empty)\n");
        return;
    }
    for (int i = 0; i < count; i++)
        printf("%3d: %s\n", i + 1, lines[i]);
}

/* Insert text as line n, shifting lines down. Returns 0 on success, -1 on error */
int insert_line(int n, const char *text)
{
    if (count >= MAX_LINES)
        return -1; /* document full */
    if (n < 1 || n > count + 1)
        return -1;                   /* invalid position */
    for (int i = count; i >= n; i--) /* shift lines down */
        strcpy(lines[i], lines[i - 1]);
    strncpy(lines[n - 1], text, MAX_LEN - 1);
    lines[n - 1][MAX_LEN - 1] = '\0';
    count++;
    return 0;
}

/* Delete line n, shifting lines up. Returns 0 on success, -1 on error */
int delete_line(int n)
{
    if (n < 1 || n > count)
        return -1;                          /* invalid line */
    for (int i = n - 1; i < count - 1; i++) /* shift lines up */
        strcpy(lines[i], lines[i + 1]);
    count--;
    return 0;
}

int main(void)
{
    char input[MAX_LEN + 20];
    printf("Line Editor. Commands: i, d, p, q\n");
    while (1)
    {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        input[strcspn(input, "\n")] = '\0';

        char cmd = input[0];
        int n, offset = 0;

        if (cmd == 'q')
        {
            break;
        }
        else if (cmd == 'p')
        {
            display();
        }
        else if (cmd == 'i')
        {
            if (sscanf(input, "i %d %n", &n, &offset) < 1 || offset == 0)
            {
                printf("Usage: i <line number> <text>\n");
            }
            else if (insert_line(n, input + offset) != 0)
            {
                printf("Error: invalid line number or document full.\n");
            }
        }
        else if (cmd == 'd')
        {
            if (sscanf(input, "d %d", &n) != 1)
                printf("Usage: d <line number>\n");
            else if (delete_line(n) != 0)
                printf("Error: no such line.\n");
        }
        else if (cmd != '\0')
        {
            printf("Unknown command.\n");
        }
    }
    return 0;
}