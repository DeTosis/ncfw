#include <ncont.hpp>

TextContent::TextContent(
		IVec2 parrent_origin, IVec2 parrent_size,
		IVec2 text_pos, IVec2 text_size, 
		const char* src_text) {
	m_parrent_origin = parrent_origin;
	m_parrent_size = parrent_size;
	m_pos = text_pos;
	m_size = text_size;
	m_wnd = newwin(m_size.y, m_size.x, m_pos.y, m_pos.x);
	m_src_text = src_text;

	draw_text();
}

TextContent::~TextContent() {
	delwin(m_wnd);
}

void TextContent::refresh() {
	wrefresh(m_wnd);
}

void TextContent::draw_text() {
	mvwaddstr(m_wnd, 0, 0, m_src_text.c_str());
}

//TODO: Alining for a multi line string
// Now it occupates full length of parrent, so second and on linse would not 
// be aligned only first one
TextContent* TextContent::format(int hor, int vert) {
	IVec2 free_space = m_parrent_size - m_size;	
	m_pos = m_parrent_origin;
	if (hor & ALIGN_CENTER) {
		m_pos.x += free_space.x / 2;
		mvwin(m_wnd, m_pos.y, m_pos.x);
	}

	if (hor & ALIGN_LEFT) {
		mvwin(m_wnd, m_pos.y, m_pos.x);
	}

	if (hor & ALIGN_RIGHT) {
		m_pos.x += free_space.x;
		mvwin(m_wnd, m_pos.y, m_pos.x);
	}

	if (vert & ALIGN_CENTER) {
		m_pos.y += free_space.y / 2;
		mvwin(m_wnd, m_pos.y, m_pos.x);
	}

	if (vert & ALIGN_TOP) {
		mvwin(m_wnd, m_pos.y, m_pos.x);
	}

	if (vert & ALIGN_BOTTOM) {
		m_pos.y += free_space.y;
		mvwin(m_wnd, m_pos.y, m_pos.x);
	}
	return this;
}
