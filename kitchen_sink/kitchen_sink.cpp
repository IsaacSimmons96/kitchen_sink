#include "pch.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <windows.h>
#include "..\..\User Interface\menu_button.h"
#include "..\..\User Interface\scrolling_box.h"
#include "..\..\User Interface\checkbox.h"

//------------------------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------------------------
constexpr auto APPLICATION_WINDOW_TITLE = "Kitchen Sink GUI";
constexpr auto FONT_FILE_LOCATION = "../kitchen_sink/User Interface/Fonts/8-BIT WONDER.ttf";

//------------------------------------------------------------------------------------------------
void draw_ui_objects( sf::RenderWindow& window, std::list<UI_OBJECT*>& ui_objects )
{
	for ( const auto object : ui_objects )
	{
		object->draw( window );
	}
}

//------------------------------------------------------------------------------------------------
// Handles all of the mouse events
//------------------------------------------------------------------------------------------------
void handle_mouse_events( sf::Event& event, sf::RenderWindow& window, std::list<UI_OBJECT*>& ui_objects, UI_OBJECT*& old_mouse_over, UI_OBJECT*& action_object )
{
	auto get_mouse_over = [&]()
	{
		UI_OBJECT* mouse_over_object = nullptr;

		for ( const auto object : ui_objects )
		{
			UI_OBJECT* found = object->get_if_mouse_over( window );
			if ( found && found->is_visible() )
			{
				mouse_over_object = found;
				break;
			}
		}

		return mouse_over_object;
	};

	auto new_mouse_over = get_mouse_over();
	switch ( event.type )
	{
	case sf::Event::MouseMoved:
		{
			// Have we been holding the mouse object? If so then we need to try and drag it
			if ( new_mouse_over == old_mouse_over && old_mouse_over && old_mouse_over->can_drag() )
			{
				old_mouse_over->handle_mouse_drag( window );
			}
			else if ( new_mouse_over != old_mouse_over )
			{
				if ( new_mouse_over )
				{
					new_mouse_over->handle_mouse_enter();
				}

				if ( old_mouse_over )
				{
					// Have we been holding the old mouse object? If so then we cancel the click
					if ( old_mouse_over->is_being_clicked() )
					{
						old_mouse_over->cancel();
					}

					old_mouse_over->handle_mouse_leave();
				}
			}
			break;
		}
	case sf::Event::MouseButtonPressed:
		{
			if ( new_mouse_over )
			{
				new_mouse_over->handle_mouse_click( event.mouseButton.button, window );
			}
			break;
		}
	case sf::Event::MouseButtonReleased:
		{
			if ( action_object )
			{
				if ( new_mouse_over != action_object && action_object->is_awaiting_action() )
				{
					action_object->cancel();
				}

				action_object = nullptr;
			}

			if ( new_mouse_over )
			{
				new_mouse_over->handle_mouse_release( event.mouseButton.button );
				if ( new_mouse_over->is_awaiting_action() )
				{
					action_object = new_mouse_over;
				}
			}
			break;
		}

	case sf::Event::MouseWheelScrolled:
		{
			if ( new_mouse_over )
			{
				new_mouse_over->handle_mouse_scroll( event.mouseWheelScroll.delta );
			}
			break;
		}
	default:
		break;
	}

	old_mouse_over = new_mouse_over;
}

//------------------------------------------------------------------------------------------------
// The execution of this program begins and ends inside the main function
//------------------------------------------------------------------------------------------------
int main()
{
	std::list<UI_OBJECT*> ui_objects;
	UI_OBJECT* current_mouse_over = nullptr;
	UI_OBJECT* object_needing_action = nullptr;

	sf::Font* font = new sf::Font();
	font->loadFromFile( FONT_FILE_LOCATION );

	sf::RenderWindow window( sf::VideoMode( 1080, 720 ), APPLICATION_WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar );

	/*BUTTON* drag_button = new BUTTON( "Drag Button", 200, 200, font, COLOUR::Yellow );
	drag_button->set_position( static_cast<float>(window.getSize().x / 2) - drag_button->get_centre_x(), 50 );
	drag_button->set_can_drag( true );
	ui_objects.push_back( drag_button );*/

	//SCROLLING_BOX* test_box = new SCROLLING_BOX( 100, 200, 800, 400, window );
	//test_box->set_debug( true );

	//BUTTON* test_button3 = new BUTTON( "Button 3", 150, 80, font, COLOUR::Cyan );
	//test_box->embed_object( test_button3, LAYOUT_ATTACHMENT::TOP_LEFT, 100, 0 );

	//BUTTON* test_button4 = new BUTTON( "Button 4", 150, 80, font, COLOUR::Cyan );
	//test_box->embed_object( test_button4, LAYOUT_ATTACHMENT::TOP_LEFT, 500, 600 );

	/*MENU_BUTTON* menu_button = new MENU_BUTTON( 150, 80, font, CUSTOM_COLOUR::SKYPE );
	menu_button->set_font( font );

	std::vector<std::pair<std::string, uint32_t>> race_list;
	for( uint8_t race_value = 0; race_value != static_cast<uint8_t>( RACE::END_OF_RACES ); ++race_value )
	{
		race_list.push_back( std::make_pair( PERSON::get_racial_string( static_cast<RACE>( race_value ) ), race_value ) );
	}
	menu_button->set_values( race_list );*/

	//test_box->embed_object( menu_button, LAYOUT_ATTACHMENT::CENTRE, -200, 0 );

	//ui_objects.push_back( test_box );

	CHECKBOX* check = new CHECKBOX( "Check Box", font );
	check->set_position( static_cast<float>(window.getSize().x / 2) - check->get_centre_x(), 50 );
	ui_objects.push_back( check );

	int mouseDelta = 0;
	while ( window.isOpen() )
	{
		sf::Event event;
		while ( window.pollEvent( event ) )
		{
			// check the type of the event...
			switch ( event.type )
			{
			case sf::Event::MouseMoved:
			case sf::Event::MouseButtonReleased:
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseWheelScrolled:
				{
					handle_mouse_events( event, window, ui_objects, current_mouse_over, object_needing_action );
					break;
				}

			case sf::Event::Closed:
				{
					window.close();
					break;
				}

			case sf::Event::KeyPressed:
				{
					if ( event.key.code == sf::Keyboard::Escape )
					{
						window.close();
					}
					break;
				}
			}
		}

		window.clear( CUSTOM_COLOUR::BACKGROUND );
		draw_ui_objects( window, ui_objects );
		window.display();
	}

	//TODO Isaac - finish button UI class make it into a abstract class when ive got more specific buttons setup
	//TODO Isaac - figure out a system to get the UI_OBJECT on the highest layer when using UI_OBJECT::get_if_mouse_over()
	//TODO Isaac - make panel UI class
	//TODO Isaac - make scrolling box UI class - IN PROGRESS
	//TODO Isaac - make text box UI class
	//TODO Isaac - make class called page that holds all the SFML ui and can draw everything inside it with one function - panel class

	return 0;
}