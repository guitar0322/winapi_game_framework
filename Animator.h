#pragma once
#include "GameObject.h"
#include "AnimationClip.h"
#include <map>
//트랜잭션을 추가할 수 있고
//트랜잭션이 동작할 조건을 추가한다
typedef struct tagTransaction {
    bool isReset; //프레임을 0부터 시작할건지
    
}Transaction;
class Animator :
    public Component
{
private:
    typedef struct tagTransaction {
        AnimationClip* startClip;
        AnimationClip* nextClip;
    }TRANSACTION;
private:
    float frameTime;
public:
    Animator();
    ~Animator();
    Renderer* renderer;
    AnimationClip* curClip;
    AnimationClip* preClip;
    map<string, AnimationClip*> clipMap;
    map<string, TRANSACTION> transactionMap;
    map<string, TRANSACTION>::iterator transactionIter;
    void Init();
    void Update();
    void Render();
    void SetClip(AnimationClip* newClip);
    void SetClip(AnimationClip* newClip, int startFrame);
    void AddClip(string clipName, AnimationClip* newClip);
    AnimationClip* GetClip(string clipName);
    void AddTransaction(string name, AnimationClip* startClip, AnimationClip* nextClip);
    
};

