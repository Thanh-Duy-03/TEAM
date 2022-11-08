#include "Sprite.h"
Sprite::Sprite()
{
    this->width = 0;
    this->height = 0;
    this->m_glyphs = NULL;
    this->m_colors = NULL;
}

Sprite::Sprite(int width, int height)
{
    this->width = width;
    this->height = height;
    this->m_glyphs = new wchar_t[width * height];
    for (int i = 0; i < width * height; i++)
    {
        this->m_glyphs[i] = L' ';
    }
    this->m_colors = new short[width * height];
    for (int i = 0; i < width * height; i++)
    {
        this->m_colors[i] = FG_BLACK;
    }
}

Sprite::~Sprite()
{
    if (this->m_glyphs != NULL)
        delete[] this->m_glyphs;
    if (this->m_colors != NULL)
        delete[] this->m_colors;
}

void Sprite::Create(int width, int height)
{
    this->width = width;
    this->height = height;

    if (this->m_glyphs != NULL)
        delete[] this->m_glyphs;
    this->m_glyphs = new wchar_t[width * height];
    for (int i = 0; i < width * height; i++)
    {
        this->m_glyphs[i] = L' ';
    }

    if (this->m_colors != NULL)
        delete[] this->m_colors;
    this->m_colors = new short[width * height];
    for (int i = 0; i < width * height; i++)
    {
        this->m_colors[i] = FG_BLACK;
    }
}

int Sprite::GetWidth()
{
    return this->width;
}

int Sprite::GetHeight()
{
    return this->height;
}

void Sprite::SetGlyph(int x, int y, short c)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
    {
        return;
    }
    else
    {
        this->m_glyphs[y * this->width + x] = c;
    }
}

wchar_t Sprite::GetGlyph(int x, int y)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
    {
        return L' ';
    }
    else
    {
        return this->m_glyphs[y * this->width + x];
    }
}

void Sprite::SetColor(int x, int y, short color)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
    {
        return;
    }
    else
    {
        this->m_colors[y * this->width + x] = color;
    }
}

short Sprite::GetColor(int x, int y)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
    {
        return FG_BLACK;
    }
    else
    {
        return this->m_colors[y * this->width + x];
    }
}

bool Sprite::Load(wstring fileName)
{
    if (this->m_glyphs != NULL)
    {
        delete[] this->m_glyphs;
    }
    if (this->m_colors != NULL)
    {
        delete[] this->m_colors;
    }
    this->width = 0;
    this->height = 0;
    wifstream file(fileName);
    if (file.fail())
        return false;
    locale loc(locale(), new codecvt_utf8_utf16<wchar_t>);
    file.imbue(loc);
    file >> this->width;
    file >> this->height;
    Create(this->width, this->height);
    wstring temp;
    file.ignore();
    getline(file, temp);
    this->m_glyphs = new wchar_t[this->width * this->height];
    for (int i = 0; i < this->width * this->height; i++)
    {
        this->m_glyphs[i] = temp[i];
    }

    this->m_colors = new short[this->width * this->height];
    for (int i = 0; i < this->width * this->height; i++)
    {
        file >> this->m_colors[i];
    }
    file.close();
    return true;
}

bool Sprite::Save(wstring fileName)
{
    wofstream file(fileName);
    if (file.fail())
        return false;
    locale loc(locale(), new codecvt_utf8_utf16<wchar_t>);
    file.imbue(loc);
    file << this->width << endl;
    file << this->height << endl;
    for (int i = 0; i < this->width * this->height; i++)
    {
        file << this->m_glyphs[i];
    }
    file << endl;
    for (int i = 0; i < this->width * this->height; i++)
    {
        file << this->m_colors[i] << endl;
    }
    file.close();
    return true;
}