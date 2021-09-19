#include "print.hpp"

#include <cstdint>

#include "PP/size_t.hpp"

using namespace PP::literals;

constexpr inline auto NUM_COLS = 80_z;
constexpr inline auto NUM_ROWS = 25_z;

class Char
{
	std::uint8_t character;
	font f;

public:
	Char(char c, font f) noexcept
		: character(static_cast<std::uint8_t>(c))
		, f(f)
	{}
};

constinit const auto buffer = reinterpret_cast<Char*>(0xb8000);
font f(color::white, color::black);

auto col = 0_z;
auto row = 0_z;

void clear_row(PP::size_t row)
{
	for (auto col = 0_z; col != NUM_COLS; ++col)
		buffer[col + NUM_COLS * row] = {' ', f};
}

void print_clear()
{
	for (auto i = 0_z; i != NUM_ROWS; ++i)
		clear_row(i);
}

void print_newline()
{
	col = 0;

	if (row < NUM_ROWS - 1)
	{
		row++;
		return;
	}

	for (auto row = 1_z; row != NUM_ROWS; ++row)
	{
		for (auto col = 0_z; col != NUM_COLS; ++col)
		{
			auto character = buffer[col + NUM_COLS * row];
			buffer[col + NUM_COLS * (row - 1)] = character;
		}
	}

	clear_row(NUM_COLS - 1);
}

void print_char(char character)
{
	if (character == '\n')
	{
		print_newline();
		return;
	}

	if (col > NUM_COLS)
		print_newline();

	buffer[col + NUM_COLS * row] = {character, f};

	col++;
}

void print_str(const char* str)
{
	for (auto i = str; *i != '\0'; ++i)
		print_char(*i);
}

void print_set_font(font f)
{
	::f = f;
}

font::font(color foreground, color background) noexcept
	: code(static_cast<std::uint8_t>(
		  static_cast<unsigned int>(foreground) |
		  (static_cast<unsigned int>(background) << 4)))
{}
