#include "stdafx.h"		
#include "DaeEllipse.h"
#include "utils.h"
#include <sstream>


DaeEllipse::DaeEllipse( const Point2f& center, float width, float height, const Color4f& color, bool isFilled )
	: DaeShape{ center,width,height,color }
, m_IsFilled{ isFilled }
{
}

void DaeEllipse::Draw( )const
{
	utils::SetColor( m_Color );
	if ( m_IsFilled )
	{
		utils::FillEllipse( m_Center, m_Width / 2, m_Height / 2 );
	}
	else
	{
		utils::DrawEllipse( m_Center, m_Width / 2, m_Height / 2, 2.0f );
	}
}

std::string DaeEllipse::ToString()
{
	std::stringstream result{};

	result << "<DaeEllipse";
	result << "\n";
	result << DaeShape::PropertiesToString();
	result << "  IsFilled=" << '"';
	if (m_IsFilled)
	{
		result << "true";
	}
	else
	{
		result << "false";
	}
	result << '"' << "\n";
	result << "/>" << "\n" << "\n";

	return result.str();
}

