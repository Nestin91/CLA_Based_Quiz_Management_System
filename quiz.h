#ifndef QUIZ_H
#define QUIZ_H

#include<stdio.h>
#include "type.h"

#define MAX_NAME 50
#define MAX_ID 20

typedef struct _Quiz
{
    char question[256];
    char options[4][100];
    char correct;
}Question;

typedef struct _Student
{
    char name[MAX_NAME];
    char id[MAX_ID];
    int score;
    Difficulty level;
}Student;

// Function prototypes

/* Print Help Menu*/
void print_help();
Difficulty parse_difficulty(int argc, char *argv[]);
void load_questions(Question **q, int *q_count, Difficulty level);
int conduct_quiz(Question *q, int q_count);
void save_score(Student student);

/* Display Score Board*/
void show_scoreboard();

const char* difficulty_to_string(Difficulty d);

#endif