/*
Name : Nestin Gregorios Sunny

Date : 09.07.2025

Description :
Individual Project 2 - Implemented code for Quiz management system 

Function Demonstrated:
1. Conduct quiz thorugh command terminal
2. Added 3 difficulty mode, where user can choose which level of difficuty he/she would like to attend the quiz

Sample input:
./quiz

Sample output:
******Help Menu******
INFO:  ./quiz [Option]
INFO:  Options:
        -e      Easy
        -m      Medium
        -h      Hard
        --help   Help Menu
        
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "quiz.h"
#include "type.h"

int main(int argc, char **argv)
{
    Student student;
    Question *q = NULL;

    // Checking for no. of arguments
    if (argc < 2)
    {
        print_help();
        return failure;
    }

    // If argument is for help
    if (strcmp(argv[1], "--help") == 0)
    {
        print_help();
        return success;
    }
    
    // Checking what difficulty level user chose
    Difficulty level = parse_difficulty(argc, argv);
    if (level == -1)
    {
        printf("Invalid difficulty option\n");
        print_help();
        return failure;
    }
    
    // Getting student details
    printf("Enter your Name: ");
    scanf("%[^\n]", student.name);
    printf("Enter your ID: ");
    scanf(" %[^\n]", student.id);

    student.level = level;

    //Load questions based on difficulty level chose
    int q_count = 0;
    load_questions(&q, &q_count, level);

    printf("\nStarting Quiz(%s Level)\n", difficulty_to_string(level));
    printf("***********************\n");
    student.score = conduct_quiz(q, q_count);

    printf("***********************\n");
    printf("Quiz Finished\n");
    printf("Your Score : %d / %d\n", student.score, q_count);

    save_score(student);
    show_scoreboard();

    free(q);

    return success;
}