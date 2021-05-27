#pragma once
#include "GameObject.h"
#include "image.h"
class Renderer :
    public Component
{
private:
public:
    Renderer();
    ~Renderer();
    HDC image;
    HBITMAP oBit, hBit;
    RECT rc;
    int width;
    int height;
    virtual void Init(const char* filename, int width, int height);
    virtual void Init();
    virtual void Render();
    virtual void Update();
    void Resize(int objWidth, int objHeight);
};

