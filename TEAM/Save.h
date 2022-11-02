#include "Win.h"

using namespace std;

class Save
{
public:
    wstring name;
    int level;
    int point;
    Save()
    {
        name = L"";
        level = 1;
        point = 0;
    }
};