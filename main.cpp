#include "main.hpp"

int main (int argc, char **argv) {
	// Main vars

	sf::RenderWindow *window;
	sf::Sprite graphicalContent;
	sf::Texture texture;
	sf::Image buf;
	bool changedPixel = false;
	float verboseSleepTime = 0.1f;

	// Default configuration
	bool showHelp(false),
		showSteps(false);
	bool paintEnabled(true);
	int winX(80),
		winY(50),
		zoom(3);
	size_t datasSize(30000);
	std::string title("Grainfuck Code");
	Buffer<char> program;
	Buffer<sf::Uint8> datas;
	std::stack<size_t> loopsStack;

	// Reading parameters
	for (int argn = 1 ; argn < argc ; argn++) {
		char* arg = argv[argn];
		size_t argl = strlen(arg);
		if (arg[0] == '-' && argl > 1 && arg[1] != '-') {
			// This part is a series of one-letter flags
			for (int nc = 1 ; nc < argl ; nc++) {
				switch (arg[nc]) {
					case 'h':
						// Show help and exit flag
						showHelp = true;
						break;
					case 'p': {
						// Define screen's size flag in pixels
						if (nc == argl - 1
							&& argn < argc - 2) {
							winX = atoi(argv[++argn]);
							winY = atoi(argv[++argn]);
						} else
							std::cerr << "-p requires two positive integers right after." << std::endl;
						} break;
					case 's': {
						// Define screen's size flag as a square
						if (nc == argl - 1
							&& argn < argc - 1) {
							winX = atoi(argv[++argn]);
							winY = atoi(argv[argn]);
						} else
							std::cerr << "-s requires a positive integer right after." << std::endl;
						} break;
					case 'z': {
						// Define the zoom
						if (nc == argl - 1
							&& argn < argc - 1)
							zoom = atoi(argv[++argn]);
						else
							std::cerr << "-z requires an integer between 1 and 10 right after." << std::endl;
						} break;
					case 'b': {
						// Define the buffer's size
						if (nc == argl - 1
							&& argn < argc - 1)
							datasSize = atoi(argv[++argn]);
						else
							std::cerr << "-b requires an integer between 1 and, well, whatever this computer can handle, right after." << std::endl;
						} break;
					case 't': {
						if (nc == argl - 1
							&& argn < argc - 1)
							title = argv[++argn];
						else
							std::cerr << "-t requires a string right after." << std::endl;
						} break;
					case 'c': {
						if (nc == argl - 1
							&& argn < argc - 1) {
							argn++;
							program.init(argv[argn], strlen(argv[argn]));
						} else
							std::cerr << "-c requires a string right after." << std::endl;
						} break;
					case 'v': {
						showSteps = true;
						} break;
					case 'n':
						winX = 0;
						winY = 0;
				}
			}
		} else if (!strcmp(argv[argn], "--help"))
			showHelp = true;
		else if (!strcmp(argv[argn], "--step"))
			showSteps = true;
	}

	if (showHelp) {
		if (system("man grainfuck")) {
			std::cerr << "Please install the complete program to get the man page." << std::endl;
			return ERR_HELP_NF;
		}
		return OMG_IT_WORKED;
	}

	if (winX == 0 || winY == 0) {
		paintEnabled = false;
	} else if (winX < 1 || winX > 256
		|| winY < 1 || winY > 256) {
		std::cerr << "Invalid window sizes." << std::endl;
		return ERR_WIN_SIZE;
	}

	if (zoom < 1 || zoom > 10) {
		std::cerr << "Invalid zoom." << std::endl;
		return ERR_ZOOM_RANGE;
	}

	if (program.getSize() < 1) {
		std::cerr << "Missing code. Execute one with `-c \"code\"` or load it with `-f file-name` or try some samples." << std::endl;
		return ERR_NO_CODE;
	}

	// All is ready, init
	// Memory buffers
	if (datasSize < 1) {
		return ERR_DATAS_SIZE;
	}
	datas.init((sf::Uint8)0, datasSize);

	if (paintEnabled) {
		// Create pixels buffers up to a drawable sprite
		texture.create(winX, winY);
		texture.setSmooth(false);

		buf.create(winX, winY, sf::Color::Black);

		graphicalContent.setTexture(texture);
		graphicalContent.setScale(zoom, zoom);

		window = new sf::RenderWindow(sf::VideoMode(winX*zoom, winY*zoom), title);
	}

    do {
		changedPixel = false;
		//std::cout << "Reading instruction `" << program.get() << "` at " << program.getPos() << "." << std::endl;
		if (showSteps) {
			std::cout << std::endl;
			for(size_t p(0) ; p < program.getSize() ; p++) {
				if (p == program.getPos() && program.getAt(p) != '\n')
					std::cout << "_";
				else
					std::cout << program.getAt(p);
			}
			std::cout << std::endl;
			for(size_t i(0) ; i < 16 ; i++) {
				if (datas.getPos() == i)
					std::cout << "*";
				else
					std::cout << " ";
				if (datas.getAt(i) < 100) {
					std::cout << " ";
					if (datas.getAt(i) < 10) {
						std::cout << " ";
					}
				}
				std::cout << (int)datas.getAt(i) << "|";
			}
			std::cout << std::endl;
			verboseSleepTime = 0.1f;
		}
		switch(program.get()) {
			case '>':
				datas.advance();
				break;
			case '<':
				datas.retreat();
				break;
			case '+':
				datas.increment();
				break;
			case '-':
				datas.decrement();
				break;
			case '.':
				std::cout << datas.get();
				break;
			case ',': {
				char inputChar;
				std::cin >> inputChar;
				datas.set(inputChar);
				} break;
			case '[':
				if (datas.get()) {
					loopsStack.push(program.getPos());
				} else {
					size_t nesting(1);
					while (nesting && program.advance()) {
						if (program.get() == '[')
							nesting++;
						else if (program.get() == ']')
							nesting--;
					}
					if (program.getPos() == 0) {
						std::cerr << "Missing `]` token." << std::endl;
					}
				}
				break;
			case ']':
				if (loopsStack.empty()) {
					std::cerr << "Missing `[` token." << std::endl;
				} else {
					program.moveTo(loopsStack.top() - 1);
					loopsStack.pop();
				}
				break;
			default:
				verboseSleepTime = 0.01f;
				// std::cerr << "Unknown instruction `" << program.get() << "`." << std::endl;
		}

		if (paintEnabled) {
			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window->close();
			}

			// Buffer rendering
			window->clear();

			buf.setPixel(3, 3, sf::Color::Green);

			texture.update(buf.getPixelsPtr());
			window->draw(graphicalContent);

			window->display();
		}
		if (showSteps)
			sf::sleep(sf::seconds(verboseSleepTime));
    } while (program.advance() || (paintEnabled && window->isOpen()));

	if (paintEnabled) {
		delete window;
	}

    return OMG_IT_WORKED;
}
