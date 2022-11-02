#include "Win.h"

using namespace std;

class Save
{
public:
    Save();

public:
    string name;
    int level;
    int point;
};

bool cmp(Save a, Save b);