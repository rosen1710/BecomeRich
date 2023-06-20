#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MIN_DIFFICULTY 1
#define MAX_DIFFICULTY 10
#define MAX_TEXT_LENGTH 255

#define DATA_FILE_NAME "data.txt"
#define BEGIN_FILE_MESSAGE "Successfully"
#define USED_QUESTION_MESSAGE "Used"
#define UNUSED_QUESTION_MESSAGE "Free"

struct Question
{
    int difficulty; // number from MIN_DIFFICULTY to MAX_DIFFICULTY
    char* name;
    char* correct_ans;
    char* wrong_ans_1;
    char* wrong_ans_2;
    char* wrong_ans_3;
};

/* struct Node
{
    struct Question q;
    struct Node* next;
}; */

struct Question init_empty_question()
{
    struct Question q;
    q.difficulty = 0;
    q.name = strdup("");
    q.correct_ans = strdup("");
    q.wrong_ans_1 = strdup("");
    q.wrong_ans_2 = strdup("");
    q.wrong_ans_3 = strdup("");
    return q;
}

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

struct Question copy_question(struct Question source_q)
{
    struct Question q;
    q.difficulty = source_q.difficulty;
    q.name = strdup(source_q.name);
    q.correct_ans = strdup(source_q.correct_ans);
    q.wrong_ans_1 = strdup(source_q.wrong_ans_1);
    q.wrong_ans_2 = strdup(source_q.wrong_ans_2);
    q.wrong_ans_3 = strdup(source_q.wrong_ans_3);
    return q;
}

// delete all elements in LinkedList
/* void free_ll(struct Node* head)
{
    struct Node* iterator;
    while (head != NULL)
    {
        iterator = head;
        head = head->next;
        free(iterator);
    }
} */

/* void add_question_in_ll(struct Node** head, struct Question q)
{
    struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));

	struct Node* iterator = *head;

	new_node->q = copy_question(q);

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
} */

/* void print_all_questions_from_ll(struct Node* head)
{
    struct Node* iterator;
    iterator = head;

    while (iterator != NULL)
    {
        printf("\nQuestion with difficulty level %d:\n    %s\n\t%-20s\t%-20s\n\t%-20s\t%-20s\n", iterator->q.difficulty, iterator->q.name, iterator->q.correct_ans, iterator->q.wrong_ans_1, iterator->q.wrong_ans_2, iterator->q.wrong_ans_3);
        iterator = iterator->next;
    }
} */

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
    char* text = strdup("");
    FILE* data_file;
    data_file = fopen(DATA_FILE_NAME, "r");
    if (data_file == NULL)
    {
        printf("\nFile was not found");
        // fclose(data_file);
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
        fclose(data_file);//
        printf(", but it was created successfully!\n\n");
    }
    else
    {
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
        exit(-1);
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
    
    fclose(data_file);//
    return 0;
}

