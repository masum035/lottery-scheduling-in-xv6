#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
        if (argc < 2) exit();
	char* n_char = argv[1]; 
        int n = atoi(n_char);
	nice(n);
	exit();
}
