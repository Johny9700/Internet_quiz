#ifndef QUESTION_H
#define QUESTION_H

#include <string>

struct Question
{
	std::string question;
	std::string choices[4];
	std::string correct;
};

#endif // QUESTION_H