#ifndef QUESTIONDATABASE_H
#define QUESTIONDATABASE_H

#include <vector>
#include "Question.h"

class QuestionDatabase
{
private:
    std::vector<Question*> questions;
    int notUsedQuestions;
    void shuffleQuestions();
public:
    QuestionDatabase(const char* filename);
    ~QuestionDatabase();
    Question getNextQuestion();
};

#endif // QUESTIONDATABASE_H