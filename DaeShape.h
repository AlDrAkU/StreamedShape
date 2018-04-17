#pragma once
#include "Vector2f.h"
class DaeShape
{
public:
	DaeShape(const Point2f &center, float width,float height, Color4f color);
	virtual ~DaeShape();
	void Translate(const Vector2f& tr);
	virtual void Draw() const =0 ;
	virtual std::string ToString() = 0;
	std::string PropertiesToString();
protected:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Color4f m_Color;
};
