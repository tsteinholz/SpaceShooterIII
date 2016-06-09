#include <gameobjects/physics/player.h>

Player::Player(ALLEGRO_BITMAP *image, b2World *world, float x, float y)
    : Projectile(image, world, x, y) {

}

Player::Player(const Player& p)
    : Projectile(p.Image, p.m_world, p.m_body->GetTransform().p.x, p.m_body->GetTransform().p.y) {

}

Player::~Player() {

}

void Player::Render() {

}

void Player::Update(ALLEGRO_EVENT *event) {

}
