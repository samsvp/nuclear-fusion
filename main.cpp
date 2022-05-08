#include <SFML/Graphics.hpp>
#include <vector>

#include "include/brush.hpp"
#include "include/window.hpp"


int main(int argc, char **argv) 
{
    nf::Window window;

    nf::Brush brush = nf::Brush("../brushes/3.png", {50,50});
    brush.setColor({255,0,0,8});
    brush.draw_line(&window, 100, 250, 1, 1);
    brush.draw_line(&window, 300, 350, 100, 250);
    brush.draw_circle(&window, 400, 400, 100);
    brush.draw_ellipse(&window, 400, 300, 100, 200);

    return 0;
}