#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "quiz.h"
#include "type.h"

void print_help()
{
    printf("******Help Menu******\n");
    printf("INFO:  ./quiz [Option]\n");
    printf("INFO:  Options:\n");
    printf("        -e      Easy\n");
    printf("        -m      Medium\n");
    printf("        -h      Hard\n");
    printf("        --help   Help Menu\n");
}

Difficulty parse_difficulty(int argc, char *argv[])
{
    if (strcmp(argv[1], "-e") == 0 )
    {
        return easy;
    }
    if (strcmp(argv[1], "-m") == 0 )
    {
        return medium;
    }
    if (strcmp(argv[1], "-h") == 0 )
    {
        return hard;
    }
    return failure;
}

void load_questions(Question **q, int *q_count, Difficulty level)
{
    static Question easy_q[] = 
    {
        {"Who developed C language?", {"Bjarne Stroustrup", "Dennis Ritchie", "James Gosling", "Guido van Rossum"}, 'B'},
        {"Binary of 5?", {"101", "110", "111", "100"}, 'A'},
        {"Which of the following is an invalid if-else statement?", {"if(func(a)){}", "if(if(a==1)){}", "if(a){}", "if((char)a){}"}, 'B'},
        {"How many times will the loop exeute?for(x = 0; x++;);", {"1", "compilation error", "0", "infinite"}, 'C'},
        {"What is the return value of sizeof() in 64-bit maachine?", {"long int", "unsigned int", "int", "unsigned long int"}, 'D'},
        {"sizeof is", {"an operator", "a function", "a macro", "None of the above"}, 'A'},
        {"How many time will loop execute?\nfor(;;);", {"infinite", "zero", "compiler error", "one"}, 'A'},
        {"Which for loop will run faster?\nCode-A\nfor(int i = 0; i < 100;i++)\nfor(int j = 0; j < 10; j++)\nCode-B\nfor(int i = 0; i < 10;i++)\nfor(int j = 0; j < 100; j++)", {"Code A", "Code B", "Both are same"}, 'B'},
        {"Which of the following cannot be checked in a switch-case statement?", {"short", "int", "char", "float"}, 'D'},
        {"What will happen if you assign a value to an array element whose subscript exceed the size of array?", {"It may overwrite other variables", "The array size would appropriately grow", "The compiler would report an error", "The element will be set to 0"}, 'A'}
    };

    static Question medium_q[] = 
    {
        {"What is the output of the following code\nint main()\n{\nint a=0,b=4, c=3, d=0;\nif(a,b,c,d)\nprintf(''%d'',b);\n}", {"Nothing is printed", "4", "0", "compiler error"}, 'A'},
        {"What is the output of the following code\nint main()\n{\nint i = 0X53F;\nprintf(''%X'',i+1);\n}", {"540", "53G", "compiler error", "none"}, 'A'},
        {"Select the correct order for SDLC phases?", {"Requirements Analysis -> Design -> Implementation -> Testing", "Requirements Analysis -> Design -> Testing -> Implementation", "Requirements Analysis -> Implementation -> Design -> Testing", "Requirements Analysis -> Implementation -> Testing -> Design"}, 'A'},
        {"What is output?\nint main()\n{\nint i = 10;\ngotolabel 2;\nwhile(i)\n{\nswitch(i-1)\n{case 1:\nlabel2:\nprintf(''%d'',i);\n}\n}\n}", {"Prints 10 infinite times", "Prints 10 and infinite loop", "Infinite loop(prints nothing)", "Compiler error"}, 'B'},
        {"What is output of following program assuming 32-bitsystem?\nint main()\n{\nprintf(''%zu\n'',sizeof(6.5));\nprintf(''%zu\n'',sizeof(9000));\nprintf(''%zu\n'',sizeof('A'));\n}", {"4 2 1", "8 4 2", "4 4 1", "8 4 4"}, 'D'},
        {"What is output?\nvoid main()\n{\nint lookup[100] = {0,1,2,3,4,5,6,7,8,9};\nprintf(''%d'', lookup[1]);\n}", {"0", "2", "compiler error", "1"}, 'D'},
        {"What is output of code:\nvoid main()\n{\nint num;\nint *ptr = &num;\nfor(*ptr = 13;ptr;(*ptr)--)\n{\nprintf(''%d'',*ptr);\n}\n}", {"13 to 0", "12 to 0", "13 to 1", "None"}, 'D'},
        {"Point out the error in program\n\nf(int a, int b)\n{\nint a;\na = 20; return a;\n}", {"Missing parenthesis in return statement", "The function should be efined as int f(int a, int b)", "Redeclaration of a", "None of above"}, 'C'},
        {"What is output?\nvoid main()\n{\nint a[3] = {1, 2, 3};\nint *p = a;\nprintf(''%p %p'', p, a);\n}", {"Nothing", "Compile time error", "Different address is printed", "Same address is printed"}, 'D'},
        {"Which keyword can be used for coming out of recurssion?", {"break", "return", "exit", "both (a) and (b)"}, 'B'}
    };

    static Question hard_q[] = 
    {
        {"What is output:\nint main()\n{\nint arr[] = {};\nprintf(''%zu'',sizeof(arr));\n}", {"4", "0", "compiler error", "segmentation fault"}, 'B'},
        {"What is output of C code?\nint main()\n{\nint y = 2, z;\nz = (y + (y= 10));\nprintf(''%d'',z);\n}", {"compiler error", "20", "12", "4"}, 'B'},
        {"How many times will loop execute?\nint main()\n{\nint i;\nfor(i = 10 == 0; i <= 10; i++)\nprintf(''%d'',i);\n}", {"10", "0", "11", "1"},'C'},
        {"What are the different ways to represent a design?", {"Algorithm and Pseudo Code", "Algorithm and Flowchart", "Algorithm, Flowchart and Pseudo Code", "Algorithm"}, 'C'},
        {"What is output for following code:\nint main()\n{\nint i = -1;\ndo\n{\n--i;\nprintf(''%d'', i);\ni++;\n}while(i<=0);\n}", {"-2 infinite times", "-1", "0", "None of above"}, 'A'},
        {"What will be the output?\nint main()\n{\nint i = 1;\nif(!i)printf(''Hello, '');\nelse\n{\ni = 0;\nprintf(''C-Program'');\nmain();\n}\nreturn 0;\n}", {"prints ''C-Program, Hello'' infinitely", "prints ''C-Program'' infinitely", "Run time error", "prints ''Hello, C-Program'' infinitely"}, 'C'},
        {"What is output?\nint main()\n{\nstatic int num = 16;\nint num = 7;\nprintf(''%d'', num);\n}", {"16", "Compiler Error", "7", "Implementation dependent"}, 'B'},
        {"Which of following statements are correct about the program?\nint main()\n{\nint a;\na = f(10, 3.14);\nprintf(''%d'', a);\nreturn 0;\n}\nfloat f(int aa, float bb)\n{\nreturn((float)aa + bb);\n}", {"Add Prototype: float f(bb, aa)", "Add Prototype: float f(aa, bb)", "Add Prototype: float f(float, int)", "Add Prototype: float f(int, float)"}, 'D'},
        {"What is the output?\nint main()\n{\nunsigned char ch;\nfor(ch = 0x30; ch <= 0x39; ch++)\nprintf(''%c'', ch);\nreturn 0;\n}", {"none", "prints from 0 to 9", "prints from 0x30 to 0x39", "infinite loop"}, 'B'},
        {"What is expected answer for this code?\nvoid foo(int*);\nint main()\n{\nint i = 10;\nfoo((&i)++);\n}\nvoid foo(int *p)\n{\nprintf(''%d''*p);\n}", {"Error:Lvalue required", "10", "11", "None of above"}, 'A'}
    };

    switch(level) 
    {
        case easy:
            *q = malloc(sizeof(easy_q));
            memcpy(*q, easy_q, sizeof(easy_q));
            *q_count = sizeof(easy_q)/sizeof(easy_q[0]);
            break;
        case medium:
            *q = malloc(sizeof(medium_q));
            memcpy(*q, medium_q, sizeof(medium_q));
            *q_count = sizeof(medium_q)/sizeof(medium_q[0]);
            break;
        case hard:
            *q = malloc(sizeof(hard_q));
            memcpy(*q, hard_q, sizeof(hard_q));
            *q_count = sizeof(hard_q)/sizeof(hard_q[0]);
            break;
    }
}

