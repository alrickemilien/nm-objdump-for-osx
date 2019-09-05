#include <unistd.h>

static const char *HELLO = "Hello\n";

void print_hello()
{
	write(1, HELLO, sizeof(HELLO));
}

int	main(int ac, char **av)
{
	print_hello();
	return (0);
}
