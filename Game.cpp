#include "stdafx.h"
#include "Game.h"
#include "DaeShape.h"
#include "DaeEllipse.h"
#include "DaeRectangle.h"
#include "DaeCircle.h"
#include "DaeRectLabel.h"
#include "Vector2f.h"
#include <iostream>
#include <fstream>


Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( ); 
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	CreateLabelFont( );
	CreateShapesFromFile( "Resources/Shapes.txt" );
	
}

void Game::Cleanup( )
{
	SaveShapesToFile( "Resources/SavedShapes.txt" );
	DeleteShapes( );
	CloseLabelFont( );
}

void Game::Update( float elapsedSec )
{
	MoveShapes( elapsedSec );
}

void Game::Draw( )
{
	ClearBackground( );
	DrawShapes( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
void Game::CreateLabelFont( )
{
	m_pFont = TTF_OpenFont( "./Resources/DIN-Light.otf", 16 );
	if ( m_pFont == nullptr )
	{
		std::cerr << "Game::CreateFont, error when calling TTF_OpenFont: " << TTF_GetError( ) << std::endl;
	}
}


void Game::CloseLabelFont( )
{
	if ( m_pFont != nullptr )
	{
		TTF_CloseFont( m_pFont );
		m_pFont = nullptr;
	}
}

void Game::DeleteShapes( ) 
{
	for ( DaeShape* pShape: m_pShapes )
	{
		delete pShape;
	}
	m_pShapes.clear( );
}

void Game::DrawShapes( ) 
{
	for ( DaeShape* pShape : m_pShapes )
	{
		pShape->Draw( );
	}
}

void Game::MoveShapes( float elapsedSec )
{
	Vector2f transVec{};

	// Check keyboard
	const Uint8 *pKeyStates = SDL_GetKeyboardState( nullptr );
	if ( pKeyStates[SDL_SCANCODE_RIGHT ] )
	{
		transVec.x += m_TransPerSec * elapsedSec;
	}
	if ( pKeyStates[SDL_SCANCODE_LEFT] )
	{
		transVec.x -= m_TransPerSec * elapsedSec;
	}
	if ( pKeyStates[SDL_SCANCODE_DOWN] )
	{
		transVec.y -= m_TransPerSec * elapsedSec;
	}
	if ( pKeyStates[SDL_SCANCODE_UP] )
	{
		transVec.y += m_TransPerSec * elapsedSec;
	}

	// Move shapes
	for ( DaeShape* pShape : m_pShapes )
	{
		pShape->Translate( transVec );
	}
}

void Game::CreateShapesFromFile( const std::string& fileName )
{
	// TODO: Reads the XML shape elements from the given file
	// Calls for each read DAE shape element the function CreateShape 
	std::string input{};
	std::ifstream fileStream{ fileName };

	while (fileStream.good())
	{
		std::string temp{};
		do
		{
			std::getline(fileStream, temp);
			input += temp;
			
		} while (input.find("/>") == input.npos && fileStream.good());

		CreateShape(input);
		input.clear();
	}
	
}

void Game::SaveShapesToFile( const std::string & fileName ) const
{
	// TODO: Complete the definition of SaveShapesToFile
	// Save all the shapes in the vector m_pShapes to the given file
	// in  XML format

	std::ofstream outFileStream{ fileName };

	for (DaeShape* i : m_pShapes)
	{
		outFileStream << i->ToString();
	}
}

std::string Game::GetAttributeValue( const std::string& attrName, const std::string& element ) const
{
	// TODO: Complete GetAttributeValue function
	// It looks for the value of the given attribute (attrName) 
	// in the given element and returns it
	std::string attribute{};
	size_t index{};
	
	index = element.find(attrName + "=") + attrName.size();
	
	index = element.find('"', index);
	
	index++;

	while (element.at(index) != '"')
	{
		attribute += element.at(index);
		index++;
	} 

	return attribute;
}

Color4f Game::ToColor( const std::string& colorStr ) const
{
	// TODO: Complete the ToColor function definition
	// The parameter contains a color in the format: "r,g,b,a"
	// This function converts this color into a Color4f type and returns it
	Color4f color{};
	size_t idx{};
	size_t prevIdx{};
	std::string r, g, b, a;

	for (int i = 0; i < 4; i++)
	{
		prevIdx = idx;
		idx = colorStr.find(',', prevIdx);
		
		switch (i)
		{
		case 0:
			r = colorStr.substr(prevIdx, idx - prevIdx);
			break;
		case 1:
			g = colorStr.substr(prevIdx, idx - prevIdx);
			break;
		case 2:
			b = colorStr.substr(prevIdx, idx - prevIdx);
			break;
		case 3:
			a = colorStr.substr(prevIdx, idx - prevIdx);
			break;

		default:
			break;
		}
		idx++;
	}
	
	color = Color4f{ std::stof(r),std::stof(g),std::stof(b),std::stof(a) };

	return color;
}

Point2f Game::ToPoint2f( const std::string& point2fStr ) const
{
	// TODO: Complete the ToPoint2f function definition
	// The parameter contains a point in the format: "x,y"
	// This function converts this information into a Point2f type and returns it
	Point2f point;
	size_t idx{};
	size_t prevIdx{};
	std::string x,y;

	for (int i = 0; i < 2; i++)
	{
		prevIdx = idx;
		idx = point2fStr.find(',', prevIdx);

		switch (i)
		{
		case 0:
			x = point2fStr.substr(prevIdx, idx - prevIdx);
			break;
		case 1:
			y = point2fStr.substr(prevIdx, idx - prevIdx);
			break;

		default:
			break;
		}
		idx++;
	}

	point = Point2f{ std::stof(x),std::stof(y) };
	return point;
}

bool Game::ToBool( const std::string& boolStr ) const
{
	// TODO: Complete the ToBool function definition
	// The parameter contains a bool in text form: "true" or "false"
	// This function converts this information into a bool type and returns it
	bool result{};

	if (boolStr == "true")
	{
		result = true;
	}
	else if (boolStr == "false")
	{
		result = false;
	}

	return result;
}

void Game::CreateShape( const std::string& shapeElement )
{
	if ( shapeElement.find( "DaeRectangle" ) != std::string::npos )
	{
		CreateRectangle( shapeElement );
	}
	else if ( shapeElement.find( "DaeEllipse" ) != std::string::npos )
	{
		CreateEllipse( shapeElement );
	}
	else if ( shapeElement.find( "DaeRectLabel" ) != std::string::npos )
	{
		CreateRectLabel( shapeElement );
	}
}

void Game::CreateRectangle( const std::string& rectangleElement )
{
	Point2f center = ToPoint2f( GetAttributeValue( "Center", rectangleElement ));
	float width = std::strtof(GetAttributeValue( "Width", rectangleElement ).data(), nullptr);
	float height = std::strtof( GetAttributeValue( "Height", rectangleElement ).data(), nullptr);
	Color4f color = ToColor( GetAttributeValue( "Color", rectangleElement ));
	
	m_pShapes.push_back( new DaeRectangle( center, width, height, color ) );
}

void Game::CreateRectLabel( const std::string& rectLabelElement )
{
	Point2f center = ToPoint2f( GetAttributeValue( "Center", rectLabelElement ) );
	float width = std::strtof( GetAttributeValue( "Width", rectLabelElement ).data( ), nullptr );
	float height = std::strtof( GetAttributeValue( "Height", rectLabelElement ).data( ), nullptr );
	Color4f color = ToColor( GetAttributeValue( "Color", rectLabelElement ) );
	std::string label = GetAttributeValue( "Label", rectLabelElement );
	Color4f textColor = ToColor( GetAttributeValue( "TextColor", rectLabelElement ) );
	std::string textColorStr = GetAttributeValue( "TextColor", rectLabelElement );

	m_pShapes.push_back( new DaeRectLabel( center, width, height, color, label, textColor, m_pFont ) );
}
void Game::CreateEllipse( const std::string& ellipseElement )
{
	Point2f center = ToPoint2f( GetAttributeValue( "Center", ellipseElement ) );
	float width = std::strtof( GetAttributeValue( "Width", ellipseElement ).data( ), nullptr );
	float height = std::strtof( GetAttributeValue( "Height", ellipseElement ).data( ), nullptr );
	Color4f color = ToColor( GetAttributeValue( "Color", ellipseElement ) );
	bool isFilled = ToBool( GetAttributeValue( "IsFilled", ellipseElement ) );
	
	m_pShapes.push_back( new DaeEllipse( center, width, height, color, isFilled ));
}
