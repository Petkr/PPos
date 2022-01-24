#pragma once
#include <cstdint>

enum class color : unsigned int
{
	black = 0,
	blue = 1,
	green = 2,
	cyan = 3,
	yellow = 14,
	white = 15,
};

class font
{
	std::uint8_t code;

public:
	font(color foreground, color background) noexcept;
};

void print_clear();
void print_char(char character);
void print_str(const char* string);
void print_set_font(font font);
