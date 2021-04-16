#pragma once
#include "colours.h"
#include "ui_flags.h"

enum class MOUSE_WHEEL_DIRECTION : uint8_t
{
	SCROLLING_UP,
	SCROLLING_DOWN
};

enum class MOUSE_DRAG_DIRECTION : uint8_t
{
	DRAGGING_UP,
	DRAGGING_DOWN
};

//-------------------------------------------------------------------------------------------
// UI_OBJECT is the base class for all ui classes in this program!
// The idea being that all basic user interface functionality should be defined here!
//-------------------------------------------------------------------------------------------
class UI_OBJECT
{
public:
	virtual UI_OBJECT*	get_if_mouse_over( sf::RenderWindow &window ) = 0;
	virtual void		draw( sf::RenderWindow &window ) = 0;

	//POSITION
	virtual void	set_position( const float &x, const float &y ) = 0;
	virtual float	get_x_position() const = 0;
	virtual float	get_y_position() const = 0;

	virtual float	get_x_offset() const { return m_x_offset; };
	virtual float	get_y_offset() const { return m_y_offset; };

	virtual void	set_offsets( const float &x_off, const float &y_off )
	{
		m_x_offset = x_off;
		m_y_offset = y_off;
	};

	virtual float	get_centre_x() const = 0;
	virtual float	get_centre_y() const = 0;
	virtual float	get_width() const = 0;
	virtual float	get_height() const = 0;

	virtual	bool	has_attachment( LAYOUT_ATTACHMENT attachment_to_find )
	{
		return m_layout_attachment == attachment_to_find;
	}

	virtual	LAYOUT_ATTACHMENT get_attachment() { return m_layout_attachment; };
	virtual void	set_attachment( LAYOUT_ATTACHMENT attachment_in );
	virtual void	clear_attachment( LAYOUT_ATTACHMENT attachment_in );	

	//VISIBILITY
	virtual void	hide();
	virtual void	show();
	virtual void	set_visible( bool visibility );
	virtual bool	is_visible();

	//MOUSE
	virtual void	cancel();
	virtual bool	is_being_clicked() { return m_clicked; };
	bool			is_awaiting_action() { return m_needs_action; };

	virtual void	handle_mouse_click( sf::Mouse::Button button_type, sf::RenderWindow& window ) {};
	virtual void	handle_mouse_release( sf::Mouse::Button button_type ) {};
	virtual void	handle_mouse_drag( sf::RenderWindow & window )  {};
	virtual void	handle_mouse_enter() {};
	virtual void	handle_mouse_leave() {};
	virtual void	handle_mouse_scroll( float mouse_wheel_direction ) {};

	virtual void	set_can_drag( bool can_drag_in ) { m_can_drag = can_drag_in;  };
	bool			can_drag() { return m_can_drag; };

	//COLOURS
	virtual void	set_colour( COLOUR colour_in );
	virtual void	set_hover_colour( COLOUR colour_in );
	virtual void	set_secondary_colour( COLOUR colour_in );
	virtual void	set_clicked_colour( COLOUR colour_in );

	COLOUR get_colour() const { return m_colour; };
	COLOUR get_hover_colour() const { return m_hover_colour; };
	COLOUR get_clicked_colour() const { return m_clicked_colour; };
	COLOUR get_secondary_colour() const { return m_secondary_colour; };

	//DEBUG
	virtual void	set_debug( bool value ) { m_debug = value; };

protected:
	bool m_clicked{ false };
	bool m_can_drag{ false };
	bool m_needs_action{ false };
	bool m_debug{ false };

	COLOUR m_colour = COLOUR::White;
	COLOUR m_hover_colour = COLOUR( 169, 169, 169 );
	COLOUR m_clicked_colour = COLOUR( 105, 105, 105 );
	COLOUR m_secondary_colour = COLOUR::Black;

	MOUSE_WHEEL_DIRECTION get_mouse_wheel_direction( float mouse_wheel_delta ) const;

private:
	LAYOUT_ATTACHMENT m_layout_attachment{ LAYOUT_ATTACHMENT::INVALID };

	float m_y_offset{ 0.0 };
	float m_x_offset{ 0.0 };

	void print_attachment();

	bool m_visible{ true };
};

