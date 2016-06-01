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

#ifndef SPACESHOOTERIII_PROJECTILE_H
#define SPACESHOOTERIII_PROJECTILE_H

#include <Box2D/Box2D.h>

#include <gameobjects/gameobject.h>

class Projectile : public GameObject {
public:

    Projectile(ALLEGRO_BITMAP *image, b2World *world, float x = 0, float y = 0);
    Projectile(const Projectile& p);
    ~Projectile();

    void Render() override;

    void Update(ALLEGRO_EVENT *event) override;

    ALLEGRO_BITMAP *Image;

protected:

    b2Body *m_body;
    b2World *m_world;
};

#endif // SPACESHOOTERIII_PROJECTILE_H
