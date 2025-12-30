#include <nterm.hpp>

nterm::nterm(InitOptions io) {
	if (io.raw) { raw(); }
	if (io.cbreak) { cbreak(); }
	if (io.noecho){ 
		noecho(); 
	} else {
		echo();
	}
	if (io.keypad) { keypad(stdscr, TRUE); }

	enable();
}

nterm::~nterm() {
	disable();
}

void nterm::enable() {
	initscr();
}

void nterm::disable() {
	endwin();
}

void nterm::add_window(nwindow* wnd) {
	m_windows.push_back(wnd);
}

void nterm::remove_window(nwindow* wnd) {
	auto it = std::find(m_windows.begin(), m_windows.end(), wnd);
	if (it != m_windows.end()) {
		m_windows.erase(it);
	}
}
