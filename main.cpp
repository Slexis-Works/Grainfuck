#include "main.hpp"

int main (int argc, char **argv) {
	std::cout << argc << " args." << std::endl;
	for (int argn = 0 ; argn < 	argc ; argn++) {
		std::cout << argv[argn] << " of size " << strlen(argv[argn]) << std::endl;
	}

	// Main vars
	sf::Sprite graphicalContent;
	sf::Texture texture;
	sf::Image buf;

	// Default configuration
	bool showHelp = false;
	int winX = 80,
		winY = 50,
		zoom = 2;
	std::string title = "Grainfuck Code";

	// Reading parameters
	for (int argn = 1 ; argn < argc ; argn++) {
		char* arg = argv[argn];
		size_t argl = strlen(arg);
		if (arg[0] == '-' && argl > 1 && arg[1] != '-') {
			// This part is a series of one-letter flags
			for (int nc = 1 ; nc < argl ; nc++) {
				std::cout << "Char " << nc << " " << arg[nc] << std::endl;
				switch (arg[nc]) {
					case 'h':
						// Show help and exit flag
						showHelp = true;
						break;
					case 'p': {
						// Define screen's size flag in pixels
						if (nc == argl - 1
							&& argn < argc - 2) {
							winX = atoi(argv[argn+1]);
							winY = atoi(argv[argn+2]);
						} else
							std::cerr << "-p requires two positive integers right after." << std::endl;
						} break;
					case 's': {
						// Define screen's size flag as a square
						if (nc == argl - 1
							&& argn < argc - 1) {
							winX = atoi(argv[argn+1]);
							winY = atoi(argv[argn+1]);
						} else
							std::cerr << "-s requires a positive integer right after." << std::endl;
						} break;
					case 'z': {
						// Define the zoom
						if (nc == argl - 1
							&& argn < argc - 1)
							zoom = atoi(argv[argn+1]);
						else
							std::cerr << "-z requires an integer between 1 and 10 right after." << std::endl;
						} break;
					case 't': {
						if (nc == argl - 1
							&& argn < argc - 1)
							title = argv[argn+1];
						else
							std::cerr << "-t requires a string right after.";
						} break;
				}
			}
		} else if (!strcmp(argv[argn], "--help"))
			showHelp = true;
	}

	if (showHelp) {
		if (system("man grainfuck")) {
			std::cerr << "Please install the complete program to get the man page." << std::endl;
			return ERR_HELP_NF;
		}
		return OMG_IT_WORKED;
	}

	if (winX < 1 || winX > 512
		|| winY < 1 || winY > 512) {
		std::cerr << "Invalid window sizes." << std::endl;
		return ERR_WIN_SIZE;
	}

	if (zoom < 1 || zoom > 10) {
		std::cerr << "Invalid zoom." << std::endl;
		return ERR_ZOOM_RANGE;
	}

	// All is ready, init
	// Create pixels buffers up to a drawable sprite
	texture.create(winX, winY);
	texture.setSmooth(false);

	buf.create(winX, winY, sf::Color::Black);

	graphicalContent.setTexture(texture);
	graphicalContent.setScale(zoom, zoom);

    sf::RenderWindow window(sf::VideoMode(winX*zoom, winY*zoom), title);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		// Buffer rendering
        window.clear();

        texture.update(buf.getPixelsPtr());
        window.draw(graphicalContent);

        window.display();
    }

    return OMG_IT_WORKED;
}
