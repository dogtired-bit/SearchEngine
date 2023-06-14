#ifndef __DICTPRODUCER_HPP
#define __DICTPRODUCER_HPP

#include <vector>
#include <string>
#include <map>
#include <set>
using std::vector;
using std::string;
using std::map;
using std::set;

class DictProducer
{
public:
    DictProducer(const string &dir);//英文语料目录 
    ~DictProducer(); 
    void buildEnDictAndIndex();             //创建英文字典和英文索引
    void storeEnDict();             //存储英文词典
    void preProcessLine(string &line);

private:
    vector<string> _files;
    map<string,int> _dict;
    map<string,set<int>> _index;

};
#endif
