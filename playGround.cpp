#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{

}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init();
	_camShakeFrame = 0;
	_mainCam.transform->SetX(_mainCam.transform->GetX() + 100);
	testParticle = new image();
	testParticle->init("full_charge_hit_effect_left.bmp", 240, 88, 4, 1, true, RGB(255, 0, 255));
	testParticle2 = new image();
	testParticle2->init("trap_blast_projectile.bmp", 168, 50, 4, 1, true, RGB(255, 0, 255));

	particleObj.AddComponent(new ParticleSystem(testParticle, 5, 5));
	demoParticleSys = particleObj.GetComponent<ParticleSystem>();
	demoParticleSys->SetPosition(WINSIZEX / 2, WINSIZEY / 2);
	demoParticleSys->SetInterval(1000);
	demoParticleSys->SetDuration(150);
	demoParticleSys->SetSpeed(0);
	demoParticleSys->SetLoop(true);

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

	//_mainCam.camera->Shake(3, 2);
	_ui.uiRenderer->Resize(WINSIZEX, WINSIZEY);
	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();

}

//���⿡�� �����ϼ��� ������
void playGround::update()
{
	gameNode::update();
	changeParticleTime++;
	if (changeParticleTime == 300) {
		demoParticleSys->SetParticleImage(testParticle2);
	}
	//_camShakeFrame++;
	//if (_camShakeFrame == 100) {
	//	_mainCam.camera->ShakeOff();
	//}
	//if (_camShakeFrame == 200) {
	//	_camShakeFrame = 0;
	//	_mainCam.camera->Shake(6, 2); 
	//}
	oldTime = curTime;
	curTime = clock();
	_rockMan->Update();
	_smallObj.Update();
	_bigObj.Update();
	_airObj.Update();
	_ground->Update();
	_mainCam.Update();
	demoParticleSys->Update();
	deltaTime = curTime - oldTime;
	//_alphaFrame++;
	//if (_alphaFrame == 5) {
	//	_alphaFrame = 0;
	//	if (_ui.uiRenderer->alpha > 0)
	//		_ui.uiRenderer->SetAlpha(_ui.uiRenderer->alpha - 1);
	//}
	//_ui.Update();
}

//���⿡�� �׷��� ��! ��!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, MAPSIZEX, MAPSIZEY, WHITENESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================
	_rockMan->Render();
	_smallObj.Render();
	_bigObj.Render();
	_airObj.Render();
	_ground->Render();
	demoParticleSys->Render();

	//==================================================
	//���⵵ �ǵ�������
	TextOut(_backBuffer->getMemDC(), _mainCam.transform->GetX() - 50, _mainCam.transform->GetY() - WINSIZEY/2, debug[0], strlen(debug[0]));
	TextOut(_backBuffer->getMemDC(), WINSIZEX / 2 - 50, 30, debug[1], strlen(debug[1]));
	TextOut(_backBuffer->getMemDC(), WINSIZEX / 2 - 50, 60, debug[2], strlen(debug[1]));
	TextOut(_backBuffer->getMemDC(), WINSIZEX / 2 - 50, 90, error, strlen(error));
	//_ui.Render();
	_mainCam.camera->Render(_hdc);
	//this->getBackBuffer()->render(hdc, 0, 0);
}
