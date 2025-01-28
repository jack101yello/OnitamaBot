#include "button.h"

Button::Button(int x_i, int y_i, int w_i, int h_i, const char* message_i, TTF_Font* font) {
    textbox = new Textbox(x_i, y_i, w_i, h_i, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, message_i, font);
}

Button::~Button() {
    delete textbox;
}

void set_message(const char* new_message) {

}

void Button::draw(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    textbox -> draw(renderer);
}

bool Button::in_click_range(int click_x, int click_y) {
    printf("The mouse clicked at (%d, %d) and the button is from (%d, %d) to (%d, %d).", click_x, click_y, textbox->get_x(), textbox->get_y(), textbox->get_x()+textbox->get_w(), textbox->get_y()+textbox->get_h());

    return click_x > textbox -> get_x() && click_x < textbox->get_x() + textbox->get_w() && click_y > textbox->get_y() && click_y < textbox->get_y() + textbox->get_h();
}