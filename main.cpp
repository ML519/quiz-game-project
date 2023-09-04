#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#include "global.h"
#include "math.h"
#include "question.h"

const char player_dir[] = ".\\data\\";

Player* plr;


#include <stdio.h>




/*Player *player_logon() {}*/


int main() {

    LoadQuestions();

   
    std::cout << "Enter your Username: ";
    std::string desired_name;
    std::getline(std::cin, desired_name);

    if (*desired_name.c_str() == *"admin")
    {
        while (true)
        {
            AddQuestion();
        }
    }
    else
    {
        Player plr = LoadPlayerData(desired_name);

        std::cout << "Welcome, " << desired_name << std::endl;

        int chosen_question = -1;
        for (int idx = 0; idx < 10; idx++)
        {
            while (chosen_question == -1 || std::find(plr.answered_questions.begin(), plr.answered_questions.end(), chosen_question) != plr.answered_questions.end())
            {
                chosen_question = Math::RandomInt(1, (int)questions.size());
                if (plr.answered_questions.size() >= questions.size())
                {
                    plr.answered_questions = std::vector<int>{};
                }
            }
            
            std::cout << "Question " << idx + 1 << " of " << "10" << ":" << std::endl;
            DisplayQuestion(questions[chosen_question - 1], plr);
            plr.answered_questions.push_back(chosen_question);
        }
        
        std::cout << "\033[2J\033[1;1H"; //clear screen char array
        std::cout << "Well done, you scored " << plr.score << "! Would you like to save your score?(y/n): ";
        std::string user_ipt;
        std::getline(std::cin, user_ipt);
        if (user_ipt == "y")
        {
            plr.SaveData();
        }
    }
}
