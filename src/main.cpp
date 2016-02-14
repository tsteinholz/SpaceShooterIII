#include <scene/menu.h>

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter III");
    Scene::Current = unique_ptr<Scene>(new Menu());

    while (Scene::Executing)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) Scene::Executing = false;
            window.clear(sf::Color::Black);
            Scene::Current->Render();
            window.display();
        }
    }

    return EXIT_SUCCESS;
}