#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DATA_FILE_NAME "data.txt"
#define BEGIN_FILE_MESSAGE "Successfully"
#define USED_QUESTION_MESSAGE "Used"
#define UNUSED_QUESTION_MESSAGE "Free"

struct Question
{
    int difficulty; // number from 1 to 10
    char* name;
    char* correct_ans;
    char* wrong_ans_1;
    char* wrong_ans_2;
    char* wrong_ans_3;
};

struct Node
{
    struct Question q;
    struct Node* next;
};

/* struct LinkedList
{
    struct Node* head;
}; */

struct Question init_question(int difficulty, char* name, char* correct_ans, char* wrong_ans_1, char* wrong_ans_2, char* wrong_ans_3)
{
    struct Question q;
    q.difficulty = difficulty;
    q.name = strdup(name);
    q.correct_ans = strdup(correct_ans);
    q.wrong_ans_1 = strdup(wrong_ans_1);
    q.wrong_ans_2 = strdup(wrong_ans_2);
    q.wrong_ans_3 = strdup(wrong_ans_3);
    return q;
}

/* struct Node* init_ll()
{
    struct Node* head;
    // struct Question q = init_question(0, "", "", "", "", "");
    // head.next = NULL;
    // head.q = q;
    head = NULL;
    return head;
} */

// delete all elements in LinkedList
void free_ll(struct Node* head)
{
    struct Node* iterator;
    while (head != NULL)
    {
        iterator = head;
        head = head->next;
        free(iterator);
    }
}

void add_question_in_ll(struct Node** head, struct Question q)
{
    /* struct Node* new_node;
    new_node = (struct Node*) calloc (1, sizeof(struct Node*));
    printf("here\n");
    new_node->q = q;
    new_node->next = NULL;
    if (head == NULL)
    {
        head = new_node;
        return;
    }
    
    struct Node* iterator;
    iterator = head;

    while (iterator->next != NULL)
    {
        iterator = iterator->next;
    }
    iterator->next = new_node; */
    
	struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));

	struct Node* iterator = *head;

	new_node->q = q;

	new_node->next = NULL;

	if (*head == NULL)
	{
        *head = new_node;
	}
    else
    {
        while (iterator->next != NULL)
        {
            iterator = iterator->next;
        }
        
        iterator->next = new_node;
    }
}

void print_all_questions_from_ll(struct Node* head)
{
    struct Node* iterator;
    iterator = head;

    while (iterator != NULL)
    {
        printf("\nQuestion with difficulty level %d:\n    %s\n\t%s\t\t%s\n\t%s\t\t%s\n", iterator->q.difficulty, iterator->q.name, iterator->q.correct_ans, iterator->q.wrong_ans_1, iterator->q.wrong_ans_2, iterator->q.wrong_ans_3);
        iterator = iterator->next;
    }
}

// the keys must be 0 - 32
char* encrypt(char* text, int key_0, int key_1, int key_2, int key_3)
{
    if (key_0 < 0 || key_0 > 32 || key_1 < 0 || key_1 > 32 || key_2 < 0 || key_2 > 32 || key_3 < 0 || key_3 > 32)
    {
        printf("\nYou have used wrong keys (they must be 0 - 32)!\n\n");
        exit(-2);
    }
    key_0 += 96;
    key_1 += 96;
    key_2 += 96;
    key_3 += 96;
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        if (i%4 == 0)
        {
            text[i] += key_0;
        }
        else if (i%4 == 1)
        {
            text[i] += key_1;
        }
        else if (i%4 == 2)
        {
            text[i] += key_2;
        }
        else
        {
            text[i] += key_3;
        }
    }
    return text;
}

