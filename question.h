#include "global.h"
#include "player.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>


const char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";

struct question {
    std::string prompt;
    std::vector<std::string> options;
    std::string answer;
    std::string hint;
};

std::vector<question> questions = {};
/*std::vector<question> questions = {
{"How many days are in a week?",std::vector<std::string>{"7","8","10","14"},"a","Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday"},
{"How many days are in February?",std::vector<std::string>{"7","30","31","28"},"d", "It's less than most months."},
{"What is 100 - 9?",std::vector<std::string>{"72","-8","91","42"},"c", "None"},
{"What is the first day of the week?",std::vector<std::string>{"wednesday","january","friday","monday"},"d", "Begins with M."},
{"How many elements are in the periodic table?",std::vector<std::string>{"9","24","168","118"},"d", "There is 100+ elements."},
{"How many faces does a Dodecahedron have?",std::vector<std::string>{"10","12","28","2"},"b", "More than 10, less than 28"},
{"How many ghosts chase Pac-Man at the start of each game?",std::vector<std::string>{"1","2","4","5"},"c", "None"},
{"What is the 4th letter of the Greek alphabet?",std::vector<std::string>{"delta","theta","epsilon","omicon"},"a","Means difference."},
{"What company was initially known as Blue Ribbon Sports?",std::vector<std::string>{"adidas","puma","reebok","nike"},"d","The current logo is a tick."},
{"How many bones do we have in an ear?",std::vector<std::string>{"4","22","3","6"},"c", "A small amount."}
};*/



question ParseLine(std::string line)
{
    
    std::vector<std::string> parsed_line = SplitString(line,"\t");
    std::vector<std::string> parsed_options = SplitString(parsed_line[1], ",");
    if (parsed_line.size() == 4)
    {
        std::string prompt = parsed_line[0];
        //std::vector<std::string> options{ "7", "8", "10", "14" };
        std::string answer = parsed_line[2];
        std::string hint = parsed_line[3];

        question parsed_question{ prompt ,parsed_options,answer,hint };
        return parsed_question;
    }
    else
    {
        std::cout << "QUESTION LOAD FAILED, STRUCT LENGTH WAS " << parsed_line.size() << std::endl;
    }
    return question{};
   
    
}

void DisplayQuestion(question q_to_display, Player &plr) {
    std::cout << q_to_display.prompt << std::endl;
    for (int i = 0; i < q_to_display.options.size(); i++) {
        std::cout << alphabet[i] << ": " << q_to_display.options[i] << std::endl;
    }
    std::string user_ipt;
    std::cout << "Your answer: ";
    std::getline(std::cin, user_ipt);

    std::string hint_prompt = "hint";
    if (user_ipt == hint_prompt)
    {
        std::cout << "HINT: " << q_to_display.hint << std::endl;
        std::cout << "Your answer: ";
        std::getline(std::cin, user_ipt);
    }

    if (user_ipt == "exit")
    {
        std::cout << "Are you sure you want to exit? (y/n): ";
        std::getline(std::cin, user_ipt);
        if (user_ipt == "y")
        {
            plr.SaveData();
            exit(0);
        }
    }
    std::cout << "\033[2J\033[1;1H"; //clear screen char arrayc
    //std::cin >> user_ipt;
    if (user_ipt == q_to_display.answer) {
        // correct
        std::cout << "Correct! Well done " << plr.username << std::endl;
        plr.score += 1;
        std::cout << "Your current score is " << plr.score << std::endl;
    }
    else {
        // incorrect
        std::cout << "Incorrect, nice try " << plr.username << std::endl;
        std::cout << "Your current score is " << plr.score << std::endl;
    }
    
}

void SaveQuestions()
{
    std::ofstream myfile;
    myfile.open(".\\data\\questions.dat");
    size_t question_size = questions.size();
    
    for (int idx = 0; idx < (int)questions.size(); idx++)
    {
        myfile << questions[idx].prompt << "\t";
        for (int idx2 = 0; idx2 < (int)questions[idx].options.size(); idx2++)
        {
            myfile << questions[idx].options[idx2] << ",";
        }
        myfile << "\t";
        myfile << questions[idx].answer << "\t";
        myfile << questions[idx].hint << "\t\n";
    }
    myfile.close();
}

void LoadQuestions()
{
    std::vector<question> loaded_questions = {};
    
    std::ifstream myfile;
    myfile.open(".\\data\\questions.dat");
    

    

    if (myfile.is_open())
    {
        static std::string line;
        while (std::getline(myfile, line))
        {
            question q_to_load = ParseLine(line);
            loaded_questions.push_back(q_to_load);
        }
        myfile.close();

        for (int idx = 0; idx < (int)questions.size(); idx++)
        {
            questions.pop_back();
        }
        for (int idx = 0; idx < (int)loaded_questions.size(); idx++)
        {
            questions.push_back(loaded_questions[idx]);
        }

        
    }
}

void AddQuestion()
{
    std::string new_q_prompt;
    std::string new_q_answer;
    std::string new_q_hint;
    std::vector<std::string> new_q_options;
    std::cout << "Enter a question prompt to add: ";
    std::getline(std::cin, new_q_prompt);
    if (new_q_prompt == "exit")
    {
        std::string user_ipt;
        std::cout << "Are you sure you want to exit? (y/n): ";
        std::getline(std::cin, user_ipt);
        if (user_ipt == "y")
        {
            exit(0);
        }
    }
    std::cout << "Enter an answer to the question: ";
    std::getline(std::cin, new_q_answer);

    std::cout << "Enter an hint to the answer: ";
    std::getline(std::cin, new_q_hint);

    for (int idx = 0; idx < 4; idx++)
    {
        static std::string current_option;
        std::cout << "Enter option " << alphabet[idx] << " for the question: ";
        std::getline(std::cin, current_option);
        new_q_options.push_back(current_option);
    }
    question new_question{ new_q_prompt,new_q_options,new_q_answer,new_q_hint };
    new_question.options = new_q_options;
    questions.push_back(new_question);
    SaveQuestions();
}
