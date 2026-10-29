#include "ansi_view.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace FrogToad {
	AnsiView::AnsiView() {
#ifdef _WIN32
		// UTF-8 strings contain the triangles and box-drawing characters.
		SetConsoleOutputCP(CP_UTF8);
#endif
		std::cout << resetStyles() << background() << clearScreen() << cursorHome() << hideCursor();
	}

	AnsiView::~AnsiView() {
		std::cout << resetStyles() << showCursor() << std::flush;
	}

	void AnsiView::drawBorder(const char* left, const char* separator, const char* right) {
		std::cout << grey() << left;
		for (int index{ 0 }; index < BoardModel::BoardSize; ++index) {
			if (index > 0) std::cout << separator;
			std::cout << "═══";
		}
		std::cout << right << '\n';
	}

	void AnsiView::draw(const BoardModel& model) {
		std::cout << cursorHome() << resetStyles() << background();

		std::cout << brown() << "Toads" << white() << " & " << green() << "Frogs" << eraseAfter() << "\n\n";
		std::cout << grey() << "1.." << BoardModel::BoardSize << " = Move & R = Restart\n\n";

		// Board row
		drawBorder("╔", "╦", "╗");
		for (int index{ 0 }; index < BoardModel::BoardSize; ++index) {
			std::cout << grey() << "║ ";
			switch (model.cellAt(index)) {
				case BoardModel::Cell::Frog:
					std::cout << green() << "►";
					break;
				case BoardModel::Cell::Toad:
					std::cout << brown() << "◄";
					break;
				case BoardModel::Cell::Empty:
					std::cout << ' ';
					break;
				default:
					std::cout << 'X';
					break;
			}
			std::cout << ' ';
		}
		std::cout << grey() << "║\n";
		drawBorder("╚", "╩", "╝");

		// Numbered positions
		std::cout << grey();
		for (int position = 1; position <= BoardModel::BoardSize; ++position) {
			std::cout << "  " << position << ' ';
		}
		std::cout << "\n\n";

		
		

		// Status line
		if (model.isSolved()) {
			std::cout << blue() << "Solved! R to restart.\n";
		}
		// lose statement 
		else if (model.state() == BoardModel::GameState::Lost) {
			std::cout << red() << "Lost :( Press R to restart.\n";
		}
		else {
			std::cout << white() << "Choose a piece to move.\n\n";
		}

		// Erase text left by a previous, longer frame.
		std::cout << eraseAfter() << resetStyles() << std::flush;
	}
}
