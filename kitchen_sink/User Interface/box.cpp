#include "pch.h" 
#include "box.h"
#include "..\Headers\console.h"

//-------------------------------------------------------------
// BOX Constructor
//-------------------------------------------------------------
BOX::BOX( float x_pos, float y_pos, float width, float height, sf::RenderWindow& window, const COLOUR bg_col /*= CUSTOM_COLOUR::BACKGROUND*/ )
{
	m_colour = bg_col;

	m_box_x_pos = x_pos;
	m_box_y_pos = y_pos;
	m_box_width = width;
	m_box_height = height;
	m_parent_window = &window;

	m_view_box = new sf::View( sf::FloatRect( 0.f, 0.f, m_box_width, m_box_height ) );

	const float view_port_x_position = convert_to_0_to_1_scale( m_box_x_pos, m_parent_window->getSize().x );
	const float view_port_y_position = convert_to_0_to_1_scale( m_box_y_pos, m_parent_window->getSize().y );
	const float view_port_width = convert_to_0_to_1_scale( m_box_width, m_parent_window->getSize().x );
	const float view_port_height = convert_to_0_to_1_scale( m_box_height, m_parent_window->getSize().y );
	m_view_box->setViewport( sf::FloatRect( view_port_x_position, view_port_y_position, view_port_width, view_port_height ) );

	m_background_rect.setPosition( 0, 0 );
	m_background_rect.setSize( sf::Vector2f( m_box_width, m_box_height ) );
	m_background_rect.setFillColor( m_colour );
}

//-----------------------------------------------------------------------------------------
// BOX Destructor
//-----------------------------------------------------------------------------------------
BOX::~BOX()
{
	for( auto object : m_embedded_objects )
	{
		delete object;
	}

	m_embedded_objects.clear();
}

//--------------------------------------------------------------------------------
// Returns the correct embedded object if the mouse is over it
//--------------------------------------------------------------------------------
UI_OBJECT* BOX::get_if_mouse_over( sf::RenderWindow & window )
{
	UI_OBJECT* mouse_over = nullptr;

	if( m_view_box )
	{
		const float button_max_width = m_box_x_pos + m_box_width;
		const float button_max_height = m_box_y_pos + m_box_height;
		const sf::Vector2i mouse_pos = sf::Mouse::getPosition( window );
		const sf::Vector2f world_mouse_pos = window.mapPixelToCoords( mouse_pos );

		const bool is_mouse_over_box = world_mouse_pos.x > m_box_x_pos && world_mouse_pos.x < button_max_width && world_mouse_pos.y > m_box_y_pos && world_mouse_pos.y < button_max_height;
		if( is_mouse_over_box )
		{
			window.setView( *m_view_box );
			for( auto object : m_embedded_objects )
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

			if( mouse_over == nullptr )
			{
				mouse_over = this;
			}

			window.setView( window.getDefaultView() );
		}
	}

	return mouse_over;
}

//-----------------------------------------------------------------------------------------
// Draws the BOX to the referenced window along with its embedded UI_OBJECTS
//-----------------------------------------------------------------------------------------
void BOX::draw( sf::RenderWindow & window )
{
	if( is_visible() && m_view_box )
	{
		window.setView( *m_view_box );
		window.draw( m_background_rect );

		for( auto object : m_embedded_objects )
		{
			if( object )
			{
				object->draw( window );
			}
		}

		window.setView( window.getDefaultView() );

		if( m_debug )
		{
			const float view_box_size_x = m_view_box->getSize().x;
			const float view_box_size_y = m_view_box->getSize().y;

			sf::RectangleShape top_outline;
			top_outline.setSize( sf::Vector2f( m_box_width, m_debug_line_thickness ) );
			top_outline.setFillColor( COLOUR::Red );
			top_outline.setPosition( sf::Vector2f( m_box_x_pos, m_box_y_pos ) );

			sf::RectangleShape left_outline;
			left_outline.setSize( sf::Vector2f( m_debug_line_thickness, m_box_height ) );
			left_outline.setFillColor( COLOUR::Red );
			left_outline.setPosition( sf::Vector2f( m_box_x_pos, m_box_y_pos ) );

			sf::RectangleShape right_outline;
			right_outline.setSize( sf::Vector2f( m_debug_line_thickness, m_box_height ) );
			right_outline.setFillColor( COLOUR::Red );
			right_outline.setPosition( sf::Vector2f( m_box_width + m_box_x_pos - m_debug_line_thickness, m_box_y_pos ) );

			sf::RectangleShape bottom_outline;
			bottom_outline.setSize( sf::Vector2f( m_box_width, m_debug_line_thickness ) );
			bottom_outline.setFillColor( COLOUR::Red );
			bottom_outline.setPosition( sf::Vector2f( m_box_x_pos, m_box_height + m_box_y_pos - m_debug_line_thickness ) );

			window.draw( top_outline );
			window.draw( left_outline );
			window.draw( right_outline );
			window.draw( bottom_outline );
		}


	}
}

