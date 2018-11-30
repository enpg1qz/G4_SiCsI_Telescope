//#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ReadLine.hh"
#include "StringSplit.hh"

//读一行
void ReadLine(std::fstream& theFile,std::vector<std::string>& result)
{
  result.clear();
  for(int symbol0=0;symbol0==0;){
    std::string str;
    if(getline(theFile,str)){
      if(str.find_first_not_of("\t\n\v\f\r ")!=std::string::npos){
        if(str[0]!='#'){
          symbol0=symbol0+1;
          result=StringSplit(str);
        }
      }
    }
  }
}
