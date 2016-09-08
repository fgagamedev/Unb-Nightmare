#ifndef MANIFESTACAO_H
#define MANIFESTACAO_H

#include "Obstacle.h"

class Manifestacao: public Obstacle{
public:
    Manifestacao();
    ~Manifestacao();

    void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	int GetLayer();
    int GetSublayer();

    // 1 = subsolo , 2 = terreo , 3 = mesaniggno
	int layer;
	 // 0 = nao colide com nada, 1 = baixo, 2 = meio ,3 = topo, 4 = todos
	int subLayer;

private:
    Sprite bloco1;
    Sprite bloco2;
    Sprite bloco3;
};

#endif // MANIFESTACAO_H