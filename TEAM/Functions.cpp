#include "Functions.h"
string WstringToString(wstring wstr)
{
    string temp(wstr.begin(), wstr.end());
    return temp;
}

wstring StringToWstring(string str)
{
    wstring temp(str.begin(), str.end());
    return temp;
}