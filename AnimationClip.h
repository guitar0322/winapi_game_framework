#pragma once
class AnimationClip
{
public:
	HDC wholeDC;
	HBITMAP hBit, oBit;
	int frameNum;
	int frameTerm;
	int frameWidth;
	int frameHeight;
	int currentFrame;
	bool isLoop;
	HRESULT Init(const char* filename, int width, int height, int frameNum, int frameTerm);
	AnimationClip();
	~AnimationClip();
};

