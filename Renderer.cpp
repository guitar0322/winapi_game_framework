#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(const char* filename, int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	HDC temp;
	this->width = width;
	this->height = height;
	image = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)LoadImage(_hInstance, filename, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	oBit = (HBITMAP)SelectObject(image, hBit);
	ReleaseDC(_hWnd, hdc);
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
}

void Renderer::Init()
{
	HDC hdc = GetDC(_hWnd);
	width = transform->GetWidth();
	height = transform->GetHeight();
	image = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	oBit = (HBITMAP)SelectObject(image, hBit);

	rc = RectMakeCenter(this->transform->GetX(), transform->GetY(),
		width, height);
	ReleaseDC(_hWnd, hdc);
}

void Renderer::Render()
{
	if(!KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(_backBuffer->getMemDC(), rc);
	GdiTransparentBlt(
		_backBuffer->getMemDC(),					//복사될 영역의 DC
		rc.left,				//복사될 좌표(left)
		rc.top,					//복사될 좌표(top)
		width,					//복사될 크기 (가로크기)
		height,					//복사될 크기 (세로크기)
		image,					//복사해올 DC 
		0, 0,					//복사해올 시작좌표(left, top)
		width,					//복사해올 가로크기
		height,					//복사해올 세로크기
		RGB(255, 0, 255)		//복사할때 제외할 픽셀값
	);
}

void Renderer::Update()
{
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
}

void Renderer::Resize(int newWidth, int newHeight)
{
	HDC hdc = GetDC(_hWnd);
	HDC temp;

	HBITMAP scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);
	SelectObject(image, oBit);
	oBit = (HBITMAP)SelectObject(image, scaleBitmap);
	ReleaseDC(_hWnd, hdc);
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		newWidth,
		newHeight);

	width = newWidth;
	height = newHeight;
}


