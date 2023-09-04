#pragma once
std::vector<std::string> SplitString(std::string str, std::string delimiter)
{
    std::vector<std::string> parsed_str;
    std::string token;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        parsed_str.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    return parsed_str;
}