// the keys must be 0 - 32
char* decrypt(char* text, int key_0, int key_1, int key_2, int key_3)
{
    if (key_0 < 0 || key_0 > 32 || key_1 < 0 || key_1 > 32 || key_2 < 0 || key_2 > 32 || key_3 < 0 || key_3 > 32)
    {
        printf("\nYou have used wrong keys (they must be 0 - 32)!\n\n");
        exit(-2);
    }
    key_0 += 96;
    key_1 += 96;
    key_2 += 96;
    key_3 += 96;
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        if (i%4 == 0)
        {
            text[i] -= key_0;
        }
        else if (i%4 == 1)
        {
            text[i] -= key_1;
        }
        else if (i%4 == 2)
        {
            text[i] -= key_2;
        }
        else
        {
            text[i] -= key_3;
        }
    }
    return text;
}

// the keys must be 0 - 32
int load_file(int key_0, int key_1, int key_2, int key_3)
{
    // char c;
    char* text = strdup("");
    FILE* data_file;
    data_file = fopen(DATA_FILE_NAME, "r");
    if (data_file == NULL)
    {
        printf("\nFile was not found");
        fclose(data_file);
        FILE* data_file;
        data_file = fopen(DATA_FILE_NAME, "w");
        if (data_file == NULL)
        {
            printf("!\n\nAn error occurred while creating the file!\n\n");
            // return -1;
            exit(-1);
        }
        else
        {
            fprintf(data_file, "%s\n", encrypt(strdup(BEGIN_FILE_MESSAGE), key_0, key_1, key_2, key_3));
        }
        fclose(data_file);
        printf(", but it was created successfully!\n\n");
    }
    else
    {
        /* c = fgetc(data_file);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(data_file);
        } */
        fscanf(data_file, "%[^\n]", text);
        // printf("%s\n", text);
        // printf("%s\n", decrypt(text, key_0, key_1, key_2, key_3));
        decrypt(text, key_0, key_1, key_2, key_3);
        
        // fclose(data_file);

        if (strcmp(BEGIN_FILE_MESSAGE, text) != 0)
        {
            printf("\nYou have used wrong keys!\n\n");
            return -2;
        }
    }
    
    // printf("\nThe file was loaded correctly!\n\n");
    return 0;
}

int add_question_in_file(struct Question q, int key_0, int key_1, int key_2, int key_3)
{
    if (load_file(key_0, key_1, key_2, key_3) == -2)
    {
        return -2;
    }

    if (strlen(USED_QUESTION_MESSAGE) != strlen(UNUSED_QUESTION_MESSAGE))
    {
        printf("\nERROR: Your messages for 'used' and 'unused' question are not with the same lenght!\n\n");
        exit(-3);
    }

    FILE* data_file;
    data_file = fopen(DATA_FILE_NAME, "a");
    if (data_file == NULL)
    {
        return -1;
    }

    char* difficulty_string = strdup("");
    sprintf(difficulty_string, "%d", q.difficulty);

    fprintf(data_file, "%s\n", encrypt(difficulty_string, key_0, key_1, key_2, key_3));
    fprintf(data_file, "%s\n", encrypt(strdup(UNUSED_QUESTION_MESSAGE), key_0, key_1, key_2, key_3));
    fprintf(data_file, "%s\n", encrypt(q.name, key_0, key_1, key_2, key_3));
    fprintf(data_file, "%s\n", encrypt(q.correct_ans, key_0, key_1, key_2, key_3));
    fprintf(data_file, "%s\n", encrypt(q.wrong_ans_1, key_0, key_1, key_2, key_3));
    fprintf(data_file, "%s\n", encrypt(q.wrong_ans_2, key_0, key_1, key_2, key_3));
    fprintf(data_file, "%s\n", encrypt(q.wrong_ans_3, key_0, key_1, key_2, key_3));
    
    fclose(data_file);
    return 0;
}

struct Question get_question(int difficulty, int key_0, int key_1, int key_2, int key_3)
{
    if (load_file(key_0, key_1, key_2, key_3) == -2)
    {
        exit(-2);
    }

    FILE* data_file;
    data_file = fopen(DATA_FILE_NAME, "r+");
    if (data_file == NULL)
    {
        exit(-1);
    }

    if (strlen(USED_QUESTION_MESSAGE) != strlen(UNUSED_QUESTION_MESSAGE))
    {
        printf("\nERROR: Your messages for 'used' and 'unused' question are not with the same lenght!\n\n");
        exit(-3);
    }

