#ifndef POMBO_H
#define POMBO_H

#include "GameObject.h"
#include "Sprite.h"

class Pombo: public GameObject{
public:
    Pombo(float x, float y, int subLayer);
    ~Pombo();

    void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);

    void FazCaca();
private:
    Sprite pombo;
    Sprite sombra;

    bool fazendoCaca;
    bool isDead;
    float speed;
};

#endif // POMBO_H
