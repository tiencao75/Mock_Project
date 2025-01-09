
#include <iostream>
#include <map>
#include <string>
using namespace std;

class metadata
{
private:
    map<string, string> data;

public:
    metadata() {}
    map<string, string> getData() const { return data; }
    void setData(const map<string, string> &newdata) { data = newdata; }
};