#include "pch.h" 
#include <algorithm>
#include <cmath>
#include "scrolling_box.h"
#include "button.h"
#include "..\Headers\console.h"

constexpr uint16_t SCROLL_INCEREMENT_VALUE{ 15 };

#pragma region SCROLL_BUTTON

//------------------------------------------------------------------------------
// MENU_VALUE_BUTTON Constructor
//------------------------------------------------------------------------------
SCROLL_BUTTON::SCROLL_BUTTON( SCROLLING_BOX* parent, const float height, const COLOUR col )
	: BUTTON( 20.0f, height, col )
{
	m_can_drag = true;
	m_parent_menu_button = parent;
	m_hover_colour = COLOUR_UTIL::darken_colour( m_colour, 15 );
	m_clicked_colour = COLOUR_UTIL::darken_colour( m_hover_colour, 25 );
}

void SCROLL_BUTTON::handle_mouse_drag( sf::RenderWindow & window )
{
	if( m_can_drag && m_clicked )
	{
		if( is_mouse_over( window ) )
		{
			const sf::Vector2f world_mouse_pos = window.mapPixelToCoords( sf::Mouse::getPosition( window ) );

			if( world_mouse_pos != m_last_mouse_position )
			{
				const int16_t y_pos_difference = static_cast<int16_t>( world_mouse_pos.y ) - static_cast<int16_t>( m_last_mouse_position.y );
				m_last_mouse_position = world_mouse_pos;

				if( m_parent_menu_button )
				{
					m_parent_menu_button->handle_drag_scroll( y_pos_difference > 0 ? MOUSE_DRAG_DIRECTION::DRAGGING_DOWN : MOUSE_DRAG_DIRECTION::DRAGGING_UP, y_pos_difference );
				}
			}
		}
		else
		{
			cancel();
		}
	}
}
#pragma endregion SCROLL_BUTTON


SCROLLING_BOX::SCROLLING_BOX( float x_pos, float y_pos, float width, float height, sf::RenderWindow& window, const COLOUR bg_col /*= CUSTOM_COLOUR::BACKGROUND*/ )
	: BOX( x_pos, y_pos, width, height, window, bg_col )
{
	m_max_scroll_value = 3000 - SCROLL_INCEREMENT_VALUE;
}

void SCROLLING_BOX::handle_drag_scroll( MOUSE_DRAG_DIRECTION direction, int16_t scrolled_value )
{
	uint8_t multiplier = std::round((m_max_scroll_value + SCROLL_INCEREMENT_VALUE) / m_box_height);
	int16_t scaled_scrolled_value = m_box_height - m_max_scroll_value <= 0 ? scrolled_value * multiplier : scrolled_value;
	switch( direction )
	{
		case MOUSE_DRAG_DIRECTION::DRAGGING_DOWN:
		{
			if( m_scroll_value < m_box_height - SCROLL_INCEREMENT_VALUE )
			{
				const auto new_to_scroll_value = std::clamp( m_scroll_value + scrolled_value, 0, static_cast<int>(m_box_height - SCROLL_INCEREMENT_VALUE) );
				m_view_box->move( 0, scaled_scrolled_value );
				m_viewport_scroll_value += scaled_scrolled_value;
				m_scroll_value = new_to_scroll_value;				
			}
			break;
		}

		case MOUSE_DRAG_DIRECTION::DRAGGING_UP:
		{
			if( m_scroll_value > 0 )
			{
				const auto new_to_scroll_value = std::clamp( m_scroll_value - std::abs( scrolled_value ), 0, static_cast<int>( m_max_scroll_value ) );
				m_view_box->move( 0.0f, (float)-std::abs( scaled_scrolled_value ) );
				m_viewport_scroll_value -= scaled_scrolled_value;
				m_scroll_value = new_to_scroll_value;
			}
			break;			
		}
	}

	CONSOLE::print_to_console( "m_viewport_scroll_value :" + std::to_string( m_viewport_scroll_value ) );

	if( m_scroll_button )
	{
		m_scroll_button->set_position( m_box_width + m_box_x_pos, m_box_y_pos + m_scroll_value );
	}
}

void SCROLLING_BOX::handle_mouse_scroll( float mouse_wheel_direction )
{
	if( m_debug )
	{
		CONSOLE::print_to_console( "Mouse wheel direction :" + std::to_string( mouse_wheel_direction ) );
	}

	switch( get_mouse_wheel_direction( mouse_wheel_direction ) )
	{
		case  MOUSE_WHEEL_DIRECTION::SCROLLING_DOWN:
		{
			if( m_scroll_value < m_max_scroll_value )
			{
				const auto new_to_scroll_value = std::clamp( m_scroll_value + SCROLL_INCEREMENT_VALUE, 0, static_cast<int>( m_max_scroll_value ) );
				m_view_box->move( 0, SCROLL_INCEREMENT_VALUE );
				m_scroll_value = new_to_scroll_value;
			}
			break;
		}
		case  MOUSE_WHEEL_DIRECTION::SCROLLING_UP:
		{
			if( m_scroll_value > 0 )
			{
				const auto new_to_scroll_value = std::clamp( m_scroll_value - SCROLL_INCEREMENT_VALUE, 0, static_cast<int>( m_max_scroll_value ) );
				m_view_box->move( 0, -SCROLL_INCEREMENT_VALUE );
				m_scroll_value = new_to_scroll_value;
			}
			break;
		}
	}

	if( m_scroll_button )
	{
		m_scroll_button->set_position( m_box_width + m_box_x_pos, m_box_y_pos + m_scroll_value );
	}
}

void SCROLLING_BOX::draw( sf::RenderWindow & window )
{
	parent::draw( window );

	const float view_box_size_x = m_view_box->getSize().x;
	const float view_box_size_y = m_view_box->getSize().y;


	sf::RectangleShape scroll_bar;
	scroll_bar.setSize( sf::Vector2f( 20.0f, m_box_height ) );
	scroll_bar.setFillColor( CUSTOM_COLOUR::SCROLL_BAR_GREY );
	scroll_bar.setPosition( sf::Vector2f( m_box_width + m_box_x_pos, m_box_y_pos ) );

	if( !m_scroll_button )
	{
		const auto scroll_bar_button_height = m_box_height - m_max_scroll_value <= 0 ? SCROLL_INCEREMENT_VALUE : m_box_height - m_max_scroll_value;
		m_scroll_button = new SCROLL_BUTTON( this, scroll_bar_button_height, CUSTOM_COLOUR::SCROLL_BUTTON_GREY );
		m_scroll_button->set_position( m_box_width + m_box_x_pos, m_box_y_pos + m_scroll_value );
	}

	window.draw( scroll_bar );
	m_scroll_button->draw( window );
}

UI_OBJECT * SCROLLING_BOX::get_if_mouse_over( sf::RenderWindow & window )
{
	if( m_scroll_button && m_scroll_button->get_if_mouse_over( window ) )
	{
		return m_scroll_button;
	}
	else
	{
		return parent::get_if_mouse_over( window );
	}
}