    struct Question q = init_question(difficulty, "", "", "", "", "");
    char* text = strdup("");
    fscanf(data_file, "%[^\n]\n", text); // reading BEGIN_FILE_MESSAGE
    decrypt(text, key_0, key_1, key_2, key_3);
    // printf("'%s' success\n", text);

    int gotten_diff, i;
    long position;
    bool used;
    fscanf(data_file, "%[^\n]\n", text);
    while (strcmp(text, BEGIN_FILE_MESSAGE) != 0 && strcmp(text, q.wrong_ans_3) != 0) // && strcmp(text, "") != 0 && strcmp(text, "\n") != 0 && strcmp(text, "\0") != 0
    {
        // printf("string: '%s'; ", text);
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("decrypted string: '%s'; number: '%d'\n", text, atoi(text));
        
        gotten_diff = atoi(text);
        /* if (gotten_diff == 0)
        {
            break;
        } */

        fscanf(data_file, "%[^\n]\n", text); // reading USED_QUESTION_MESSAGE or UNUSED_QUESTION_MESSAGE
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        if (strcmp(UNUSED_QUESTION_MESSAGE, text) == 0)
        {
            used = false;
        }
        else if (strcmp(USED_QUESTION_MESSAGE, text) == 0)
        {
            used = true;
        }
        else
        {
            printf("\nERROR: Your message for 'used' or 'unused' question was not recognized!\n\n");
            exit(-4);
        }

        if (gotten_diff == difficulty && used == false)
        {
            strcpy(text, USED_QUESTION_MESSAGE);
            encrypt(text, key_0, key_1, key_2, key_3);
            position = ftell(data_file);
            fseek(data_file, -(strlen(UNUSED_QUESTION_MESSAGE) + 2), SEEK_CUR);
            for (i = 0; i < strlen(text); i++)
            {
                fputc(text[i], data_file);
            }
            fputc('\n', data_file);
            // fprintf(data_file, "%s\n", encrypt(strdup(USED_QUESTION_MESSAGE), key_0, key_1, key_2, key_3));
            fseek(data_file, position, SEEK_SET);
        }
        
        fscanf(data_file, "%[^\n]\n", text); // reading question name
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.name, text);

        fscanf(data_file, "%[^\n]\n", text); // reading correct_ans
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.correct_ans, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_1
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.wrong_ans_1, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_2
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.wrong_ans_2, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_3
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.wrong_ans_3, text);
        
        fscanf(data_file, "%[^\n]\n", text); // reading the next difficulty or "" if this is the end

        if (gotten_diff == difficulty && used == false)
        {
            return q;
        }
    }
    // fclose(data_file);

    printf("\nThere is no unused question with the requested difficulty (level %d) in the file!\n\n", difficulty);

    exit(-5);
}

