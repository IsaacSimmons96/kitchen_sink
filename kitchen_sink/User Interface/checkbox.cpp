#include "pch.h"
#include "checkbox.h"
#include "ui_object.h"
#include "..\Headers\console.h"

CHECKBOX::CHECKBOX( const std::string text , sf::Font* font, const float size /*= 30*/, const COLOUR col, const uint8_t text_size )
: BUTTON( text, size, size, font, col, text_size )
{

	m_button_rectangle.setOutlineColor( COLOUR::Black );
	m_button_rectangle.setOutlineThickness( 2 );
}

//-------------------------------------------------------------
// Draws the checkbox to the referenced window 
//-------------------------------------------------------------
void CHECKBOX::draw( sf::RenderWindow& window )
{
	if ( is_visible() )
	{
		if ( m_clicked && m_button_rectangle.getFillColor() != m_clicked_colour )
		{
			m_button_rectangle.setFillColor( m_clicked_colour );
		}

		window.draw( m_button_rectangle );
		window.draw( m_button_text );
	}
}

//-------------------------------------------------------------
// Sets the position
//-------------------------------------------------------------
void CHECKBOX::set_position( const float& x, const float& y )
{
	const auto position = sf::Vector2f( x, y );
	m_button_rectangle.setPosition( position );

	const float text_x_position = position.x + m_button_rectangle.getGlobalBounds().width + 5;
	const float text_y_position = (position.y + m_button_rectangle.getGlobalBounds().height / 2) - (m_button_text.getGlobalBounds().height / 2);
	m_button_text.setPosition( sf::Vector2f( text_x_position, text_y_position ) );
}

//-------------------------------------------------------------
// Handles what to do when clicked
//-------------------------------------------------------------
void CHECKBOX::handle_mouse_click( sf::Mouse::Button button_type, sf::RenderWindow& window )
{
	switch ( button_type )
	{
	case sf::Mouse::Button::Left:
	case sf::Mouse::Button::Middle:
		{
			const sf::Vector2i mouse_pos = sf::Mouse::getPosition( window );
			const sf::Vector2f world_mouse_pos = window.mapPixelToCoords( mouse_pos );
			m_last_mouse_position = world_mouse_pos;

			CONSOLE::print_to_console( "held" );
			m_clicked = true;
			break;
		}
	case sf::Mouse::Button::Right:
		break;
	default:
		break;
	}
}
