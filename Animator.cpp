#include "stdafx.h"
#include "Animator.h"

Animator::Animator()
{
}


Animator::~Animator()
{

}

void Animator::Init()
{
	renderer = gameObject->GetComponent<Renderer>();
	if (renderer == nullptr) {
		throw "Animator에서 발생 : 게임 오브젝트에 Renderer컴포넌트가 없습니다";
	}
}

void Animator::Update()
{
	if (curClip == nullptr)
		return;
	frameStack++;
	if (frameStack == curClip->frameTerm) {
		BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
			curClip->wholeDC, curClip->frameWidth * curClip->currentFrame, 0, SRCCOPY);
		curClip->currentFrame++;
		if (curClip->currentFrame == curClip->frameNum) {
			if (curClip->isLoop == true)
				curClip->currentFrame = 0;
			else
				curClip->currentFrame = curClip->frameNum - 1;
		}
		frameStack = 0;
	}
}

void Animator::Render()
{

}

void Animator::SetClip(AnimationClip* newClip)
{
	curClip = newClip;
	curClip->currentFrame = 0;
	frameStack = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, 0, 0, SRCCOPY);
}

void Animator::SetClip(AnimationClip* newClip, int startFrame)
{
	curClip = newClip;
	curClip->currentFrame = startFrame;
	frameStack = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, curClip->currentFrame * curClip->frameWidth, 0, SRCCOPY);
}

void Animator::AddClip(string clipName, AnimationClip* newClip)
{
	clipMap.insert(make_pair(clipName, newClip));
}

AnimationClip* Animator::GetClip(string clipName)
{
	map<string, AnimationClip*>::iterator iter;
	iter = clipMap.find(clipName);
	if (iter != clipMap.end()) {
		return iter->second;
	}
	return nullptr;
}
