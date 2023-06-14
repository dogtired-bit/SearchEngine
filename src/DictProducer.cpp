#include "../include/DictProducer.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::istringstream;

DictProducer::DictProducer(const string &dir)//英文语料目录
{
    //初始化英文索引词典
    for(char ch = 'a';ch <= 'z';++ch)
    {
        string key(1,ch);
        _index[key] = set<int>();
    }

    //读英文语料目录
    DIR *pDir= opendir("dir");
    if(!pDir)
    {
        perror("opendir");
        return;
    }
    struct dirent *pDirent;
    while((pDirent = readdir(pDir)))
    {
        if(strcmp(pDirent->d_name,".") != 0 && strcmp(pDirent->d_name,"..") != 0)
        {
            _files.push_back(dir + "/" + pDirent->d_name);
        }
    }
    closedir(pDir);
}

DictProducer::~DictProducer()
{

}

//处理一行英文
void DictProducer::preProcessLine(string &line)
{
    for(auto &ch:line)
    {
        if(!isalpha(ch))
        {
            ch = ' ';
        }
        else if(isupper(ch))
        {
            ch = tolower(ch);
        }
    }
}

//创建英文字典和英文索引
void DictProducer::buildEnDictAndIndex()       
{
    for(auto &filepath:_files)
    {
        ifstream ifs(filepath);
        if(!ifs)
        {
            perror("ifstream open error");
            return;
        }
        string line;
        int cnt = 0;
        while(getline(ifs,line))
        {
            preProcessLine(line);            
            string word;
            istringstream iss(line);
            while(iss >> word)
            {
                ++_dict[word];
                for(auto &ch:word)
                {
                    _index[string(1,ch)].insert(cnt);
                }
            }
            ++cnt;
        }
    }
    ifs.close(ifs);
}

//存储英文词典
void DictProducer::storeEnDict()
{
    ofstream ofs("../data/dict/en_dict.dat"); 
    if(!ofs)
    {
        perror("ofstream open file error");
        return;
    }
    for(auto &word:_dict)
    {
        ofs << word.first << " " << word.second << "\n";
    }
    ofs.close(ofs);
}
