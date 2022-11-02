#include "Save.h"
Save::Save()
{
    this->name = "";
    this->level = 1;
    this->point = 0;
}

bool cmp(Save a, Save b)
{
    return (a.level > b.level || (a.level == b.level && a.point > b.point));
}