//-------------------------------------------------------------
// Sets the position of the BOX
//-------------------------------------------------------------
void BOX::set_position( const float & x, const float & y )
{
	m_box_x_pos = x;
	m_box_y_pos = y;

	const float view_port_x_position = convert_to_0_to_1_scale( m_box_x_pos, m_parent_window->getSize().x );
	const float view_port_y_position = convert_to_0_to_1_scale( m_box_y_pos, m_parent_window->getSize().y );
	const float view_port_width = convert_to_0_to_1_scale( m_box_width, m_parent_window->getSize().x );
	const float view_port_height = convert_to_0_to_1_scale( m_box_height, m_parent_window->getSize().y );
	m_view_box->setViewport( sf::FloatRect( view_port_x_position, view_port_y_position, view_port_width, view_port_height ) );
}

//-------------------------------------------------------------
// Sets the background colour of the BOX
//-------------------------------------------------------------
void BOX::set_colour( COLOUR colour_in )
{
	m_colour = colour_in;
	m_background_rect.setFillColor( m_colour );
}

//-------------------------------------------------------------
// Returns the centre point of the BOX width
//-------------------------------------------------------------
float BOX::get_centre_x() const
{
	return m_box_width / 2;
}

//-------------------------------------------------------------
// Returns the centre point of the BOX height
//-------------------------------------------------------------
float BOX::get_centre_y() const
{
	return m_box_height / 2;
}

//-------------------------------------------------------------
// Returns the width of the BOX
//-------------------------------------------------------------
float BOX::get_width() const
{
	return m_box_width;
}

//-------------------------------------------------------------
// Returns the height of the BOX
//-------------------------------------------------------------
float BOX::get_height() const
{
	return m_box_height;
}

