#include <iostream>
#include <ncfw.hpp>

int main (int argc, char *argv[]) {
	{
	nterm nt;
	nwindow nw(&nt, {2,2}, {COLS - 4, LINES - 4});

	auto a = nw.add_child({4,4}, {20,20});
	a->add_box();
	a->add_text("So")->format(ALIGN_LEFT, ALIGN_TOP);
	a->add_text("now")->format(ALIGN_CENTER, ALIGN_TOP);
	a->add_text("we")->format(ALIGN_RIGHT, ALIGN_TOP);
	a->add_text("have")->format(ALIGN_LEFT, ALIGN_CENTER);
	a->add_text("some")->format(ALIGN_RIGHT, ALIGN_CENTER);
	a->add_text("fancy")->format(ALIGN_LEFT, ALIGN_BOTTOM);
	a->add_text("alignment")->format(ALIGN_RIGHT, ALIGN_BOTTOM);
	a->set_z_index(-1);
	
	auto b = nw.add_child({10, 10}, {30, 10});
	b->add_box();
	b->add_text("Box two")->format(ALIGN_RIGHT, 0);
	b->set_z_index(-2);

	nw.draw_all();
	
	while (true) {}
	}

	return 0;
}
