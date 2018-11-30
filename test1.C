//#include "TLatex.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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

void ReadData(std::fstream& theFile,std::vector<std::vector<std::string> >& result)
{
  result.clear();
	std::string str;
	while(getline(theFile,str)){
		if(str.find_first_not_of("\t\n\v\f\r ")!=std::string::npos){
			if(str[0]!='#'){
				result.push_back(StringSplit(str));
			}
		}
	}
}

int main(){
  fstream theFile;  //   ifstream outFile;
  theFile.open("test-data.txt",ios::in);
  vector<vector<string> > result;
  ReadData(theFile,result);
  for(int i=0;i<result.size();i++){
    cout<<result[i][0]<<"  "<<result[i][1]<<endl;
  }
  return 0;
}
