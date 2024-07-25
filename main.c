#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char Buffer[0x1000] = {0};
char *keys[0x200] = {0};
void toLowercase(char *str)
{
    int i = 0;
    while (str[i])
    {
        str[i] = tolower(str[i]);
        i++;
    }
}
void GenKeys()
{
    toLowercase(Buffer);
    char *c = Buffer;
    char *wrdstart = Buffer;
    char **Key = keys;
    while ((*c))
    {
        if ((*c) == ' ' || (*c == '\n'))
        {
            *c = 0;
            *Key = wrdstart;
            wrdstart = c + 1;
            Key++;
        }
        c++;
    }
    *Key = NULL;
}
typedef struct _LEARNING LEARNING;
typedef struct _LEARNING
{
    UINT64 Instruction; // 0 = answer, 1 = execute, 2 = Add, 3 = Multiply
    UINT64 DataLength;
    char *Match;
    char *Data;
    LEARNING *Child;
    LEARNING *LastChild;
} LEARNING;
LEARNING Learnings[0x20] = {0};
LEARNING *Learnt = Learnings;
void LxTrain(char *Match, char *Data)
{
    Learnt->Match = Match;
    Learnt->Data = Data;
    Learnt++;
}

void Think()
{
    LEARNING *en = Learnings;
    float Farness = 1;
    LEARNING *BestAnswer = NULL;
    for (; en->Match; en++)
    {
        char *c = en->Match, *bf = Buffer;
        double Len = (double)strlen(c);
        double f = 0;

        for (; (*c); c++)
        {
            if (*bf)
            {
                f += ((double)abs((*c) - (*bf)) / 100) * Len;
                bf++;
            }
            else
                f += 1 / Len;
        }
        printf("far %lf ||| %s  :  answer %s\n", f, en->Match, en->Data);
        if (f < Farness)
        {
            BestAnswer = en;
            Farness = f;
        }
    }
    if (!BestAnswer)
        printf("I do not understand what you are trying to say, can you please clarify?\n");
    else
    {
        printf("Farness : %lf\n\n", Farness);
        printf("%s\n", BestAnswer->Data);
    }
}

int main()
{
    LxTrain("hello", "Hi, how are you");
    LxTrain("how is your day", "It's very good!");
    LxTrain("welcome", "You're welcome too");
    LxTrain("salam", "Kiday Labas");
    LxTrain("salamo alaykum", "Wa alaykumu salamo wa rahmatou lahi ta'ala wa barakatuh :)");
    // printf("Hello AI\n");
    for (;;)
    {

        printf("> ");

        fgets(Buffer, 0xFFF, stdin);

        GenKeys();
        printf("You asked : %s\n", Buffer);

        Think();
    }
    return 0;
}