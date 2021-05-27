#include "stdafx.h"
#include "RockMan.h"

void RockMan::Init()
{
    renderer = (Renderer*)(AddComponent(new Renderer()));
    renderer->Init();
    collider = (BoxCollider*)(AddComponent(new BoxCollider()));
    collider->Init();
    animator = (Animator*)(AddComponent(new Animator()));
    animator->Init();
    controler = (PlayerControler*)AddComponent(new PlayerControler());
    controler->Init();
    InitClip();
}

void RockMan::Update()
{
    GameObject::Update();
}

void RockMan::Render()
{
    GameObject::Render();
}

void RockMan::InitClip()
{
    idleRight = new AnimationClip();
    idleRight->Init("mega_man_idle_right.bmp", 960, 96, 10, 10);

    idleLeft = new AnimationClip();
    idleLeft->Init("mega_man_idle_left.bmp", 960, 96, 10, 10);

    runRight = new AnimationClip();
    runRight->Init("mega_man_run_right.bmp", 1536, 96, 16, 5);

    runLeft = new AnimationClip();
    runLeft->Init("mega_man_run_left.bmp", 1536, 96, 16, 5);

    jumpRight = new AnimationClip();
    jumpRight->Init("mega_man_jump_right.bmp", 1056, 108, 11, 4);
    jumpRight->isLoop = false;

    jumpLeft = new AnimationClip();
    jumpLeft->Init("mega_man_jump_left.bmp", 1056, 108, 11, 4);
    jumpLeft->isLoop = false;

    wallRight = new AnimationClip();
    wallRight->Init("mega_man_wall_right.bmp", 384, 116, 4, 3);
    wallRight->isLoop = false;

    wallLeft = new AnimationClip();
    wallLeft->Init("mega_man_wall_left.bmp", 384, 116, 4, 3);
    wallLeft->isLoop = false;
    
    animator->AddClip("idle_right", idleRight);
    animator->AddClip("idle_left", idleLeft);
    animator->AddClip("run_right", runRight);
    animator->AddClip("run_left", runLeft);
    animator->AddClip("jump_right", jumpRight);
    animator->AddClip("jump_left", jumpLeft);
    animator->AddClip("wall_right", wallRight);
    animator->AddClip("wall_left", wallLeft);

    animator->SetClip(animator->GetClip("idle_right"));
}
