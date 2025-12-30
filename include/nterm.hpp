#pragma once
#include <cstdint>
#include <ncurses.h>
#include <vector>
#include <memory>
#include <algorithm>

#include <nwin.hpp>

typedef uint8_t ui8t;

struct InitOptions {
	bool refresh = true;
	bool raw = true;
	bool cbreak = true;
	bool noecho = true;
	bool keypad = true;
};

class nterm {
private:
	std::vector<nwindow*> m_windows;
public:
	nterm (InitOptions io = {});
	~nterm();
	void add_window(nwindow* wnd);
	void remove_window(nwindow* wnd);

	// KEYBOARD MANAGMENT

private:
	void enable();
	void disable();
};
