#ifndef LIXEIRA_H
#define LIXEIRA_H

#include "GameObject.h"
#include "Obstacle.h"
#include "Sprite.h"

class Lixeira: public Obstacle{
public:
    Lixeira(int layer);
    ~Lixeira();

	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);

	int GetLayer();
	int GetSublayer();

private:
    Sprite lixeiraTop;
    Sprite lixeiraMiddle;
    Sprite lixeiraBottom;
};

#endif // LIXEIRA_H