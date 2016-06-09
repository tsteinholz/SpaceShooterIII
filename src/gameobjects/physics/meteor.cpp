#include <gameobjects/physics/meteor.h>

Meteor::Meteor(ALLEGRO_BITMAP *image, b2World *world, float x, float y)
    : Projectile(image, world, x, y) {

}

Meteor::Meteor(const Meteor& p)
    : Projectile(p.Image, p.m_world, p.m_body->GetTransform().p.x, p.m_body->GetTransform().p.y) {

}

Meteor::~Meteor() {

}
