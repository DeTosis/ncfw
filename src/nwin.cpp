#include <nwin.hpp>

#include <ncont.hpp>
#include <nterm.hpp>

//
// *** NWINDOW
//

nwindow::nwindow(nterm* nt, IVec2 pos, IVec2 size) {
	m_pos = pos;
	m_size = size;
	m_nt = nt;

	m_nt->add_window(this);
}

nwindow::~nwindow() {
	m_nt->remove_window(this);
}

WndChild* nwindow::add_child(IVec2 pos, IVec2 size, ChildPosOptions cpo) {
	if (cpo.pos_relative && (size.x > m_size.x || size.y > m_size.y)) {
		return nullptr;
	}

	IVec2 fpos = cpo.pos_relative ? m_pos + pos : pos;

	auto child = std::make_unique<WndChild>(fpos, size);
	child->cpo = cpo;

	m_childs.push_back(std::move(child));
	return m_childs.back().get();
}

void nwindow::draw_all() const {
	std::vector<WndChild*> temp;
	for (auto& it : m_childs) temp.push_back(it.get());

	std::sort(temp.begin(), temp.end(), 
			[](WndChild* a, WndChild* b) {
				return a->get_zindex() < b->get_zindex();
			});

	for (const auto& it : temp) {
		it->refresh();
	}
}

//
// *** WNDCHILD
//

WndChild::WndChild(IVec2 pos, IVec2 size) {
	m_pos = pos;
	m_size = size;

	m_content_area = m_size - IVec2{2,2,};
	m_content_origin = m_pos + IVec2{1, 1};

	m_wnd = newwin(size.y, size.x, pos.y, pos.x);
}

void WndChild::add_box(chtype verch, chtype horch) const {
	box(m_wnd, verch, horch);
}

void WndChild::refresh() const {
	wrefresh(m_wnd);
	for (const auto& it : m_text_contents) {
		it->refresh();
	}
}

void WndChild::set_z_index(int index) {
	m_zindex = index;
}

TextContent* WndChild::add_text(const char* src_text) {
	
	int lines = 1 + strlen(src_text) / m_content_area.x;
	int cols = strlen(src_text) > m_content_area.x ? m_content_area.x : strlen(src_text); 

	IVec2 text_size = {cols, lines};

	auto txt = std::make_unique<TextContent>(
			m_content_origin, m_content_area,
			m_content_origin, text_size,
			src_text);
	m_text_contents.push_back(std::move(txt));
	return m_text_contents.back().get();
}
