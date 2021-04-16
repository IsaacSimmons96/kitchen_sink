#pragma once
#include <math.h>
#include <string.h>
#include "ui_object.h"

//-------------------------------------------------------------------------------------------
// BUTTON is a class of the most basic button
//-------------------------------------------------------------------------------------------
class BUTTON : public UI_OBJECT
{
public:
	BUTTON(const std::string text, const float width, const float height, sf::Font* font, const COLOUR col = COLOUR::White, uint8_t text_size = 14);
	BUTTON(const float width, const float height, const COLOUR col = COLOUR::White );

	UI_OBJECT* get_if_mouse_over(sf::RenderWindow &window)		override;

	void draw(sf::RenderWindow &window)													override;
	void handle_mouse_click(sf::Mouse::Button button_type, sf::RenderWindow& window )	override;
	void handle_mouse_release(sf::Mouse::Button button_type)							override;
	void handle_mouse_drag( sf::RenderWindow & window )									override;
	void handle_mouse_enter()															override;	
	void handle_mouse_leave()															override;		

	virtual void set_font(sf::Font* font);

	void set_position(const float &x, const float &y) override;
	float get_x_position() const override;
	float get_y_position() const override;


	void set_colour(COLOUR colour_in) override;
	void set_secondary_colour(COLOUR colour_in) override;

	float get_centre_x()	const override;
	float get_centre_y()	const override;
	float get_width()		const override;
	float get_height()		const override;

protected:
	bool is_mouse_over( sf::RenderWindow & window ) const;

	sf::Text m_button_text;
	sf::RectangleShape m_button_rectangle;
	sf::Vector2f m_last_mouse_position;


};

