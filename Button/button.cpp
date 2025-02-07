#include "button.h"

Button::Button(int x_i, int y_i, int w_i, int h_i, const char* message_i) {
    textbox = new Textbox(x_i, y_i, w_i, h_i, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, message_i);
}

Button::~Button() {
    delete textbox;
}

void set_message(const char* new_message) {

}

void Button::draw(SDL_Renderer* renderer) {
    textbox -> draw(renderer);
}

bool Button::in_click_range(int click_x, int click_y) {
    return click_x > textbox -> get_x() && click_x < textbox->get_x() + textbox->get_w() && click_y > textbox->get_y() && click_y < textbox->get_y() + textbox->get_h();
}