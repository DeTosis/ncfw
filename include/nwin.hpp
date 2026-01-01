#pragma once
#include <ncurses.h>
#include <vector>
#include <memory>
#include <cstring>
#include <string>

#include <ncont.hpp>

class TextContent;
class nterm;

struct ChildPosOptions {
	bool pos_relative = true;
};

class WndChild {
private:
	WINDOW* m_wnd = nullptr;
	std::vector<std::unique_ptr<TextContent>> m_text_contents;
	IVec2 m_pos = {};
	IVec2 m_size = {};
	int m_zindex = 0;
	IVec2 m_content_area = {};
	IVec2 m_content_origin = {};
public:
	ChildPosOptions cpo;
	WndChild(IVec2 pos, IVec2 size);
	~WndChild();

	void add_box(chtype verch = 0, chtype horch = 0) const;
	TextContent* add_text(const char* src_text);

	void refresh() const;
	void set_z_index(int index);
	int get_zindex() const { return m_zindex; };
};

class nwindow {
private:
	std::vector<std::unique_ptr<WndChild>> m_childs;
	IVec2 m_pos;
	IVec2 m_size;
	int m_zindex = 0;
	nterm* m_nt = nullptr;
public:
	nwindow(nterm* nt, IVec2 pos, IVec2 size);
	~nwindow();

	WndChild* add_child(IVec2 pos, IVec2 size, ChildPosOptions cpo = {});
	void draw_all() const;

};
