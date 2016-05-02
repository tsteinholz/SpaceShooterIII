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

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <cstdio>
#include <memory>

#define DEBUG

void initialize();
void shutdown();

int main(void) {
    initialize();

    ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
    ALLEGRO_EVENT_QUEUE *evqueue = al_create_event_queue();
    ALLEGRO_TIMER *fps_timer = al_create_timer(1.0 / 60.0);
    bool render = true, executing = true;

    al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);

    if (!display) {
        printf("Failed to create display!\n");
        exit(EXIT_FAILURE);
    }

    al_register_event_source(evqueue, al_get_keyboard_event_source());
    al_register_event_source(evqueue, al_get_mouse_event_source());
    al_register_event_source(evqueue, al_get_display_event_source(display));
    al_register_event_source(evqueue, al_get_timer_event_source(fps_timer));

    al_start_timer(fps_timer);

    while (executing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(evqueue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                render = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                executing = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                executing = event.keyboard.keycode != ALLEGRO_KEY_ESCAPE;
                break;
        }

        if (render && al_is_event_queue_empty(evqueue)) {
            render = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_filled_rectangle(0, 0, 1920, 1080, al_map_rgb(100, 100, 100));
            al_flip_display();
        }
        render = false;
    }

    al_unregister_event_source(evqueue, al_get_keyboard_event_source());
    al_unregister_event_source(evqueue, al_get_mouse_event_source());
    al_unregister_event_source(evqueue, al_get_display_event_source(display));
    al_unregister_event_source(evqueue, al_get_timer_event_source(fps_timer));

    al_destroy_display(display);
    al_destroy_event_queue(evqueue);
    al_destroy_timer(fps_timer);

    shutdown();
    return EXIT_SUCCESS;
}

void initialize() {
    srand((unsigned int) time(NULL));

#ifdef DEBUG
    printf("Allegro v%i.%i.%i\n",
        al_get_allegro_version() >> 24,
        (al_get_allegro_version() >> 16) & 255,
        (al_get_allegro_version() >> 8) & 255);
#endif //DEBUG

    if (!al_init()) {
        printf("Failed to initialize allegro!\n");
        exit(EXIT_FAILURE);
    }
    if (!al_install_audio()) {
        fprintf(stderr, "Failed to initialize audio!\n");
        exit(EXIT_FAILURE);
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Failed to initialize audio codecs!\n");
        exit(EXIT_FAILURE);
    }
    if (!al_reserve_samples(1)) {
        fprintf(stderr, "Failed to reserve samples!\n");
        exit(EXIT_FAILURE);
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Failed to initialize the mouse!\n");
        exit(EXIT_FAILURE);
    }
    if (!al_install_keyboard()) {
        fprintf(stderr, "al_install_keyboard Failed!\n");
        exit(EXIT_FAILURE);
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
}

void shutdown() {
    al_shutdown_image_addon();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_audio();
    al_uninstall_system();
}
