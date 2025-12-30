# NCFW (nCurses Framework)

NCFW is a C++ wrapper for `ncurses` that makes building terminal interfaces a lot less painful. Instead of managing window coordinates manually, it uses a parent-child system with relative positioning and Z-indexing.

## Why use this?
* **Relative Positioning:** If you move a parent window, all children move with it automatically.
* **Z-Indexing:** You can layer windows on top of each other without worrying about the draw order.
* **Text Alignment:** No more calculating string lengths and offsets. Just use macros like `ALIGN_CENTER` to put text where it belongs.
* **Easy Boxes:** Adding a border to a sub-window is just one function call.

---

## Getting Started

### 1. Build and Install
You'll need `cmake` and `ncurses` headers installed on your system.

```bash
git clone https://github.com/DeTosis/ncfw
cd ncfw
mkdir build && cd build
cmake ..
make
sudo make install
```

### 2. Include `ncfw.hpp` to your project.
``` c++
#include <ncfw.hpp>
```

### 3. Link your project with `-lncfw -lncurses`

### Quick example

``` c++
  // nterm's constructor handles initialization and
  // destructor exits from raw terminal state automaticly
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
```

<details>
  <summary><b>A bit more about how it works</b></summary>

**`nterm`** The core class that initializes the terminal. Think of it as the engine; you only need one instance to manage the entire console session.

**`nwindow`** A container window used to organize elements. Its main job is to act as a parent for other components, handling things like Z-index and relative layout so you don't have to.

**`add_child()`** Probably the method you'll use most. It creates a new sub-window or component inside the current window. Everything created this way stays relative to the parent’s position.

**`add_text()->format()`** A chained method for putting text on screen. `add_text` creates the string, and `format` lets you snap it to the edges or center of its parent container using alignment macros.

</details>

<details>
  <summary><b>View render result</b></summary>
<img width="956" height="1044" alt="image" src="https://github.com/user-attachments/assets/c76d6a03-e72e-4052-8902-ee23d4d1ffbf" />
</details>

### Roadmap
- [ ] Mouse support
- [ ] Dynamic resizing when terminal window changes
- [ ] Color support
- [ ] Keyboard support
- [ ] Free (Coordinate based) text positioning (Now only pre-defined macros are supported)
- [ ] Automatic cleanup managed by `nterm`'s destructor