//-------------------------------------------------------------
// 
//-------------------------------------------------------------
void BOX::reposition_embedded_object( UI_OBJECT * object )
{
	if( object )
	{
		const auto object_attachment = object->get_attachment();
		switch( object_attachment )
		{
			case LAYOUT_ATTACHMENT::IGNORE_ATTACHMENTS:
			case LAYOUT_ATTACHMENT::INVALID:
			{
				break;
			}
			case LAYOUT_ATTACHMENT::TOP:
			{
				object->set_position( ( ( m_box_width / 2 ) - object->get_centre_x() ) + object->get_x_offset(), 0 + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::TOP_LEFT:
			{
				object->set_position( 0 + object->get_x_offset(), 0 + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::TOP_RIGHT:
			{
				object->set_position( ( m_box_width - object->get_width() ) + object->get_x_offset(), 0 + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::BOTTOM:
			{
				object->set_position( ( ( m_box_width / 2 ) - object->get_centre_x() ) + object->get_x_offset(), ( m_box_height - object->get_height() ) + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::BOTTOM_LEFT:
			{
				object->set_position( 0 + object->get_x_offset(), ( m_box_height - object->get_height() ) + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::BOTTOM_RIGHT:
			{
				object->set_position( ( m_box_width - object->get_width() ) + object->get_x_offset(), ( m_box_height - object->get_height() ) + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::LEFT:
			{
				object->set_position( 0 + object->get_x_offset(), ( ( m_box_height / 2 ) - object->get_centre_y() ) + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::RIGHT:
			{
				object->set_position( ( m_box_width - object->get_width() ) + object->get_x_offset(), ( ( m_box_height / 2 ) - object->get_centre_y() ) + object->get_y_offset() );
				break;
			}
			case LAYOUT_ATTACHMENT::TOP_AND_BOTTOM:
			{
				CONSOLE::print_to_console( "LAYOUT_ATTACHMENT::TOP_AND_BOTTOM NOT IMPLEMENTED YET" );
				break;
			}
			case LAYOUT_ATTACHMENT::LEFT_AND_RIGHT:
			{
				CONSOLE::print_to_console( "LAYOUT_ATTACHMENT::LEFT_AND_RIGHT NOT IMPLEMENTED YET" );
				break;
			}
			case LAYOUT_ATTACHMENT::ALL_SIDES:
			{
				CONSOLE::print_to_console( "LAYOUT_ATTACHMENT::ALL_SIDES NOT IMPLEMENTED YET" );
				break;
			}
			case LAYOUT_ATTACHMENT::CENTRE:
			{
				object->set_position( ( ( m_box_width / 2 ) - object->get_centre_x() ) + object->get_x_offset(), ( ( m_box_height / 2 ) - object->get_centre_y() ) + object->get_y_offset() );
				break;
			}
		}
	}
}

//-------------------------------------------------------------
// 
//-------------------------------------------------------------
void BOX::position_object_and_embed( UI_OBJECT * object )
{
	if( object )
	{
		if( dynamic_cast<BOX*>( object ) )
		{
			CONSOLE::print_to_console( "EMBEDDED BOXES NOT SUPPORTED YET" );
		}

		m_embedded_objects.push_back( object );
		reposition_embedded_object( object );
	}
}

//-------------------------------------------------------------
// 
//-------------------------------------------------------------
float BOX::convert_to_0_to_1_scale( float input, unsigned int window_size )
{
	return input / window_size;
}

//-------------------------------------------------------------
float BOX::get_x_position() const
{
	return m_box_x_pos;
}

//-------------------------------------------------------------
float BOX::get_y_position() const
{
	return m_box_y_pos;
}

//-------------------------------------------------------------
// Adds a UI_OBJECT to the embedded objects list
//-------------------------------------------------------------
void BOX::embed_object( UI_OBJECT * object )
{
	if( object )
	{
		position_object_and_embed( object );
	}
}

//--------------------------------------------------------------------------------------------------------------
// Adds a UI_OBJECT to the embedded objects list whilst adding offsets to the object
//--------------------------------------------------------------------------------------------------------------
void BOX::embed_object( UI_OBJECT * object, const float &x_offset, const float &y_offset )
{
	if( object )
	{
		object->set_offsets( x_offset, y_offset );
		position_object_and_embed( object );
	}
}

//--------------------------------------------------------------------------------------------------------------
// Adds a UI_OBJECT to the embedded objects list whilst adding a layout attachment and offsets to the object
//--------------------------------------------------------------------------------------------------------------
void BOX::embed_object( UI_OBJECT * object, LAYOUT_ATTACHMENT attachment, const float &x_offset, const float &y_offset )
{
	if( object )
	{
		object->set_attachment( attachment );
		object->set_offsets( x_offset, y_offset );
		position_object_and_embed( object );
	}
}

//----------------------------------------------------------------------------------------------------
// Adds a UI_OBJECT to the embedded objects list whilst adding a layout attachment to the object
//----------------------------------------------------------------------------------------------------
void BOX::embed_object( UI_OBJECT * object, LAYOUT_ATTACHMENT attachment )
{
	if( object )
	{
		object->set_attachment( attachment );
		position_object_and_embed( object );
	}
}