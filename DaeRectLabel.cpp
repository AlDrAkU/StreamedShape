#include "stdafx.h"		
#include "DaeRectLabel.h"
#include "utils.h"
#include <sstream>

DaeRectLabel::DaeRectLabel(const Point2f& center, float width, float height, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont)
	:DaeRectangle{ center,width,height,color },
	m_Label{ label },
	m_TextColor{ textColor }
{
	m_pLabelText = new Texture( label, pFont, textColor );
	m_MarginX = ( m_Width - m_pLabelText->GetWidth( ) ) / 2;
	m_MarginY = ( m_Height - m_pLabelText->GetHeight( ) ) / 2;
}

DaeRectLabel::~DaeRectLabel( )
{
	delete m_pLabelText;
	m_pLabelText = nullptr;
}

void DaeRectLabel::Draw( )const
{
	DaeRectangle::Draw();

	// Label
	Point2f bottomLeft{ m_Center.x - m_Width / 2 + m_MarginX, m_Center.y - m_Height / 2 + m_MarginY };
	m_pLabelText->Draw( bottomLeft );
}

std::string DaeRectLabel::ToString()
{
	std::stringstream result{};

	result << "<DaeRectLabel";
	result << "\n";
	result << DaeShape::PropertiesToString();
	result << "  Label=" << '"' + m_Label << '"' << "\n";
	result << "  TextColor=" << '"' << std::to_string(m_TextColor.r) << ',' << std::to_string(m_TextColor.g)
		<< ',' << std::to_string(m_TextColor.b) << ',' << std::to_string(m_TextColor.a) << '"' << "\n";
	result << "/>" << "\n" << "\n";

	return result.str();
}

