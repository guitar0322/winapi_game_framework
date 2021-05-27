#pragma once
#include "GameObject.h"
#include "AnimationClip.h"
#include <map>
//Ʈ������� �߰��� �� �ְ�
//Ʈ������� ������ ������ �߰��Ѵ�
typedef struct tagTransaction {
    bool isReset; //�������� 0���� �����Ұ���
    
}Transaction;
class Animator :
    public Component
{
private:
    int frameStack;
public:
    Animator();
    ~Animator();
    Renderer* renderer;
    AnimationClip* curClip;
    map<string, AnimationClip*> clipMap;
    void Init();
    void Update();
    void Render();
    void SetClip(AnimationClip* newClip);
    void SetClip(AnimationClip* newClip, int startFrame);
    void AddClip(string clipName, AnimationClip* newClip);
    AnimationClip* GetClip(string clipName);
};

