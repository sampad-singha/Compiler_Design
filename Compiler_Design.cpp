#include <iostream>
#include "RegularEx.h"
#include <vector>
#include <fstream>
#include <string>
#include <stack>
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
                cout<<"Line " <<line << " >> No such header file. \n\t " <<s << endl<<endl;
            }
        }
        else if (j == 0)
        {
            cout << "Line " << line << " >> No header found " << endl<<endl;
            return j;
        }
        else
        {
            return j;
            break;
        }
        j++;
    }
}


//*************     Tokenization        ******************************
void lexAnalyzer(vector<pair<int,string>> code, int line) {
    string fullCode;
    vector<pair<int, string>>::iterator it = code.begin() + line;
    vector<pair<int, string>>::iterator itr = it;
    for (; it != code.end(); it++)
    {
        fullCode += code[line].second;
        line++;
    }

    smatch match;
    vector<pair<string, string>> token;
    Regular regular;
    regex keyword = regular.keyword();
    regex identifier = regular.identifier();


    int lexBgn = 0, frd = 0; bool flag = false;
    for (int i = 0; i < fullCode.size();) {
        string buffer = fullCode.substr(lexBgn, (lexBgn - frd + 1));
        while (regex_match(buffer, identifier)) {
            frd++;
            buffer += fullCode[frd];
            flag = true;
        }
        if (flag) {
            frd--;
            buffer.pop_back();
            flag = false;

            if (regex_match(buffer, keyword))
            {
                token.push_back(make_pair("kw", buffer));
            }
            else {
                token.push_back(make_pair("id", buffer));
            }
        }
        else {
            if (regex_match(buffer, identifier))
            {
                token.push_back(make_pair("id", buffer));
            }
            else if (regex_match(buffer, identifier))
            {
                token.push_back(make_pair("op", buffer));
            }
        }
        cout << buffer << endl;


    }
    /*for (; itr != code.end(); itr++) {
        string s = (*itr).second;
        smatch match;
        while (true) {
            if (regex_search(s, match, keyword))
            {
                token.push_back(make_pair("kw", match[0]));
                s = regex_replace(s, keyword, "\0");
            }
            else if (regex_search(s, match, identifier))
            {
                token.push_back(make_pair("id", match[0]));
                s = regex_replace(s, identifier, "\0");
            }
        }
    }*/

    

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
    
    int j = headerCheck(code);

    
    lexAnalyzer(code, j);


    
}




















/*Regular regular;
    regex mainFunc = regular.mainFunc();

    string fullCode = code[j].second; j++;

    for (; it != code.end(); it++)
    {
        fullCode += code[j].second;
        j++;
    }
    cout << fullCode << endl << endl;
    if (!regex_match(fullCode, mainFunc))
    {
        cout << "Error in code body " << endl;
    }*/


    /*j++;
    string fullCode = code[j].second; j++;
    vector<pair<int, string>>::iterator itr= code.begin();
    auto it = next(itr, j);
    for (; it != code.end(); it++)
    {
        fullCode += code[j].second;
        j++;
    }*/
    //cout << fullCode;


    //regex fullcodereg = regular.fullCodereg();
    /*if (regex_match(fullCode, fullcodereg))
    {
        cout << "error in code body" << endl;
    }*/