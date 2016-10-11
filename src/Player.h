#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <sstream>

#include "GameObject.h"
#include "Timer.h"
#include "Clock.h"
#include "Text.h"
#include "Sound.h"

#include "Game.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Defines.h"

/******
    Player Defines
******/
#define RUNNING_FILE        "img/playerRunning.png"
#define RUNNING_FRAMES       6
#define RUNNING_FTIME        0.09
#define RUNNING_ACC          1.5
#define RUNNING_SLOW_SPEED   4
#define RUNNING_SPEED        5


#define STOPPING_FILE    "img/derrota.png"
#define STOPPING_FRAMES  12
#define STOPPING_TIMES   1

#define SKATING_FILE    "img/playerskating.png"
#define SKATING_FRAMES  3
#define SKATING_SPEED   7
#define SKATING_TIME    5
#define SKATING_MUS     "audio/skate.ogg"

#define EATING_FILE     "img/comendoAcai.png"
#define EATING_FRAMES   6
#define EATING_SPEED
#define EATING_TIME     3

#define COFFEE_FILE     "img/coffee.png"

#define TEXT_FONT_FILE  "font/ComicNeue_Bold.otf"
#define TEXT_INIT       "Coffee: 0"


#define DELTA_ACCEPT 10

enum PowerUp{
	NONE,
	SKATE,
	DASH,
	COMIDA,
	CACA_DE_POMBO
};

enum MovementState{
    RUNNING,
    EATING,
    STOPPING
};

enum InputState{
    NO_INPUT,
    GOING_UP,
    GOING_DOWN,
    GOING_UPSTAIRS,
    GOING_DOWNSTAIRS,
};

class Player : public GameObject{
public:
	Player(float x,float y);
	virtual ~Player();

	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);
	int GetLayer();
	int GetSublayer();

    Player& GetInstance();

	bool IsTargetSpeed(float targetSpeed);
	void SetTargetSpeed(float targetSpeed);
    float GetSpeed();
	float GetAcceleration();
	void SetAcceleration(float acceleration);

	bool IsRightPosition(); // checa se ta numa posicao na qual a camera pode voltar ao normal;

	void Shoot();

	static Player* player;
	static int coffee_ammo; // caso pegue cafe, tem q aumentar isso aki
    MovementState movementState;
    InputState inputState;
    //temporario
    int GetBaseX();
	int GetX();
	bool isPlayerColliding();
	bool isInPosition();
	float GetPositionIncrement();
	void TimeOver();

private:
    Sprite sp;

    //Atributos de posi��o
	Vec2 pos;               //Posicao atual
	int baseX;              //Posicao padrao
	bool isRightPosition;   //Flag de corretude da posi��o
	float speed;            //velocidade atual
	float acceleration;     //aceleracao
	float targetSpeed;      //velocidade a alcan�ar
    float positionIncrement;//Incremento calculado para Player no eixo X

    //Atributos de PowerUp
	PowerUp powerUp;        //Possiveis estados
	Timer itemTimer;       //Cron�metro
    bool isIndestructible;  //Flag especial atribuida por um estado
    Sound powerupMusic;
	bool isPlayingMusic;

    //Atributos de Colis�o
    bool isColliding;
    bool wasColliding;
    bool isPassingMapObject;

    //Indicador de fim de tempo
    bool timeOver;
    bool playerControl;

	void SetPositionIncrement(float dt);
	void checkPosition(float diff);
	void SetSpriteScale();
	bool IsIndestructible();
	void ChangeSpriteSheet(string file, int frameCount, int times = 0);

    void PlayerStops();
    void MoveGirl();
    void MoveSameFloor();       //executa o mmovimentos principais de input
    void MoveThroughFloors();   //Confere se o player pode ou nao subir/descer escada

    void SetPositionInY();

    //retorna true se encerrar o powerup
    void EndPowerUp();

    void UpdatePowerUp(float dt);
    void CheckCollisionToResetSpeed();
    void AdjustSpeed(float dt);

    //ajusta a posi��o do Player de acordo com o tipo do movimento
    //(se ele se desloca de um lado para o outro ou de cima para baixo)
    void SetPositionToMovementState(float dt);

    //ajusta a posi��o do player quando troca de andar
    void AdjustGoingUpOrDown();

    void StopIndestructiblePowerup();
    void SetNewSpeedAndPowerup(PowerUp powerup, float newSpeed, float targetSpeed);

    //N�o deveria estar aqui
    Text hud;
	void RenderHud();
};

#endif /* PLAYER_H_ */
