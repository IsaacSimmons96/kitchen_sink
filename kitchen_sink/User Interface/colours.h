#pragma once
#include <SFML\Graphics.hpp>

typedef sf::Color COLOUR;

namespace CUSTOM_COLOUR
{
	static const COLOUR BACKGROUND( 249, 249, 231 );
	static const COLOUR SKYPE( 0, 175, 240 );
	static const COLOUR SCROLL_BUTTON_GREY( 148, 148, 148 );
	static const COLOUR SCROLL_BAR_GREY( 84, 84, 84 );
}

namespace COLOUR_UTIL
{
	static COLOUR darken_colour( COLOUR colour_in, uint8_t darken_value = 20 )
	{
		auto if_doable_darken_value = [&]( uint8_t &value_to_change )
		{
			if( value_to_change >= darken_value )
			{
				value_to_change -= darken_value;
			}
		};

		if_doable_darken_value( colour_in.r );
		if_doable_darken_value( colour_in.g );
		if_doable_darken_value( colour_in.b );

		return colour_in;
	}

	static COLOUR lighten_colour( COLOUR colour_in, uint8_t lighten_value = 20 )
	{
		auto if_doable_lighten_value = [&]( uint8_t &value_to_change )
		{
			if( (value_to_change + static_cast<uint16_t>(lighten_value)) <= 256 )
			{
				value_to_change += lighten_value;
			}
		};

		if_doable_lighten_value( colour_in.r );
		if_doable_lighten_value( colour_in.g );
		if_doable_lighten_value( colour_in.b );

		return colour_in;
	}
}