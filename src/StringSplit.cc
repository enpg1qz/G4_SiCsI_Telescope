#include <iostream>
#include <string>
#include <vector>

#include "StringSplit.hh"

//字符串分割
std::vector<std::string> StringSplit(std::string str)
{
    std::string pattern="\t\n\v\f\r #";
    std::string::size_type pos;
    std::vector<std::string> result;

    str+=pattern;//扩展字符串以方便操作
    std::string::size_type size=str.size();

    for(std::string::size_type i=0; i<size; i++)
    {
        pos=str.find_first_of(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            if(s!=""){result.push_back(s);}
            i=pos;
        }
    }
    return result;
}
