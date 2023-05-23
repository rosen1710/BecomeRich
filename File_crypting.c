#include <stdio.h>
#include <string.h>

#define DATA_FILE_NAME "data.txt"
#define BEGIN_FILE_MESSAGE strdup("Success_data_file_open_begin_message")

char* encrypt(char* text, int key_0, int key_1, int key_2, int key_3) // the keys must be 24 - 32
{
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        if (i%4 == 0)
        {
            text[i] += 4 * key_0;
        }
        else if (i%4 == 1)
        {
            text[i] += 4 * key_1;
        }
        else if (i%4 == 2)
        {
            text[i] += 4 * key_2;
        }
        else if (i%4 == 3)
        {
            text[i] += 4 * key_3;
        }
    }
    return text;
}

char* decrypt(char* text, int key_0, int key_1, int key_2, int key_3)
{
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        if (i%4 == 0)
        {
            text[i] -= 4 * key_0;
        }
        else if (i%4 == 1)
        {
            text[i] -= 4 * key_1;
        }
        else if (i%4 == 2)
        {
            text[i] -= 4 * key_2;
        }
        else if (i%4 == 3)
        {
            text[i] -= 4 * key_3;
        }
    }
    return text;
}

int main()
{
    // char c;
    char* text = BEGIN_FILE_MESSAGE;
    // char* text = strdup("AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz 11223344556677889900 !!@@##$$%%%%^^&&**(())--__==++[[{{}}]]''\\||//??<<>>");
    // printf("%s\n", text);
    // printf("%s\n", encrypt(text, 24, 25, 26, 27));
    // printf("%s\n", decrypt(text, 24, 25, 26, 27));
    FILE* data_file;
    data_file = fopen(DATA_FILE_NAME, "r");
    if (data_file == NULL)
    {
        printf("File was not found!\n");
        fclose(data_file);
        FILE* data_file;
        data_file = fopen(DATA_FILE_NAME, "w");
        fprintf(data_file, "%s\n", encrypt(BEGIN_FILE_MESSAGE, 24, 25, 26, 27));
    }
    else
    {
        /* c = fgetc(data_file);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(data_file);
        } */
        fscanf(data_file, "%s", text);
        printf("%s\n", text);
        printf("%s\n", decrypt(text, 24, 25, 26, 27));

        if (strcmp(BEGIN_FILE_MESSAGE, text) != 0)
        {
            printf("You have used wrong keys!");
            return -1;
        }
        // Load data from file
    }
    fclose(data_file);
    
    printf("Hello world!\n");
    return 0;
}