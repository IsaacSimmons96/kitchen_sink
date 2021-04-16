#pragma once
#include "box.h"
#include "button.h"

//-------------------------------------------------------------------------------------------
// A child of BOX that can move its view contents using the scroll wheel
//-------------------------------------------------------------------------------------------
class SCROLLING_BOX : public BOX
{
	typedef BOX parent;

public:
	SCROLLING_BOX( float x_pos, float y_pos, float width, float height, sf::RenderWindow& window, const COLOUR bg_col = CUSTOM_COLOUR::BACKGROUND );


	void handle_drag_scroll( MOUSE_DRAG_DIRECTION direction, int16_t scrolled_value );
	void handle_mouse_scroll( float mouse_wheel_direction )	override;
	void draw( sf::RenderWindow &window )					override;
	UI_OBJECT* get_if_mouse_over( sf::RenderWindow &window ) override;


private:
	friend class SCROLL_BUTTON;
	SCROLL_BUTTON* m_scroll_button{ nullptr };
	
	uint16_t m_scroll_value{ 0 };
	uint16_t m_max_scroll_value{ 0 };
};

//----------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------
class SCROLL_BUTTON : public BUTTON
{
public:
	SCROLL_BUTTON( SCROLLING_BOX* parent, const float height, const COLOUR col );
	void handle_mouse_drag( sf::RenderWindow& window ) override;

private:
	SCROLLING_BOX* m_parent_menu_button{ nullptr };
};

