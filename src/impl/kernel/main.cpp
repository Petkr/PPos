#include "print.hpp"

extern "C" void kernel_main()
{
	print_clear();
	print_set_font({color::yellow, color::black});
	print_str("Welcome to our 64-bit kernel!\n\n");
	print_str("Dzivotka\n");
}
