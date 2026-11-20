#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

/* Write all lines to a file. Returns 0 on success, -1 on error */
int save_file(const char *name)
{
    FILE *f = fopen(name, "w");
    if (f == NULL)
        return -1;
    for (int i = 0; i < count; i++)
        fprintf(f, "%s\n", lines[i]);
    fclose(f);
    return 0;
}

/* Replace the document with the contents of a file. Returns 0 on success, -1 on error */
int load_file(const char *name)
{
    FILE *f = fopen(name, "r");
    if (f == NULL)
        return -1;
    char buf[MAX_LEN];
    count = 0;
    while (count < MAX_LINES && fgets(buf, MAX_LEN, f) != NULL)
    {
        buf[strcspn(buf, "\n")] = '\0';
        strcpy(lines[count++], buf);
    }
    fclose(f);
    return 0;
}

/* Print every line containing the given text */
void search(const char *text)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strstr(lines[i], text) != NULL)
        {
            printf("%3d: %s\n", i + 1, lines[i]);
            found++;
        }
    }
    if (found == 0)
        printf("Not found.\n");
}

/* Print the number of lines and words in the document */
void show_stats(void)
{
    int words = 0;
    for (int i = 0; i < count; i++)
    {
        int in_word = 0;
        for (int j = 0; lines[i][j] != '\0'; j++)
        {
            if (isspace((unsigned char)lines[i][j]))
            {
                in_word = 0;
            }
            else if (!in_word)
            {
                in_word = 1;
                words++;
            }
        }
    }
    printf("Lines: %d, Words: %d\n", count, words);
}

int main(void)
{
    char input[MAX_LEN + 20];
    printf("Line Editor. Commands: i, d, p, s, l, f, c, q\n");
    while (1)
    {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        input[strcspn(input, "\n")] = '\0';

        char cmd = input[0];
        int n, offset = 0;
        char name[100];

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
        else if (cmd == 's')
        {
            if (sscanf(input, "s %99s", name) != 1)
                printf("Usage: s <filename>\n");
            else if (save_file(name) != 0)
                printf("Error: could not save file.\n");
            else
                printf("Saved %d lines.\n", count);
        }
        else if (cmd == 'l')
        {
            if (sscanf(input, "l %99s", name) != 1)
                printf("Usage: l <filename>\n");
            else if (load_file(name) != 0)
                printf("Error: could not open file.\n");
            else
                printf("Loaded %d lines.\n", count);
        }
        else if (cmd == 'f')
        {
            if (strlen(input) < 3 || input[1] != ' ')
                printf("Usage: f <text to find>\n");
            else
                search(input + 2);
        }
        else if (cmd == 'c')
        {
            show_stats();
        }
        else if (cmd != '\0')
        {
            printf("Unknown command.\n");
        }
    }
    return 0;
}