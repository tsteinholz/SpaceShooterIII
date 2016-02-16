#include <scene/menu.h>

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter III");
    sf::Clock timer;
   
    Scene::Current = unique_ptr<Scene>(new Menu());

    while (Scene::Executing)
    {
        sf::Event event;
        auto dt(timer.restart().asSeconds());
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) Scene::Executing = false;
            Scene::Current->Update(event, dt);
        }
        window.clear(sf::Color::Black);
        window.display();
    }

    return EXIT_SUCCESS;
}