int conduct_quiz(Question *q, int count)
{
    int i, score = 0;
    char ans;
    for (i = 0; i < count; i++)
    {
        printf("\nQ%d: %s\n", i + 1, q[i].question);
        printf("A) %s\nB) %s\nC) %s\nD) %s\n", q[i].options[0], q[i].options[1]
                                             , q[i].options[2], q[i].options[3]);
        printf("Your answer: ");
        scanf(" %c", &ans);
        if (toupper(ans) == q[i].correct) 
        {
            score++;
        }
    }
    return score;
}

void save_score(Student student)
{
    FILE *fp = fopen("result.txt", "a");
    if (fp == NULL)
    {
        perror("Error opening scoreboard file");
        return ;
    }
    fprintf(fp, "%s\t\t| %s\t| %d\t| %s\n", student.name, student.id, student.score,difficulty_to_string(student.level));
    fclose(fp);
}

/* Display Score Board*/
void show_scoreboard()
{
    FILE *fp = fopen("result.txt", "r");
    if (fp == NULL)
    {
        printf("No scoreboard found\n");
        return ;
    }
    printf("\n****** SCOREBOARD ******\n");
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }
    fclose(fp);
}

const char* difficulty_to_string(Difficulty d)
{
    switch (d)
    {
    case easy:
        return "Easy";
    case medium:
        return "Medium";    
    case hard:
        return "Hard";
    default:
        return "Unknown";
    }
}