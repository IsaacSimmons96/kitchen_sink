#pragma once
#include "button.h"

class CHECKBOX : public BUTTON
{
public:
	CHECKBOX( const std::string text, sf::Font* font, const float size = 24, const COLOUR col = COLOUR::White, const uint8_t text_size = 14 );

	void draw( sf::RenderWindow& window ) override;
	void handle_mouse_click( sf::Mouse::Button button_type, sf::RenderWindow& window )	override;

	void set_position( const float& x, const float& y ) override;
};

