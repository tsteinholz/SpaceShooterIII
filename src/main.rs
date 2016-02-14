extern crate sfml;

use sfml::system::Vector2f;
use sfml::window::{ ContextSettings, VideoMode, event, Close };
use sfml::graphics::{ RenderWindow, RenderTarget, Color, Sprite, Texture };

fn main() {
    let mut window: RenderWindow = match RenderWindow::new(VideoMode::new_init(800, 600, 32),
        "Space Shooter III",
        Close,
        &ContextSettings::default()) {
        Some(window) => window,
        None => panic!("Cannot create a new Render Window.")
    };
    window.set_vertical_sync_enabled(true);

    //let mut img: Texture = new_from_file("res/gfx/playerShip1_blue.png");

    while window.is_open() {
        for event in window.events() {
            match event {
                event::Closed => window.close(),
                _             => { }

            }
        }
        window.clear(&Color::black());
        window.display()
    }
}
