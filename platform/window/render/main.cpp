#include <SDL\SDL.h>
#include "window.h"

int main(int argc, char * argv[]) {

	Window window(argc, argv);
	window.run();
	return 0;
}