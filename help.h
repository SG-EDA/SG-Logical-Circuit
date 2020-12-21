#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

class help
{
public:
    static void tab(unsigned int num=0)
    {
        for(unsigned int i=0;i<num;i++)
            cout<<"   ";
    }

    static vector<string> split(const string &s, const string &seperator)
    {
        vector<string> result;
        typedef string::size_type string_size;
        string_size i = 0;

        while(i != s.size())
        {
          //找到字符串中首个不等于分隔符的字母；
          int flag = 0;
          while(i != s.size() && flag == 0)
          {
            flag = 1;
            for(string_size x = 0; x < seperator.size(); ++x)
            if(s[i] == seperator[x])
            {
              ++i;
              flag = 0;
              break;
            }
          }

          //找到又一个分隔符，将两个分隔符之间的字符串取出；
          flag = 0;
          string_size j = i;
          while(j != s.size() && flag == 0)
          {
            for(string_size x = 0; x < seperator.size(); ++x)
            if(s[j] == seperator[x]){
              flag = 1;
              break;
            }
            if(flag == 0)
            ++j;
          }
          if(i != j)
          {
            result.push_back(s.substr(i, j-i));
            i = j;
          }
        }
        return result;
    }

    static int toint(string str)
    {
        return atoi(str.c_str());
    }

    static string readTxt(string file)
    {
        ifstream infile;
        infile.open(file.data());   //将文件流对象与文件连接起来
        assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

        string result;
        string s;
        while(getline(infile,s))
        {
            result+=s+"\n";
        }
        infile.close();             //关闭文件输入流
        return result;
    }
};