void get_all_unused_questions(struct Node* head, int key_0, int key_1, int key_2, int key_3)
{
    if (load_file(key_0, key_1, key_2, key_3) == -2)
    {
        exit(-2);
    }

    FILE* data_file;
    data_file = fopen(DATA_FILE_NAME, "r+");
    if (data_file == NULL)
    {
        exit(-1);
    }

    if (strlen(USED_QUESTION_MESSAGE) != strlen(UNUSED_QUESTION_MESSAGE))
    {
        printf("\nERROR: Your messages for 'used' and 'unused' question are not with the same lenght!\n\n");
        exit(-3);
    }

    // struct Node* head = NULL;
    struct Question q = init_question(0, "", "", "", "", "");
    char* text = strdup("");
    fscanf(data_file, "%[^\n]\n", text); // reading BEGIN_FILE_MESSAGE
    decrypt(text, key_0, key_1, key_2, key_3);
    // printf("'%s' success\n", text);

    int gotten_diff, i;//, count = 0;
    // long position;
    bool used;
    fscanf(data_file, "%[^\n]\n", text);
    while (strcmp(text, BEGIN_FILE_MESSAGE) != 0 && strcmp(text, q.wrong_ans_3) != 0) // && strcmp(text, "") != 0 && strcmp(text, "\n") != 0 && strcmp(text, "\0") != 0
    {
        // printf("string: '%s'; ", text);
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("decrypted string: '%s'; number: '%d'\n", text, atoi(text));
        
        gotten_diff = atoi(text);
        /* if (gotten_diff == 0)
        {
            break;
        } */
        q.difficulty = gotten_diff;

        fscanf(data_file, "%[^\n]\n", text); // reading USED_QUESTION_MESSAGE or UNUSED_QUESTION_MESSAGE
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        if (strcmp(UNUSED_QUESTION_MESSAGE, text) == 0)
        {
            used = false;
        }
        else if (strcmp(USED_QUESTION_MESSAGE, text) == 0)
        {
            used = true;
        }
        else
        {
            printf("\nERROR: Your message for 'used' or 'unused' question was not recognized!\n\n");
            exit(-4);
        }

        /* if (gotten_diff == difficulty && used == false)
        {
            strcpy(text, USED_QUESTION_MESSAGE);
            encrypt(text, key_0, key_1, key_2, key_3);
            position = ftell(data_file);
            fseek(data_file, -(strlen(UNUSED_QUESTION_MESSAGE) + 2), SEEK_CUR);
            for (i = 0; i < strlen(text); i++)
            {
                fputc(text[i], data_file);
            }
            fputc('\n', data_file);
            // fprintf(data_file, "%s\n", encrypt(strdup(USED_QUESTION_MESSAGE), key_0, key_1, key_2, key_3));
            fseek(data_file, position, SEEK_SET);
        } */
        
        fscanf(data_file, "%[^\n]\n", text); // reading question name
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.name, text);

        fscanf(data_file, "%[^\n]\n", text); // reading correct_ans
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.correct_ans, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_1
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.wrong_ans_1, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_2
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.wrong_ans_2, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_3
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("'%s'\n", text);
        strcpy(q.wrong_ans_3, text);
        
        fscanf(data_file, "%[^\n]\n", text); // reading the next difficulty or "" if this is the end

        if (used == false)
        {
            add_question_in_ll(&head, q);
        }
    }
    // fclose(data_file);
    // return head;
}

void main()
{
    // the keys must be 0 - 32; now the correct keys are: 17, 10, 20, 6
    int key_0, key_1, key_2, key_3;
    printf("Input keys ['key_0' 'key_1' 'key_2' 'key_3']: ");
    scanf("%d %d %d %d", &key_0, &key_1, &key_2, &key_3); // the keys must be 0 - 32
    while (load_file(key_0, key_1, key_2, key_3) == -2) // while the used keys are wrong; now the correct keys are: 17, 10, 20, 6
    {
        // in this loop the used keys are wrong, because load_file() returns -2
        // here we must loop inputing new keys until they become correct and load_file() return 0
        printf("Input keys ['key_0' 'key_1' 'key_2' 'key_3']: ");
        scanf("%d %d %d %d", &key_0, &key_1, &key_2, &key_3); // now the correct keys are: 17, 10, 20, 6
    }
    printf("\nThe file was loaded correctly!\n\n");
    struct Node* head = NULL;
    struct Question q;
    q = init_question(10, "How many dots define one plain?", "3 dots", "1 dot", "2 dots", "4 dots");
    // add_question_in_ll(&head, q);
    // add_question_in_file(q, key_0, key_1, key_2, key_3);
    get_all_unused_questions(head, key_0, key_1, key_2, key_3);
    print_all_questions_from_ll(head);
    // q = get_question(10, key_0, key_1, key_2, key_3);
    printf("\nThe question was gotten correctly!\n\n");
    printf("\nQuestion with difficulty level %d:\n    %s\n\t%s\t\t%s\n\t%s\t\t%s\n", q.difficulty, q.name, q.correct_ans, q.wrong_ans_1, q.wrong_ans_2, q.wrong_ans_3);
}