#include "pch.h"
#include "menu_button.h"
#include "colours.h"
#include "..\Headers\console.h"

//-------------------------------------------------------------
// Constants
//-------------------------------------------------------------
constexpr float		MENU_VALUE_BUTTON_HEIGHT = 40;
constexpr uint8_t	MENU_VALUE_BUTTON_FONT_SIZE = 14;

#pragma region MENU_VALUE_BUTTON

//------------------------------------------------------------------------------
// MENU_VALUE_BUTTON Constructor
//------------------------------------------------------------------------------
MENU_VALUE_BUTTON::MENU_VALUE_BUTTON( MENU_BUTTON* parent, const std::string text, const uint32_t &selection_index, const float width, const float height, sf::Font* font, const COLOUR col )
	: m_parent_menu_button{ parent }, m_selection_index{ selection_index }, BUTTON( text, width, height, font, col, MENU_VALUE_BUTTON_FONT_SIZE )
{}

//------------------------------------------------------------------------------
// Handles what to do when the mouse is released on the MENU_VALUE_BUTTON
//------------------------------------------------------------------------------
void MENU_VALUE_BUTTON::handle_mouse_release( sf::Mouse::Button button_type )
{
	switch( button_type )
	{
		case sf::Mouse::Left:
		case sf::Mouse::Middle:
		{
			BUTTON::handle_mouse_release( button_type );
			if( m_parent_menu_button )
			{
				m_parent_menu_button->handle_value_selected( m_selection_index );
			}
			break;
		}
		default:
			break;
	}
}
#pragma endregion MENU_VALUE_BUTTON

//-----------------------------------------------------------------------------------------
// MENU_BUTTON Constructor
//-----------------------------------------------------------------------------------------
MENU_BUTTON::MENU_BUTTON( const float width, const float height, sf::Font* font, const COLOUR col )
	: BUTTON( "Menu Button", width, height, font, col )
{}

//-----------------------------------------------------------------------------------------
// MENU_BUTTON Destructor
//-----------------------------------------------------------------------------------------
MENU_BUTTON::~MENU_BUTTON()
{
	for( auto object : m_menu_buttons )
	{
		delete object;
	}

	m_menu_buttons.clear();
}

//-----------------------------------------------------------------------------------------
// Draws the menu button to the referenced window along with its dropdown menu UI_OBJECTS
//-----------------------------------------------------------------------------------------
void MENU_BUTTON::draw( sf::RenderWindow &window )
{
	parent::draw( window );

	if( m_needs_action && is_visible() )
	{
		window.draw( m_menu_rectangle );

		for( auto object : m_menu_buttons )
		{
			if( object )
			{
				object->draw( window );
			}
		}
	}
}

//--------------------------------------------------------------------------------
// Returns this if the mouse is over the button 
//--------------------------------------------------------------------------------
UI_OBJECT* MENU_BUTTON::get_if_mouse_over( sf::RenderWindow& window )
{
	UI_OBJECT* mouse_over = parent::get_if_mouse_over( window );

	//TODO Isaac - make it so we only search through our menu objects if we are in the bounds of the menu rectangle AND make this support view embedding
	if( !mouse_over )
	{
		for( auto object : m_menu_buttons )
		{
			if( object )
			{
				mouse_over = object->get_if_mouse_over( window );

				if( mouse_over )
				{
					break;
				}
			}
		}
	}

	return mouse_over;
}

//-------------------------------------------------------------
// Handles what to do when clicked
//-------------------------------------------------------------
void MENU_BUTTON::handle_mouse_click( sf::Mouse::Button button_type, sf::RenderWindow& window )
{
	switch( button_type )
	{
		case sf::Mouse::Left:
		case sf::Mouse::Middle:
		{
			CONSOLE::print_to_console( "menu button held" );
			m_clicked = true;
			break;
		}
		case sf::Mouse::Right:
			break;
		default:
			break;
	}
}

//-------------------------------------------------------------
// Handles what to do when the mouse is released
//-------------------------------------------------------------
void MENU_BUTTON::handle_mouse_release( sf::Mouse::Button button_type )
{
	switch( button_type )
	{
		case sf::Mouse::Left:
		case sf::Mouse::Middle:
		{
			CONSOLE::print_to_console( "menu button click" );
			m_button_rectangle.setFillColor( m_hover_colour );

			if( !m_needs_action )
			{
				expand_menu();
			}
			else
			{
				close_menu();
			}
			m_clicked = false;
			break;
		}
		case sf::Mouse::Right:
			break;
		default:
			break;
	}
}

//---------------------------------------------------------------------------------------
// Sets the font to be used in the parent and for the MENU_VALUE_BUTTON children later
//---------------------------------------------------------------------------------------
void MENU_BUTTON::set_font( sf::Font* font )
{
	parent::set_font( font );
	m_font = font;
}

//--------------------------------------------------------------------------------
// Cancels the MENU_BUTTON which closes its menu and sets it to not being clicked
//--------------------------------------------------------------------------------
void MENU_BUTTON::cancel()
{
	CONSOLE::print_to_console( "cancelled menu button" );
	m_clicked = false;

	close_menu();
}

//--------------------------------------------------------------------------------
// Handles a value being selected from the dropdown menu.
//--------------------------------------------------------------------------------
void MENU_BUTTON::handle_value_selected( uint32_t selection_index )
{
	if( m_values.size() > 0 && selection_index <= m_values.size() - 1 )
	{
		set_selected_index( selection_index );
	}

	close_menu();
}

