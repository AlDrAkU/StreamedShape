#pragma once
#include "Vector2f.h"
#include "DaeRectangle.h"
#include "Texture.h"

class DaeRectLabel : public DaeRectangle
{
public:
	DaeRectLabel( const Point2f& center, float width, float height, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont );
	~DaeRectLabel()override;
	DaeRectLabel( const DaeRectLabel& ) = delete;
	DaeRectLabel& operator=( const DaeRectLabel& ) = delete;

	void Draw( ) const override;
	virtual std::string ToString()override;
	

private: 
	std::string m_Label;
	Color4f m_TextColor;
	Texture* m_pLabelText;
	float m_MarginX;
	float m_MarginY;
};

 
