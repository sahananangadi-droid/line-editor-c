#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 256

char lines[MAX_LINES][MAX_LEN];
int count = 0;

int main(void)
{
    char input[MAX_LEN + 20];
    printf("Line Editor. Type q to quit.\n");
    while (1)
    {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        input[strcspn(input, "\n")] = '\0';
        if (input[0] == 'q')
            break;
        printf("You typed: %s\n", input);
    }
    return 0;
}