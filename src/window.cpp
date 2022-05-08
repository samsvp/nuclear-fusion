#include "../include/window.hpp"


nf::Window::Window() : window_thread(&Window::main, this), should_draw(0)
{
    this->window_thread.launch();
}


nf::Window::~Window()
{
    this->window_thread.wait();
}


void nf::Window::main()
{
    this->canvas.create(800, 600);
    this->canvas.clear(sf::Color::White);

    this->window.create(sf::VideoMode(800, 600), L"s", sf::Style::Default);

    sf::Sprite sprite;
    sprite.setTexture(this->canvas.getTexture(), true);

    while (this->window.isOpen())
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            this->window.close();
            break;
        
        case sf::Event::Resized:
            this->resize();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                this->window.close();
            break;
        }

        if (this->should_draw)
        {
            // Draw our "brush"
            this->canvas.draw(*this->brush);
            // Finalize the texture
            this->canvas.display();

            this->should_draw = false;
        }

        this->window.clear(sf::Color(64, 64, 64));
        
        // Draw our canvas
        this->window.draw(sprite);

        this->window.display();
    }
}


void nf::Window::resize()
{
    // Window got resized, update the view to the new size
    sf::View view(this->window.getView());
    const sf::Vector2f size(this->window.getSize().x, this->window.getSize().y);
    view.setSize(size); // Set the size
    view.setCenter(size / 2.f); // Set the center, moving our drawing to the top left
    this->window.setView(view); // Apply the view
}


void nf::Window::set_brush(Brush* brush)
{
    this->brush = brush;
}
