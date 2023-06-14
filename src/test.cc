#include <iostream>
#include "../include/DictProducer.hpp"

int main()
{
    DictProducer dic("/home/nanjiang/SearchEngine/data/cn_corpus");
    dic.buildEnDictAndIndex();
    dic.storeEnDict();
    return 0;
}

