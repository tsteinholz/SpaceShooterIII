//-----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016 Thomas Steinholz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#include <gameobjects/physics/projectile.h>

Projectile::Projectile(ALLEGRO_BITMAP *image, b2World *world, float x, float y)
    : Image(image), Velocity(0, 0),m_body(), m_world(world) {
    b2BodyDef proj;
    proj.position.Set(x, y);
	proj.type = b2_kinematicBody;
	proj.gravityScale = 0;
    m_body = m_world->CreateBody(&proj);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(al_get_bitmap_width(Image) ,al_get_bitmap_height(Image));
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    m_body->CreateFixture(&boxFixtureDef);
    m_body->SetActive(true);
}

Projectile::Projectile(const Projectile& p)
    : Image(p.Image), m_body(), m_world(p.m_world) { }

Projectile::~Projectile() {
    m_world->DestroyBody(m_body);
}

void Projectile::Render() {
    al_draw_bitmap(Image, m_body->GetPosition().x, m_body->GetPosition().y, 0);
}

void Projectile::Update(ALLEGRO_EVENT *event) {
    m_body->SetLinearVelocity(Velocity);
    m_body->SetTransform(b2Vec2(m_body->GetPosition().x + Velocity.x, m_body->GetPosition().y + Velocity.y), 0);
}
