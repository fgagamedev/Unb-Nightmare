#include "Game.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Text.h"
#include <cstdlib>
#include <sstream>

#include "Bullet.h"

#include "Defines.h"

Player* Player::player = nullptr;
int Player::coffee_ammo = 0;


Player::Player(float x, float y) : sp("img/playerRunning.png", 6, 0.09){
	subLayer = SUBLAYER_MIDDLE;
	layer = LAYER_MIDDLE;
	box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	targetSpeed = speed = PLAYER_NORMAL_SPEED;
	acceleration = 1.5;
	isRightPosition = false;
	powerUp = NONE;
	movementState = RUNNING;
    isColliding = false;
    wasColliding = false;
    isPassingMapObject = false;
	hud = Text("font/arial.ttf", 28, SOLID, "Coffee: 0", TEXT_WHITE, 40,50);

	player = this;

    coffee_ammo = 60;
	std::cout << "Player Construido" << std::endl;

}

Player::~Player() {
	player = nullptr;
}


float Player::GetSpeed(){
	return speed;
}

void Player::Update(float dt){
//	clock.Update(dt);
	sp.Update(dt);
	Movement(); // faz os movimentos do input

	//colocando na posicao certa o player
	if(box.x - Camera::pos.x > PLAYER_DISTANCE_TO_CAMERA)
		isRightPosition = true;
	else
		isRightPosition = false;

    if(!isColliding){
        if(wasColliding){
            speed = PLAYER_NORMAL_SPEED;
            SetTargetSpeed(PLAYER_NORMAL_SPEED);
            wasColliding = false;
        }
    }

	//ir acelerando at� a velocidade
	if(!IsTargetSpeed(targetSpeed)){
		if(targetSpeed > speed)
			speed = speed + acceleration*dt;
		if(targetSpeed < speed)
			speed = speed - acceleration*dt;
		if(targetSpeed == 0){
			speed = 0;
			std::cout << " entrou aki no targer speed" << std::endl;
		}
	}

	//correndo
	if(movementState == MovementState::RUNNING)
        box.x = box.x + speed*dt*100;

    if(movementState == MovementState::GOING_DOWN)
        box.y = box.y + speed*dt*150;

    if(movementState == MovementState::GOING_UP)
        box.y = box.y - speed*dt*150;


	//cafe

	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		Shoot();
	}
	isColliding=false;


    if(movementState != RUNNING){
        if(layer == LAYER_TOP && abs(box.y - ITEM_HEIGHT_L3) < 10){							//
            this->movementState = RUNNING;
            box.y = ITEM_HEIGHT_L3 - (this->subLayer - 3)*26;
        }
        if(layer == LAYER_MIDDLE && abs(box.y - ITEM_HEIGHT_L2) < 10){
            this->movementState = RUNNING;
            box.y = ITEM_HEIGHT_L2 - (this->subLayer - 3)*26;
        }
        if(layer == LAYER_BOTTON && abs(box.y - ITEM_HEIGHT_L1) < 10){
            this->movementState = RUNNING;
            box.y = ITEM_HEIGHT_L1 - (this->subLayer - 3)*26;
        }

    }


    isPassingMapObject = false;
}

void Player::Render(){
	sp.Render((int)(box.x - Camera::pos.x), (int)(box.y - Camera::pos.y));
	this->RenderHud();
    if(subLayer == 3)
    	sp.SetScale(0.95);
    if(subLayer == 2)
        sp.SetScale(1);
    if(subLayer == 1)
        sp.SetScale(1.05);

}
bool Player::IsDead(){
	// camera passou player
	if(Camera::pos.x > pos.x + sp.GetWidth()){
		player = nullptr;
		cout<<"TESTE"<<endl;
		return true;
	}
	return false; // retornar true se tiver camera passou, ou se o tempo acabou
	//isso pode ser feito pelo state data.

}
bool Player::Is(std::string type){
	return (type == "Player");

}

