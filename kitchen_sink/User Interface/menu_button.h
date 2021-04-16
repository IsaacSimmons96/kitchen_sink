#pragma once
#include "button.h"
#include <utility>
#include <string>
#include <vector>

//--------------------------------------------------------------------------------------------------------
// MENU_BUTTON is a button that when selected displays a dropdown menu
// The menu is filled with values from MENU_BUTTON's m_values which can be selected to
// change the currently selected value. This current value can be accessed by using get_selected_value()
//--------------------------------------------------------------------------------------------------------
class MENU_BUTTON : public BUTTON
{
	typedef BUTTON parent;

public:
	MENU_BUTTON( const float width, const float height, sf::Font* font, const COLOUR col = COLOUR::White);
	~MENU_BUTTON();

	UI_OBJECT* get_if_mouse_over(sf::RenderWindow &window)									override;

	void draw(sf::RenderWindow &window)														override;
	void handle_mouse_click(sf::Mouse::Button button_type, sf::RenderWindow& window )		override;
	void handle_mouse_release(sf::Mouse::Button button_type)								override;
	void set_font(sf::Font* font)															override;
	void cancel()																			override;

	uint32_t	get_selected_value();
	void		set_selected_index(uint32_t new_selection);
	void		set_values(const std::vector<std::pair<std::string, uint32_t>> &values, uint32_t default_value = 0);

private:
	friend class MENU_VALUE_BUTTON;

	void handle_value_selected(uint32_t selection_index);
	void update_selected_text();
	void expand_menu();
	void close_menu();
	
	sf::Font* m_font;
	bool m_menu_open{ false };

	uint32_t m_selected_index{ 0 };
	sf::RectangleShape m_menu_rectangle;
	std::vector<MENU_VALUE_BUTTON*> m_menu_buttons;
	std::vector<std::pair<std::string, uint32_t>> m_values;

	COLOUR m_menu_button_colour{ COLOUR::Black };
	COLOUR m_menu_button_hover_colour{ COLOUR::Black };
	COLOUR m_menu_button_clicked_colour{ COLOUR::Black };

	COLOUR m_selected_value_colour{ COLOUR::Black };
	COLOUR m_selected_value_hover_colour{ COLOUR::Black };
	COLOUR m_selected_value_clicked_colour{ COLOUR::Black };
};

//----------------------------------------------------------------------------------------------------------------
// MENU_VALUE_BUTTON - A class that helps the MENU_BUTTON!
// Its purpose is to contain the strings and the indexs that correspond to MENU_BUTTON's m_values vector
// When selected it sends back the value index selected for the MENU_BUTTON to deal with.
//----------------------------------------------------------------------------------------------------------------
class MENU_VALUE_BUTTON : public BUTTON
{
public:
	MENU_VALUE_BUTTON( MENU_BUTTON* parent, const std::string text, const uint32_t& selection_index, const float width, const float height, sf::Font* font, const COLOUR col );

	void handle_mouse_release( sf::Mouse::Button button_type ) override;

private:
	MENU_BUTTON* m_parent_menu_button{ nullptr };
	uint32_t m_selection_index{ 0 };
};