int get_question_from_file(struct Question* result_question_ptr, int difficulty, int key_0, int key_1, int key_2, int key_3)
{
    if (load_file(key_0, key_1, key_2, key_3) == -2)
    {
        return -2;
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

    result_question_ptr->difficulty = difficulty;
    // printf("testing 1 get question from file\n");
    char* text = strdup("");
    text = realloc (text, (MAX_TEXT_LENGTH + 1) * sizeof(char));
    text = strcpy(text, "");
    // printf("testing 2 get question from file\n");
    fscanf(data_file, "%[^\n]\n", text); // reading BEGIN_FILE_MESSAGE
    decrypt(text, key_0, key_1, key_2, key_3);
    // printf("'%s' success\n", text);

    int gotten_diff, i;
    long position;
    bool used;
    fscanf(data_file, "%[^\n]\n", text);
    // printf("before cycle: '%s'\n", text);
    while (strcmp(text, BEGIN_FILE_MESSAGE) != 0 && strcmp(text, result_question_ptr->wrong_ans_3) != 0) // && strcmp(text, "") != 0 && strcmp(text, "\n") != 0 && strcmp(text, "\0") != 0
    {
        // printf("string: '%s'; ", text);
        decrypt(text, key_0, key_1, key_2, key_3);
        // printf("decrypted string: '%s'; number: %d\n", text, atoi(text));
        
        gotten_diff = atoi(text);

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
            // fseek(data_file, -(strlen(UNUSED_QUESTION_MESSAGE) + 2), SEEK_CUR);
            fseek(data_file, position - (strlen(UNUSED_QUESTION_MESSAGE) + 2), SEEK_SET);
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
        result_question_ptr->name = realloc (result_question_ptr->name, (strlen(text) + 1) * sizeof(char));
        strcpy(result_question_ptr->name, text);

        fscanf(data_file, "%[^\n]\n", text); // reading correct_ans
        decrypt(text, key_0, key_1, key_2, key_3);
        result_question_ptr->correct_ans = realloc (result_question_ptr->correct_ans, (strlen(text) + 1) * sizeof(char));
        strcpy(result_question_ptr->correct_ans, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_1
        decrypt(text, key_0, key_1, key_2, key_3);
        result_question_ptr->wrong_ans_1 = realloc (result_question_ptr->wrong_ans_1, (strlen(text) + 1) * sizeof(char));
        strcpy(result_question_ptr->wrong_ans_1, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_2
        decrypt(text, key_0, key_1, key_2, key_3);
        result_question_ptr->wrong_ans_2 = realloc (result_question_ptr->wrong_ans_2, (strlen(text) + 1) * sizeof(char));
        strcpy(result_question_ptr->wrong_ans_2, text);

        fscanf(data_file, "%[^\n]\n", text); // reading wrong_ans_3
        decrypt(text, key_0, key_1, key_2, key_3);
        result_question_ptr->wrong_ans_3 = realloc (result_question_ptr->wrong_ans_3, (strlen(text) + 1) * sizeof(char));
        strcpy(result_question_ptr->wrong_ans_3, text);
        
        fscanf(data_file, "%[^\n]\n", text); // reading the next difficulty or nothing (the text still keeps result_question_ptr->wrong_ans_3) if this is the end of the file

        if (gotten_diff == difficulty && used == false)
        {
            // fclose(data_file);
            free(text);
            return 0;
        }
    }
    // fclose(data_file);
    free(text);

    // printf("\nThere is no unused question with the requested difficulty (level %d) in the file!\n\n", difficulty);

    return -5;
}

/* void overwrite_all_questions_in_file(struct Node* head, int key_0, int key_1, int key_2, int key_3)
{
    FILE* data_file;
    data_file = fopen(DATA_FILE_NAME, "w");
    if (data_file == NULL)
    {
        printf("\nAn error occurred while creating the file!\n\n");
        // return -1;
        exit(-1);
    }
    else
    {
        fprintf(data_file, "%s\n", encrypt(strdup(BEGIN_FILE_MESSAGE), key_0, key_1, key_2, key_3));
        fclose(data_file);
        struct Node* iterator = head;
        while (iterator != NULL)
        {
            add_question_in_file(copy_question(iterator->q), key_0, key_1, key_2, key_3);
            iterator = iterator->next;
        }
    }
} */

/* int get_all_unused_questions(struct Node* result_linkedlist_head, int key_0, int key_1, int key_2, int key_3)
{
    if (load_file(key_0, key_1, key_2, key_3) == -2)
    {
        return -2;
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

    free_ll(result_linkedlist_head);
    struct Question q;

    for (int i = MIN_DIFFICULTY; i <= MAX_DIFFICULTY; i++)
    {
        q = init_empty_question();
        // printf("test difficulty: %d\n", i);
        while (get_question_from_file(&q, i, key_0, key_1, key_2, key_3) == 0)
        {
            add_question_in_ll(&result_linkedlist_head, q);
        }
    }
    // struct Question q[1 + MAX_DIFFICULTY - MIN_DIFFICULTY];

    // for (int i = MIN_DIFFICULTY; i <= MAX_DIFFICULTY; i++)
    // {
    //     q[i - MIN_DIFFICULTY] = init_empty_question();
    //     printf("test difficulty: %d\n", i);
    //     while (get_question_from_file(&(q[i - MIN_DIFFICULTY]), i, key_0, key_1, key_2, key_3) == 0)
    //     {
    //         add_question_in_ll(&result_linkedlist_head, q[i - MIN_DIFFICULTY]);
    //     }
    // }

    overwrite_all_questions_in_file(result_linkedlist_head, key_0, key_1, key_2, key_3);

    return 0;
} */

void test()
{
    // the keys must be 0 - 32; now the correct keys are: 17, 10, 20, 6
    int key_0, key_1, key_2, key_3;
    do
    {
        printf("Input keys [k0 k1 k2 k3]: ");
        scanf("%d %d %d %d", &key_0, &key_1, &key_2, &key_3); // now the correct keys are: 17, 10, 20, 6
    } while (load_file(key_0, key_1, key_2, key_3) == -2); // while the used keys are wrong
    printf("\nThe file was loaded correctly!\n\n");
    
    struct Node* head = NULL;
    struct Question q;
    int res;
    // q = init_empty_question();
    q = init_question(3, "How many dots define one plain?", "3 dots", "1 dot", "2 dots", "4 dots");
    // add_question_in_file(q, key_0, key_1, key_2, key_3);

    // // get_all_unused_questions(head, key_0, key_1, key_2, key_3);
    // // add_question_in_ll(&head, q);
    // // overwrite_all_questions_in_file(head, key_0, key_1, key_2, key_3);

    if ((res = get_question_from_file(&q, 10, key_0, key_1, key_2, key_3)) == 0)
    {
        printf("\nThe question was gotten correctly!\n\n");
        printf("\nQuestion with difficulty level %d:\n    %s\n\t%-20s\t%-20s\n\t%-20s\t%-20s\n", q.difficulty, q.name, q.correct_ans, q.wrong_ans_1, q.wrong_ans_2, q.wrong_ans_3);
    }
    else if (res == -5)
    {
        printf("\nThere is no unused question with the requested difficulty in the file!\n\n");
    }
    if ((res = get_question_from_file(&q, 3, key_0, key_1, key_2, key_3)) == 0)
    {
        printf("\nThe question was gotten correctly!\n\n");
        printf("\nQuestion with difficulty level %d:\n    %s\n\t%-20s\t%-20s\n\t%-20s\t%-20s\n", q.difficulty, q.name, q.correct_ans, q.wrong_ans_1, q.wrong_ans_2, q.wrong_ans_3);
    }
    else if (res == -5)
    {
        printf("\nThere is no unused question with the requested difficulty in the file!\n\n");
    }
    // // print_all_questions_from_ll(head);
    // printf("end\n");
}

void main()
{
    test();
}