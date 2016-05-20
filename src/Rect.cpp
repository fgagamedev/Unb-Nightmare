/*
 * Rect.cpp
 *
 *  Created on: 16 de mar de 2016
 *      Author: Caio
 */

#include "Rect.h"
#include <iostream>
//**************************************************************//
//Fun��o: Rect::CenterPos()************************************//
//Retorno: Vec2***********************************************//
//Parametros:  void *****************************************//
//Descri��o: Pega um rect e retorna o centro em um Vec2 ****//
//*********************************************************//
Vec2 Rect::CenterPos(){
		Vec2 centro(x+w/2.0, y+h/2.0);
		return centro;
}
Vec2 Rect::GetCenter() const{

	return Vec2(x + w/2.0, y + h/2.0);
}
//**************************************************************//
//Fun��o: Rect::Print()************************************//
//Retorno: void***********************************************//
//Parametros:  void *****************************************//
//Descri��o: Da um print no box ****//
//*********************************************************//
void Rect::Print(){
		std::cout << std::endl << "(X,Y)(" << x << ", " << y << ")" << std::endl;
		std::cout << "   ________" << w << "________" << std::endl;
		std::cout << "   |\n   |\n   |\n " << h << "\n   |\n   |\n" << std::endl;
}

//**********************************************************************//
//Fun��o: Rect::IsInside()*********************************************//
//Retorno: bool*******************************************************//
//Parametros:  float x , float y*************************************//
//Descri��o: Verifica se a posi�ao de entrada esta dentro do rect **//
//*****************************************************************//
bool Rect::IsInside(float xx, float yy){
	if(xx < x || yy < y)
		return false;
	if(xx > x + w || yy > y + h)
		return false;
	return true;
}

//**********************************************************************//
//Fun��o: Rect::Distance(Rect rect1, Rect rect2************************//
//Retorno: float******************************************************//
//Parametros:  Rect rect1, Rect rect2********************************//
//Descri��o: retorna distancia entre dois centros*******************//
//*****************************************************************//
float Rect::Distance(Rect rect1, Rect rect2){
	Vec2 center1 = rect1.CenterPos();
	Vec2 center2 = rect2.CenterPos();
	return std::abs(center1.Magnitude() - center2.Magnitude());
}



//**********************************************************************//
//Fun��o: CONSTRUTOR***************************************************//
//Retorno: N/A********************************************************//
//Parametros(overload): int x,int y,int w,int h**********************//
//Descri��o: constroi o rect ***************************************//
//*****************************************************************//
Rect::Rect() {
	x = y = w = h = 0;
}
Rect::Rect(float xx, float yy, int ww, int hh){
	x = xx;
	y = yy;
	w = ww;
	h = hh;
}

void Rect::Centralize(float x, float y, float w, float h){
	this->x = x - w/2;
	this->y = y - h/2;
	this->w = w;
	this->h = h;
}

//**********************************************************************//
//Fun��o: DESTRUTOR****************************************************//
//Retorno: N/A********************************************************//
//Parametros: N/A****************************************************//
//Descri��o: destroi o rect ****************************************//
//*****************************************************************//

Rect::~Rect() {
}

// Operadores
Rect& Rect::operator=(const Vec2& vetor){
	x = vetor.x;
	y = vetor.y;
	return *this;
}
Rect Rect::operator+(const Vec2& vetor){
	return Rect(this->x + vetor.x, this->y + vetor.y, this->w, this->h);
}
Rect Rect::operator-(const Vec2& vetor){
	return Rect(x - vetor.x, y - vetor.y, w, h);
}
Rect Rect::operator*(const Vec2& vetor) {
	return Rect(x * vetor.x, y * vetor.y, w, h);
}
Rect Rect::operator/(const Vec2& vetor){
	return Rect(x / vetor.x, y / vetor.y, w, h);
}
