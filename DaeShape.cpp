#include "stdafx.h"
#include "DaeShape.h"
#include <sstream>


DaeShape::DaeShape(const Point2f & center, float width, float height, Color4f color):
	m_Center{center},
	m_Width{width},
	m_Height{height},
	m_Color{color}
{
}

DaeShape::~DaeShape()
{
}


void DaeShape::Translate(const Vector2f & tr)
{
	m_Center.x += tr.x;
	m_Center.y += tr.y;
}

std::string DaeShape::PropertiesToString()
{
	std::stringstream result;

	result << "  Center=" << '"' << std::to_string(m_Center.x) << ','<< std::to_string(m_Center.y) << '"' << "\n";
	result << "  Width=" << '"' << std::to_string(m_Width) << '"' << "\n";
	result << "  Height=" << '"' << std::to_string(m_Height) << '"' << "\n";
	result << "  Color=" << '"' << std::to_string(m_Color.r) << ',' << std::to_string(m_Color.g) << ',' 
	<< std::to_string(m_Color.b) << ',' << std::to_string(m_Color.a) << '"' << "\n";

	return result.str();
}
