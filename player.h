#include <string>
#include <fstream>
#include <vector>
#include "global.h"
class Player {
private:
    char pass[32];

public:
    int score;
    int level;
    int user_id;
    std::string username;
    std::vector<int> answered_questions;

    Player(std::string username_arg, int score_arg, int level_arg, int user_id_arg, std::vector<int> answered_questions_arg) {
        username = username_arg;
        score = score_arg;
        level = level_arg;
        user_id = user_id_arg;
        for (int idx = 0; idx < (int)answered_questions_arg.size(); idx++)
        {
            answered_questions.push_back(answered_questions_arg[idx]);
        }
    }

    void SaveData()
    {
        std::string filepath = ".\\data\\players\\" + username + ".plr";
        std::ofstream myfile;
        myfile.open(filepath);
        myfile << username << std::endl;
        myfile << score << std::endl;
        for (int idx = 0; idx < (int)answered_questions.size(); idx++)
        {
            myfile << answered_questions[idx] << ",";
        }
    }
};

inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

Player LoadPlayerData(std::string filename)
{
    std::string filepath = ".\\data\\players\\" + filename + ".plr";
    if (file_exists(filepath))
    {
        
        std::ifstream myfile;
        myfile.open(filepath);
        if (myfile.is_open())
        {
            static std::string line;
            std::getline(myfile, line);
            std::string plr_username = line;
            std::getline(myfile, line);
            int plr_score = std::stoi(line);
            std::getline(myfile, line);
            std::vector<std::string> plr_answered_questions_str = SplitString(line,",");
            std::vector<int> plr_answered_questions;
            for (int idx = 0; idx < plr_answered_questions_str.size(); idx++)
            {
                plr_answered_questions.push_back(std::stoi(plr_answered_questions_str[idx]));
            }
            Player plr(plr_username,plr_score,0,0, plr_answered_questions);
            return plr;
            
        }
       
        myfile.close();
    }
    else
    {
        return Player(filename, 0, 0, 0, std::vector<int>{});
    }
}
