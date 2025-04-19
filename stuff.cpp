// library
#include <SFML/Graphics.hpp>
#include <iostream>

// main program
int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Title");

    // create rectangle
    sf::RectangleShape rectangle({400.f, 200.f});

    // color & outline
    rectangle.setFillColor(sf::Color(255, 213, 128));
    rectangle.setOutlineThickness(-20.f);
    rectangle.setOutlineColor(sf::Color(255, 170, 0));

    // set origin
    rectangle.setOrigin({200.f, 100.f});

    // transformation
    // rectangle.setScale({1.5f, 1.f});
    rectangle.setRotation(sf::degrees(30.f));
    rectangle.setPosition({400.f, 300.f});


    // while window is still open
    while (window.isOpen())
    {
        // handle events
        while (std::optional event = window.pollEvent())
        {
            // when close button is clicked
            if (event->is<sf::Event::Closed>())
            {
                // close window
                window.close();
            }
            else if (event->is<sf::Event::Resized>()){
                sf::View view()
                //get details
                // std::cout<<"RESIZE HOGAYA BC = "<<window.getSize().x<<", "<<window.getSize().y<<std::endl;
                // std::cout<<"ViEW RESIZE HOGAYI BC = "<<window.getView().getSize().x<<", "<<window.getView().getSize().y<<std::endl<<std::endl;
            }
        }

        // fill window with color
        window.clear(sf::Color(127, 127, 127));

        // draw
        window.draw(rectangle);

        // display
        window.display();
    }

    
    // program end successfully
    return 0;
}