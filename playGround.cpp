#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{

}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init();
	_camShakeFrame = 0;
	_mainCam.transform->SetX(_mainCam.transform->GetX() + 100);

	_rockMan = new RockMan();
	_rockMan->Init();
	_rockMan->transform->SetX(_rockMan->transform->GetX() - 300);
	_rockMan->transform->SetY(_rockMan->transform->GetY() + 150);

	_smallObj.GetComponent<Renderer>()->Init("small_object.bmp", 98, 224);
	_smallObj.GetComponent<BoxCollider>()->SetSize(98, 224);
	_smallObj.transform->SetPosition(_rockMan->transform->GetX() + 150, _rockMan->transform->GetY() - 62);
	_smallObj.AddComponent(new ObjectInfo(false));

	_bigObj.GetComponent<Renderer>()->Init("big_object.bmp", 104, 320);
	_bigObj.GetComponent<BoxCollider>()->SetSize(104, 320);
	_bigObj.transform->SetPosition(_rockMan->transform->GetX() + 500, _rockMan->transform->GetY() - 110);
	_bigObj.AddComponent(new ObjectInfo(false));

	_airObj.GetComponent<Renderer>()->Init("air_object.bmp", 128, 72);
	_airObj.GetComponent<BoxCollider>()->SetSize(128, 72);
	_airObj.transform->SetPosition(_rockMan->transform->GetX() + 800, _rockMan->transform->GetY() - 200);
	_airObj.AddComponent(new ObjectInfo(true));

	_ground = new GameObject();
	_ground->AddComponent(new BoxCollider());
	_ground->GetComponent<BoxCollider>()->Init();
	_ground->GetComponent<BoxCollider>()->SetSize(800, 100);
	_ground->transform->SetPosition(_rockMan->transform->GetX() + 300, _rockMan->transform->GetY() + 100);
	_ground->AddComponent(new ObjectInfo(false));

	_mainCam.camera->Shake(3, 2);
	_rockMan->transform->AddChild(&_mainCam);
	_ui.uiRenderer->Resize(WINSIZEX, WINSIZEY);
	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();

}

//여기에다 연산하세요 제에발
void playGround::update()
{
	gameNode::update();
	_camShakeFrame++;
	if (_camShakeFrame == 100) {
		_mainCam.camera->ShakeOff();
	}
	if (_camShakeFrame == 200) {
		_camShakeFrame = 0;
		_mainCam.camera->Shake(6, 2); 
	}
	oldTime = curTime;
	curTime = clock();
	_rockMan->Update();
	_smallObj.Update();
	_bigObj.Update();
	_airObj.Update();
	_ground->Update();
	_mainCam.Update();
	deltaTime = curTime - oldTime;
	_alphaFrame++;
	if (_alphaFrame == 5) {
		_alphaFrame = 0;
		if (_ui.uiRenderer->alpha > 0)
			_ui.uiRenderer->SetAlpha(_ui.uiRenderer->alpha - 1);
	}
	_ui.Update();
}

//여기에다 그려라 좀! 쫌!
void playGround::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, MAPSIZEX, MAPSIZEY, WHITENESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================
	_rockMan->Render();
	_smallObj.Render();
	_bigObj.Render();
	_airObj.Render();
	_ground->Render();
	//==================================================
	//여기도 건들지마라
	TextOut(_backBuffer->getMemDC(), _mainCam.transform->GetX() - 50, _mainCam.transform->GetY() - WINSIZEY/2, debug[0], strlen(debug[0]));
	TextOut(_backBuffer->getMemDC(), WINSIZEX / 2 - 50, 30, debug[1], strlen(debug[1]));
	TextOut(_backBuffer->getMemDC(), WINSIZEX / 2 - 50, 60, debug[2], strlen(debug[1]));
	TextOut(_backBuffer->getMemDC(), WINSIZEX / 2 - 50, 90, error, strlen(error));
	_ui.Render();
	_mainCam.camera->Render(hdc);
	//this->getBackBuffer()->render(hdc, 0, 0);
}
