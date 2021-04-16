#include "pch.h" 
#include "ui_object.h"
#include "..\Headers\console.h"

void UI_OBJECT::set_colour( COLOUR colour_in )
{
	m_colour = colour_in;
}

void UI_OBJECT::set_hover_colour( COLOUR colour_in )
{
	m_hover_colour = colour_in;
}

void UI_OBJECT::set_secondary_colour( COLOUR colour_in )
{
	m_secondary_colour = colour_in;
}

void UI_OBJECT::set_clicked_colour( COLOUR colour_in )
{
	m_clicked_colour = colour_in;
}

void UI_OBJECT::hide()
{
	m_visible = false;
}

void UI_OBJECT::show()
{
	m_visible = true;
}

void UI_OBJECT::set_visible( bool visibility )
{
	m_visible = visibility;
}

bool UI_OBJECT::is_visible()
{
	return m_visible;
}

void UI_OBJECT::set_attachment( LAYOUT_ATTACHMENT attachment_in )
{
	m_layout_attachment = attachment_in;
	print_attachment();
}

void UI_OBJECT::clear_attachment( LAYOUT_ATTACHMENT attachment_in )
{
	m_layout_attachment = LAYOUT_ATTACHMENT::INVALID;
	print_attachment();
}

MOUSE_WHEEL_DIRECTION UI_OBJECT::get_mouse_wheel_direction( float mouse_wheel_delta ) const
{
	return mouse_wheel_delta < 0 ? MOUSE_WHEEL_DIRECTION::SCROLLING_DOWN : MOUSE_WHEEL_DIRECTION::SCROLLING_UP;
}

void UI_OBJECT::print_attachment()
{
	if( m_debug )
	{
		if( m_layout_attachment == LAYOUT_ATTACHMENT::INVALID )
		{
			CONSOLE::print_to_console( "Current UI_OBJECT has no layout attachment." );
		}
		else
		{
			CONSOLE::print_to_console( "Current UI_OBJECT layout attachment :" );
			switch( m_layout_attachment )
			{
				case LAYOUT_ATTACHMENT::IGNORE_ATTACHMENTS:
				{
					CONSOLE::print_to_console( "IGNORE_ATTACHMENTS" );
					break;
				}
				case LAYOUT_ATTACHMENT::TOP:
				{
					CONSOLE::print_to_console( "TOP" );
					break;
				}
				case LAYOUT_ATTACHMENT::TOP_LEFT:
				{
					CONSOLE::print_to_console( "TOP_LEFT" );
					break;
				}
				case LAYOUT_ATTACHMENT::TOP_RIGHT:
				{
					CONSOLE::print_to_console( "TOP_RIGHT" );
					break;
				}
				case LAYOUT_ATTACHMENT::BOTTOM:
				{
					CONSOLE::print_to_console( "BOTTOM" );
					break;
				}
				case LAYOUT_ATTACHMENT::BOTTOM_LEFT:
				{
					CONSOLE::print_to_console( "BOTTOM_LEFT" );
					break;
				}
				case LAYOUT_ATTACHMENT::BOTTOM_RIGHT:
				{
					CONSOLE::print_to_console( "BOTTOM_RIGHT" );
					break;
				}
				case LAYOUT_ATTACHMENT::LEFT:
				{
					CONSOLE::print_to_console( "LEFT" );
					break;
				}
				case LAYOUT_ATTACHMENT::RIGHT:
				{
					CONSOLE::print_to_console( "RIGHT" );
					break;
				}
				case LAYOUT_ATTACHMENT::TOP_AND_BOTTOM:
				{
					CONSOLE::print_to_console( "TOP_AND_BOTTOM" );
					break;
				}
				case LAYOUT_ATTACHMENT::LEFT_AND_RIGHT:
				{
					CONSOLE::print_to_console( "LEFT_AND_RIGHT" );
					break;
				}
				case LAYOUT_ATTACHMENT::ALL_SIDES:
				{
					CONSOLE::print_to_console( "ALL_SIDES" );
					break;
				}
				case LAYOUT_ATTACHMENT::CENTRE:
				{
					CONSOLE::print_to_console( "CENTRE" );
					break;
				}
			}
		}
	}
}

void UI_OBJECT::cancel()
{
	CONSOLE::print_to_console( "cancelled click" );
	m_clicked = false;
}