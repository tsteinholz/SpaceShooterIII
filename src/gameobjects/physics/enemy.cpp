#include <gameobjects/physics/enemy.h>

Enemy::Enemy(ALLEGRO_BITMAP *image, b2World *world, float x, float y)
    : Projectile(image, world, x, y) {

}

Enemy::Enemy(const Enemy& p)
    : Projectile(p.Image, p.m_world, p.m_body->GetTransform().p.x, p.m_body->GetTransform().p.y) {

}

Enemy::~Enemy() {

}

void Enemy::Render() {

}

void Enemy::Update(ALLEGRO_EVENT *event) {

}