//--------------------------------------------------------------------------------
// Updates the text of the currently selected item from the menu
//--------------------------------------------------------------------------------
void MENU_BUTTON::update_selected_text()
{
	if( m_values.size() > 0 )
	{
		m_button_text.setString( m_values[m_selected_index].first );

		const sf::Vector2f button_position = m_button_rectangle.getPosition();
		const float text_x_position = (button_position.x + m_button_rectangle.getGlobalBounds().width / 2) - (m_button_text.getGlobalBounds().width / 2);
		const float text_y_position = (button_position.y + m_button_rectangle.getGlobalBounds().height / 2) - (m_button_text.getGlobalBounds().height / 2);
		m_button_text.setPosition( sf::Vector2f( text_x_position, text_y_position ) );
	}
}

//--------------------------------------------------------------------------------
// Expands the dropdown menu
//--------------------------------------------------------------------------------
void MENU_BUTTON::expand_menu()
{
	const sf::Vector2f button_position = m_button_rectangle.getPosition();
	m_menu_rectangle.setPosition( button_position.x, button_position.y + m_button_rectangle.getGlobalBounds().height );
	m_menu_rectangle.setSize( sf::Vector2f( m_button_rectangle.getSize().x, MENU_VALUE_BUTTON_HEIGHT * m_values.size() ) );
	m_menu_rectangle.setFillColor( m_colour );

	if( m_menu_buttons.size() == 0 )
	{
		m_selected_value_colour = m_clicked_colour;
		m_menu_button_colour = COLOUR_UTIL::lighten_colour( m_colour );

		uint32_t value_index = 0;
		for( auto value : m_values )
		{
			MENU_VALUE_BUTTON* value_button = nullptr;

			if( value_index == m_selected_index )
			{
				value_button = new MENU_VALUE_BUTTON( this, value.first, value_index, m_button_rectangle.getSize().x, MENU_VALUE_BUTTON_HEIGHT, m_font, m_clicked_colour );

				if( m_selected_value_clicked_colour == COLOUR::Black && value_button )
				{
					m_selected_value_clicked_colour = value_button->get_clicked_colour();
					m_selected_value_hover_colour = value_button->get_hover_colour();
				}
			}
			else
			{
				value_button = new MENU_VALUE_BUTTON( this, value.first, value_index, m_button_rectangle.getSize().x, MENU_VALUE_BUTTON_HEIGHT, m_font, m_menu_button_colour );

				if( m_menu_button_clicked_colour == COLOUR::Black && value_button )
				{
					m_menu_button_clicked_colour = value_button->get_clicked_colour();
					m_menu_button_hover_colour = value_button->get_hover_colour();
				}
			}

			if( value_button )
			{
				value_button->set_position( button_position.x, (button_position.y + m_button_rectangle.getGlobalBounds().height) + (MENU_VALUE_BUTTON_HEIGHT * value_index) );

				m_menu_buttons.push_back( value_button );
			}

			++value_index;
		}
	}
	else
	{
		uint32_t value_index = 0;
		for( auto button : m_menu_buttons )
		{
			if( value_index == m_selected_index )
			{
				button->set_colour( m_selected_value_colour );
				button->set_hover_colour( m_selected_value_hover_colour );
				button->set_clicked_colour( m_selected_value_clicked_colour );
			}
			else
			{
				button->set_colour( m_menu_button_colour );
				button->set_hover_colour( m_menu_button_hover_colour );
				button->set_clicked_colour( m_menu_button_clicked_colour );
			}

			button->show();

			++value_index;
		}
	}



	m_needs_action = true;
}

//--------------------------------------------------------------------------------
// Closes the dropdown menu
//--------------------------------------------------------------------------------
void MENU_BUTTON::close_menu()
{
	m_needs_action = false;

	for( auto object : m_menu_buttons )
	{
		object->handle_mouse_leave();
		object->hide();
	}
}

//--------------------------------------------------------------------------------
// Sets the values to be held and displayed by the dropdown menu
//--------------------------------------------------------------------------------
void MENU_BUTTON::set_values( const std::vector<std::pair<std::string, uint32_t>>& values, uint32_t default_value /*= 0*/ )
{
	//if we are setting new values for this and we already has existing values, we'll need to dispose of the objects we had!
	if( m_menu_buttons.size() > 0 )
	{
		for( auto object : m_menu_buttons )
		{
			delete object;
		}

		m_menu_buttons.clear();
	}

	m_values = values;

	//Because size returns the number contained we want to do -1 because it doesnt count from 0
	if( default_value <= m_values.size() - 1 )
	{
		set_selected_index( default_value );
	}
	else
	{
		CONSOLE::print_to_console( "default value parameter exceeds size of vector of values! Setting it to 0" );
		set_selected_index( 0 );
	}
}

//--------------------------------------------------------------------------------
// Gets the currently selected value
//--------------------------------------------------------------------------------
uint32_t MENU_BUTTON::get_selected_value()
{
	if( m_values.size() > 0 )
	{
		return m_values[m_selected_index].second;
	}
	else
	{
		return 0;
	}
}

//--------------------------------------------------------------------------------
// Sets the current selected index thus changing the value selected
//--------------------------------------------------------------------------------
void MENU_BUTTON::set_selected_index( uint32_t new_selection )
{
	if( new_selection < m_values.size() )
	{
		m_selected_index = new_selection;
		update_selected_text();
	}
	else
	{
		CONSOLE::print_to_console( "default value parameter exceeds size of vector of values! Setting it to 0" );
		m_selected_index = 0;
	}
}