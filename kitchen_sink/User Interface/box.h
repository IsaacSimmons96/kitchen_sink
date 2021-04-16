#pragma once
#include "ui_object.h"

//-------------------------------------------------------------------------------------------
// A UI_OBJECT used for containing other UI_OBJECTS
//-------------------------------------------------------------------------------------------
class BOX : public UI_OBJECT
{
public:
	BOX( float x_pos, float y_pos, float width, float height, sf::RenderWindow& window, const COLOUR bg_col = CUSTOM_COLOUR::BACKGROUND );
	~BOX();

	UI_OBJECT* get_if_mouse_over( sf::RenderWindow &window ) override;

	void embed_object( UI_OBJECT * object );
	void embed_object( UI_OBJECT * object, const float &x_offset, const float &y_offset );
	void embed_object( UI_OBJECT * object, LAYOUT_ATTACHMENT attachment, const float &x_offset, const float &y_offset );
	void embed_object( UI_OBJECT * object, LAYOUT_ATTACHMENT attachment );

	void draw( sf::RenderWindow &window )	override;
	void set_position( const float &x, const float &y ) override;
	void set_colour( COLOUR colour_in ) override;

	float get_centre_x()	const override;
	float get_centre_y()	const override;
	float get_width()		const override;
	float get_height()		const override;
	float get_x_position()	const override;
	float get_y_position()	const override;
	sf::View* get_view()	const { return m_view_box; };

protected:
	sf::View*				m_view_box{ nullptr };

	void reposition_embedded_object( UI_OBJECT * object );
	void position_object_and_embed( UI_OBJECT* object );

	float convert_to_0_to_1_scale( float input, unsigned int window_size );

	sf::RenderWindow*		m_parent_window{ nullptr };
	std::vector<UI_OBJECT*> m_embedded_objects;
	sf::RectangleShape		m_background_rect;

	float m_box_x_pos{ 0 };
	float m_box_y_pos{ 0 };
	float m_box_width{ 0 };
	float m_box_height{ 0 };
	const float m_debug_line_thickness = 2.5f;
};

