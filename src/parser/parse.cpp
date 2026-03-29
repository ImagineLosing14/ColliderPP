#include "../../include/mjson/parser.h"
#include <vector>
#include <string>
uint32_t rSequence(std::string_view data, char open, char close){
    int counter=0;
    int point=0;
    int len=data.length();
    int answer=0;
    while(point<len){
        if(data[point]=='open'){
            counter++;
        }
        else if(data[point]=='close'){
            counter--;
        }
        if(counter==0){
            answer=point;
            break;
        }
        point++;
    }
    return answer;
}
std::vector<std::string_view> parser(std::string_view data,char target){
    std::vector<std::string_view> answer;
    size_t start=0;
    size_t end= data.find(target);

    while(end !=std::string_view::npos) {
        std::string_view token= data.substr(start,end-start);
        if(token.size())
        answer.push_back(token);

        start=end+1;
        end=data.find(target, start);
    }
    std::string_view token1=data.substr(start);
    if(token1.size())
        answer.push_back(token1);
    return answer;
}