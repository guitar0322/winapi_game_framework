#pragma once
#include "GameObject.h"

enum enumState {
    IDLE_RIGHT,
    IDLE_LEFT,
    RUN_RIGHT,
    RUN_LEFT,
    JUMP_RIGHT,
    JUMP_LEFT,
    WALL_RIGHT,
    WALL_LEFT
};
class PlayerControler :
    public Component
{
public:
    PlayerControler() {};
    ~PlayerControler() {};
    Animator* animator;
    BoxCollider* collider;
    enumState state;
    float gravity;
    float jumpPower;
    float wallJumpPower;
    bool isJump;
    bool isWall;
    bool isDive;
    int diveTime;
    RECT groundRc;
    void Init();
    void Update();
    void Render();
    bool CheckGround();
    void DebugState();
};
