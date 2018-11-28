#include "rectangle_drawable.hpp" 
#include "kmint/graphics.hpp"

using namespace kmint;

void rectangle_drawable::draw(ui::frame &f) const {
	f.draw_rectangle(actor_->location(), { 10.0, 10.0 }, graphics::colors::white);
}