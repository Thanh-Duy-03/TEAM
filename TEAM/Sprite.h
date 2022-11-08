#pragma once
#include "Functions.h"
using namespace std;

class Sprite
{
private:
    int width;
    int height;
    wchar_t *m_glyphs;
    short *m_colors;

public:
    Sprite();
    Sprite(int width, int height);
    ~Sprite();
    void Create(int width, int height);
    int GetWidth();
    int GetHeight();
    void SetGlyph(int x, int y, short c);
    wchar_t GetGlyph(int x, int y);
    void SetColor(int x, int y, short color);
    short GetColor(int x, int y);
    bool Load(wstring fileName);
    bool Save(wstring fileName);
};