bool Player::IsTargetSpeed(float targetSpeed){
	if(targetSpeed <=0) // se algo a levar para tras
		speed = targetSpeed;
	if(abs(speed - targetSpeed) <= 0.005)
		return true;
	return false;
}

float Player::GetAcceleration(){
	return acceleration;
}
void Player::SetAcceleration(float acceleration){
	this->acceleration = acceleration;
}

bool Player::IsRightPosition(){
	return isRightPosition;
}

void Player::Movement(){
	pos = box.CenterPos();

	if(subLayer > 3)
		subLayer = 3;
	if(subLayer < 1)
		subLayer = 1;

	if(InputManager::GetInstance().KeyPress(SDLK_w)){
		std::cout << "DEBUG\n" << std::endl;
		std::cout << "-------------PLayer---------------------"  << std::endl;
		std::cout << "Layer: " << layer  << std::endl;
		std::cout << "suLayer: " << subLayer << std::endl;
		std::cout << "camera: "<< Camera::pos.x <<std::endl;
		std::cout << "player: "<<pos.x + sp.GetWidth() <<std::endl;
	}

	if(InputManager::GetInstance().KeyPress(SDLK_l))
		targetSpeed = 7.5;
	// exemplo de diminuir velocidade
	if(InputManager::GetInstance().KeyPress(SDLK_j))
		targetSpeed =4.5;
	// exemplo de velocidade voltou ao normal
	if(InputManager::GetInstance().KeyPress(SDLK_k))
		targetSpeed =5;


	//movimento de sublayer
	if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		if(subLayer <=2)
			subLayer++;

	}
	if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		if(subLayer >=2)
			subLayer--;
	}
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;						//
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////



//
	if(subLayer == SUBLAYER_TOP){
		if(layer == LAYER_MIDDLE || layer == LAYER_BOTTON)
			if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && isPassingMapObject){
				layer++;
				subLayer = SUBLAYER_TOP;
				movementState = GOING_UP;
			}
		if(layer == LAYER_TOP|| layer == LAYER_MIDDLE)
			if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && isPassingMapObject){
				layer--;
				subLayer = SUBLAYER_TOP;
				movementState = GOING_DOWN;
		}
	}

}

void Player::Shoot(){
	Vec2 shootPos = box.CenterPos();
	if(coffee_ammo>0){
		Bullet* coffee = new Bullet(shootPos.x,shootPos.y,10,"img/coffee.png", 3, 0.3,false, "Coffee");
		coffee->SetLayers(layer,subLayer); // para renderizar corretamente
		Game::GetInstance().GetCurrentState().AddObject(coffee);

		coffee_ammo--;
	}
}

void Player::RenderHud(){
    //QUANDO ARRUMAR VAZAMENTO DE MEMORIA, DESCOMENTAR ISSO AKI
    std::stringstream hudString;
    hudString << "Coffee: " << coffee_ammo;
   // cout << "hud " << hudString.str() << endl;

//	std::string hudString = "Coffee: " + to_string(coffee_ammo);
	hud.SetText(hudString.str());
	hud.Render(0,0);

}

void Player::SetTargetSpeed(float targetSpeed){
    this->targetSpeed = targetSpeed;
}

void Player::NotifyCollision(GameObject* other){
    //cout<< "collision with obstacle1" << endl;
    if(other->Is("gordinha") || other->Is("lixeira")){
        this->isColliding = true;
        this->wasColliding = true;
        this->SetTargetSpeed(0.0);
    }
    if(other->Is("manifestacao")){
        this->isColliding = true;
        this->wasColliding = true;
        this->speed = 2;
        // se ficar apertando vai mais rapido
        if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY))
        	box.x = box.x + 20;
    }

    if(other->Is("COFFEE")){
        coffee_ammo++;
    }
    if(other->Is("SKATE")){
        this->SetTargetSpeed(7.5);
    }

    if(other->Is("Escada")){
        this->isPassingMapObject = true;
    }
}

