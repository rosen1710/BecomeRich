#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "File_crypting.c"

// Returns 0 if adding is successfull; 
// Exits with -1 if it cannot create/write in file;
// Returns -2 if wrong keys were used;
int addQuestion (int key_0, int key_1, int key_2, int key_3) {
    int diff;
    char name[MAX_TEXT_LENGTH];
    char correct[MAX_TEXT_LENGTH];
    char wrongOne[MAX_TEXT_LENGTH];
    char wrongTwo[MAX_TEXT_LENGTH];
    char wrongThree[MAX_TEXT_LENGTH];

    printf("Input difficulty: ");
    scanf ("%d", &diff);
    getchar();
    printf("Input question: ");
    scanf("%[^\n]", name);
    getchar();
    printf("Input correct answer: ");
    scanf("%[^\n]", correct);
    getchar();
    printf("Input wrong answer 1: ");
    scanf("%[^\n]", wrongOne);
    getchar();
    printf("Input wrong answer 2: ");
    scanf("%[^\n]", wrongTwo);
    getchar();
    printf("Input wrong answer 3: ");
    scanf("%[^\n]", wrongThree);
    getchar();

    struct Question q = init_question(diff, name, correct, wrongOne, wrongTwo, wrongThree);

    return add_question_in_file(q, key_0, key_1, key_2, key_3);
}

/* int main () {
    addQuestion();

    int flag; // Contains state from getting question
    
    struct Question q = init_empty_question();

    flag = get_question_from_file(&q, 3, 17, 10, 20, 6);
    if(flag == 0) printf("\nQuestion with difficulty level %d:\n    %s\n\t%-20s\t%-20s\n\t%-20s\t%-20s\n", q.difficulty, q.name, q.correct_ans, q.wrong_ans_1, q.wrong_ans_2, q.wrong_ans_3);
    else if (flag == -5) printf("\nThere is no unused question with the requested difficulty in the file!\n");
    
    return 0;
} */