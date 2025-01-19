#include <unistd.h>
#include <string.h>

int main(void)
{
	char	buf[100];

	memset(buf, '\0', 100);
	if (read(0, buf, 100) == -1)
		return (1);
	if (write(1, buf, 100) == -1)
		return (1);
	return (0);
}
