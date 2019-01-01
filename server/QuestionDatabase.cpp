#include "QuestionDatabase.h"

#include <fstream>
#include <error.h>
#include <algorithm>
#include <random>

#include <stdio.h> //WYWAL TO

QuestionDatabase::QuestionDatabase(const char* filename)
{
    std::ifstream input (filename);
    if(input.is_open())
    {
        while(!input.eof())
        {
            Question *question = new Question;
            std::getline(input, question->question);
            for(int i=0; i<4; ++i)
            {
                std::getline(input, question->choices[i]);
            }
            std::getline(input, question->correct);
            questions.push_back(question);
        }
    }
    else
    {
        error(1, errno, "cannot open %s", filename);
    }
    shuffleQuestions();
}

QuestionDatabase::~QuestionDatabase()
{
    for(auto q : questions)
    {
        delete q;
    }
    questions.clear();
    printf("QuestionDatabase destroyed\n"); //WYWAL TO
}

void QuestionDatabase::shuffleQuestions()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);
    notUsedQuestions = questions.size();
}

Question QuestionDatabase::getNextQuestion()
{
    if(notUsedQuestions == 0)
        shuffleQuestions();
    notUsedQuestions -= 1;
    return *questions[notUsedQuestions];
}