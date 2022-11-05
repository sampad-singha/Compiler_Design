#include <iostream>
#include "RegularEx.h"
#include <vector>
#include<fstream>
using namespace std;

//*************     clearing left and right space/tab    ******************
vector<pair<int,string>> clearSpace(vector<pair<int, string>> code1)
{
    int j = 0;

    Regular regular;
    regex preSpace = regular.preSp();
    regex postSpace = regular.postSp();
    vector<pair<int, string>> code2;

    for (auto i = code1.begin(); i != code1.end(); i++, j++)
    {
        if (!regex_match(code1[j].second, preSpace))
        {
            code2.push_back(make_pair(code1[j].first, regex_replace(code1[j].second, preSpace, "\0")));
        }
    }
    j = 0;
    vector<pair<int, string>> code3;
    for (auto i = code2.begin(); i != code2.end(); i++, j++)
    {
        if (!regex_match(code2[j].second, postSpace))
        {
            code3.push_back(make_pair(code2[j].first, regex_replace(code2[j].second, postSpace, "\0")));
        }
    }
    return code3;
}

//*************     header check        ******************************

int headerCheck(vector<pair<int, string>> code)
{
    int j = 0, line;
    Regular regular;
    regex header = regular.header();
    string s;
    for (auto i:code)
    {
        s = code[j].second;
        line = code[j].first;
        if (s[0] == '#')
        {
            if (!regex_match(s.begin(), s.end(), header))
            {
                cout<<"Line " <<line << " >> No such header file. \n\t " <<s << endl;
            }
        }
        else
        {
            return j;
            break;
        }
        j++;
    }
}

int main()
{
    fstream file;
    file.open("IDE.txt", ios::in);
    vector<pair<int, string>> primaryCode;
    string s;
    int lineNum = 1;
    while (!file.eof())
    {
        getline(file, s);
        primaryCode.push_back(make_pair(lineNum, s));
        lineNum++;
    }
    vector<pair<int, string>> code = clearSpace(primaryCode);
    
    int j = 0;
    for (auto i : code)
    {
        cout << code[j].first << " " << code[j].second << endl;
        j++;
    }
    headerCheck(code);
}
