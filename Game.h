#pragma once
#include <vector>

class  DaeShape;

class Game
{
public: 
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( );

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	Window m_Window;
	std::vector< DaeShape * > m_pShapes;

	const float m_TransPerSec{ 100.0f };
	TTF_Font *m_pFont;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( );

	void CreateLabelFont( );
	void CloseLabelFont( );
	void DeleteShapes( );
	void DrawShapes( );
	void MoveShapes( float elapsedSec );

	// Methods for reading/writing shapes from/to file
	void CreateShapesFromFile( const std::string & fileName );
	void SaveShapesToFile( const std::string & fileName ) const;

	std::string GetAttributeValue( const std::string& name, const std::string& shape ) const;

	Color4f ToColor( const std::string& color ) const;
	Point2f ToPoint2f( const std::string& point ) const;
	bool ToBool( const std::string& boolString ) const;

	void CreateShape( const std::string& shape );
	void CreateRectangle( const std::string& shape );
	void CreateRectLabel( const std::string& shape );
	void CreateEllipse( const std::string& shape );
};