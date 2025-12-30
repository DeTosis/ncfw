#pragma once
#include <ncurses.h>
#include <string>

#include <ntypes.hpp>

#define ALIGN_CENTER 0x01

#define ALIGN_LEFT 0x02
#define ALIGN_RIGHT 0x04

#define ALIGN_TOP 0x08
#define ALIGN_BOTTOM 0x10

class TextContent {
private:
	WINDOW* m_wnd = nullptr;
	IVec2 m_pos = {};
	IVec2 m_size = {};
	IVec2 m_parrent_size = {};
	IVec2 m_parrent_origin = {};
	std::string m_src_text = "";
public:
	TextContent(
			IVec2 parrent_origin, IVec2 parrent_size,
			IVec2 text_pos, IVec2 text_size, 
			const char* src_text);
	void refresh();
	TextContent* format(int hor, int vert);
	void format(IVec2 pos);
private:
	void draw_text();
};
