#include <unistd.h>

int main(int argc, char **argv) {
	int pid = fork();
	if (pid == 0) {
		execvp("./sequential_min_max", argv);
		return 1;
	}
	return 0;
}
