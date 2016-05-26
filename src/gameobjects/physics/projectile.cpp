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

Projectile::Projectile(ALLEGRO_BITMAP *image, float x, float y)
    : Image(image), X(x), Y(y) {
    hitbox[0][0] = X;
    hitbox[0][1] = Y;
    hitbox[1][0] = X + al_get_bitmap_width(Image);
    hitbox[1][1] = Y;
    hitbox[2][0] = X;
    hitbox[2][1] = Y + al_get_bitmap_height(Image);
    hitbox[3][0] = X + al_get_bitmap_width(Image);
    hitbox[3][1] = Y + al_get_bitmap_height(Image);

    velocity[0] = 0;
    velocity[1] = 0;
}

void Projectile::Render() {
    al_draw_bitmap(Image, X, Y, 0);
}

void Projectile::Update(ALLEGRO_EVENT *event) {
    X += velocity[0];
    Y += velocity[1];
}
