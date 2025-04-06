#include <iostream>
#include <SFML/Graphics.hpp>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>


const int rows = 6, cols = 16;
const int cell_size = 100;

// TODO(any): class attributes
std::string current_action = "";
Fl_Button* selected_cell = nullptr;

void cell_cb(Fl_Widget* w, void* data) {
  Fl_Button* btn = static_cast<Fl_Button*>(w);
  int cell_id = reinterpret_cast<intptr_t>(data);
  int row = cell_id / cols;
  int col = cell_id % cols;

  if (!current_action.empty()) {
    std::cout << "Acción '" << current_action
      << "' en casilla (" << row << ", " << col << ")" << std::endl;
    // refresh selection
    if (selected_cell) {
      selected_cell->color(FL_BACKGROUND_COLOR);
      selected_cell->redraw();
    }
    selected_cell = btn;
    selected_cell->color(FL_YELLOW);
    selected_cell->redraw();
  } else {
    std::cout << "Selecciona primero una acción del menú." << std::endl;
  }
}
void loadImage(Fl_Widget* widget, char* path) {
  Fl_PNG_Image* image = new Fl_PNG_Image(path);
  if (!image->fail()) {
    widget->image(image);
  }
}

int main(int argc, char **argv) {
  Fl_Window* window = new Fl_Window(1920, 1080
      , "Vessels of Order: Battle for the Seas");
  window->resizable(window);
  window->fullscreen();
  window->color(fl_rgb_color(5, 10, 48));
  // Fl_Box *background = new Fl_Box(0, 0, 1640, 640);
  // loadImage(background, "assets/scenes_backgrounds/board.png");
  // Buttons
  Fl_Toggle_Button *attack = new Fl_Toggle_Button(1750, 250, 100, 100
      , "Attack");
  attack->labelcolor(FL_WHITE);
  loadImage(attack, "assets/sprites/buttons/attackRune.png");
  Fl_Toggle_Button *upgrade = new Fl_Toggle_Button(1750, 400, 100, 100
      , "Upgrade");
  upgrade->labelcolor(FL_WHITE);
  loadImage(upgrade, "assets/sprites/buttons/upgradeRune.png");
  Fl_Toggle_Button *move = new Fl_Toggle_Button(1750, 550, 100, 100, "Move");
  move->labelcolor(FL_WHITE);
  loadImage(move, "assets/sprites/buttons/moveRune.png");
  Fl_Toggle_Button *buy = new Fl_Toggle_Button(1750, 700, 100, 100, "Buy");
  buy->labelcolor(FL_WHITE);
  loadImage(buy, "assets/sprites/buttons/buyRune.png");

  // colors
  Fl_Color light_cell = fl_rgb_color(3, 169, 244);
  Fl_Color dark_cell = fl_rgb_color(2, 136, 209);

  // Board
  for (int i = 0; i < rows * cols; ++i) {
    int x = 80 + (i % cols) * cell_size;
    int y = 140 + (i / cols) * cell_size;

    Fl_Button* cell = new Fl_Button(x, y, cell_size, cell_size);
    cell->callback(cell_cb, reinterpret_cast<void*>(i));
    cell->box(FL_FLAT_BOX);
    if (((i / cols) + (i % cols)) % 2 == 0) {
      cell->color(light_cell); 
    } else {
        cell->color(dark_cell);
    }
    cell->redraw();
  }

  window->end();
  window->show(argc, argv);
  return Fl::run();
}