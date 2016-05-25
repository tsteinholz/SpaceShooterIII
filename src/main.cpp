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

#include <gameobjects/ui/button.h>



////////////////////////////////////////////////////////////////////////////////////////////////////
// When the DEBUG Macro is defined the game will run in DEBUG mode

#define DEBUG

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Variables & Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

void initialize();
void shutdown();

int screen_w = 0, screen_h = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Structs and Data
////////////////////////////////////////////////////////////////////////////////////////////////////
struct Stats {
    int enemies_destroyed = 0,
        meteors_destroyed = 0;

    float start_time = 0,
          end_time = 0;
};

struct Assets {
public:
    Assets() :
        png_background(load_bitmap("res/imgs/Backgrounds/purple.png")),
        png_player(load_bitmap("res/imgs/Players/playerShip1_blue.png")),
        png_player_damage1(load_bitmap("res/imgs/Damage/playerShip1_damage1.png")),
        png_player_damage2(load_bitmap("res/imgs/Damage/playerShip1_damage2.png")),
        png_player_damage3(load_bitmap("res/imgs/Damage/playerShip1_damage3.png")),
        png_player_laser(load_bitmap("res/imgs/Lasers/laserBlue07.png")),
        png_meteor_brown_big1(load_bitmap("res/imgs/Meteors/meteorBrown_big1.png")),
        png_meteor_brown_big2(load_bitmap("res/imgs/Meteors/meteorBrown_big2.png")),
        png_meteor_brown_big3(load_bitmap("res/imgs/Meteors/meteorBrown_big3.png")),
        png_meteor_brown_big4(load_bitmap("res/imgs/Meteors/meteorBrown_big4.png")),
        png_meteor_brown_med1(load_bitmap("res/imgs/Meteors/meteorBrown_med1.png")),
        png_meteor_brown_med2(load_bitmap("res/imgs/Meteors/meteorBrown_med3.png")),
        png_meteor_brown_small1(load_bitmap("res/imgs/Meteors/meteorBrown_small1.png")),
        png_meteor_brown_small2(load_bitmap("res/imgs/Meteors/meteorBrown_small2.png")),
        png_meteor_brown_tiny1(load_bitmap("res/imgs/Meteors/meteorBrown_tiny1.png")),
        png_meteor_brown_tiny2(load_bitmap("res/imgs/Meteors/meteorBrown_tiny2.png")),
        png_meteor_grey_big1(load_bitmap("res/imgs/Meteors/meteorGrey_big1.png")),
        png_meteor_grey_big2(load_bitmap("res/imgs/Meteors/meteorGrey_big2.png")),
        png_meteor_grey_big3(load_bitmap("res/imgs/Meteors/meteorGrey_big3.png")),
        png_meteor_grey_big4(load_bitmap("res/imgs/Meteors/meteorGrey_big4.png")),
        png_meteor_grey_med1(load_bitmap("res/imgs/Meteors/meteorGrey_med1.png")),
        png_meteor_grey_med2(load_bitmap("res/imgs/Meteors/meteorGrey_med2.png")),
        png_meteor_grey_small1(load_bitmap("res/imgs/Meteors/meteorGrey_small1.png")),
        png_meteor_grey_small2(load_bitmap("res/imgs/Meteors/meteorGrey_small2.png")),
        png_meteor_grey_tiny1(load_bitmap("res/imgs/Meteors/meteorGrey_tiny1.png")),
        png_meteor_grey_tiny2(load_bitmap("res/imgs/Meteors/meteorGrey_tiny2.png")),
        png_enemy_black1(load_bitmap("res/imgs/Enemies/enemyBlack1.png")),
        png_enemy_black2(load_bitmap("res/imgs/Enemies/enemyBlack2.png")),
        png_enemy_black3(load_bitmap("res/imgs/Enemies/enemyBlack3.png")),
        png_enemy_black4(load_bitmap("res/imgs/Enemies/enemyBlack4.png")),
        png_enemy_blue1(load_bitmap("res/imgs/Enemies/enemyBlue1.png")),
        png_enemy_blue2(load_bitmap("res/imgs/Enemies/enemyBlue2.png")),
        png_enemy_blue3(load_bitmap("res/imgs/Enemies/enemyBlue3.png")),
        png_enemy_blue4(load_bitmap("res/imgs/Enemies/enemyBlue4.png")),
        png_enemy_green1(load_bitmap("res/imgs/Enemies/enemyGreen1.png")),
        png_enemy_green2(load_bitmap("res/imgs/Enemies/enemyGreen2.png")),
        png_enemy_green3(load_bitmap("res/imgs/Enemies/enemyGreen3.png")),
        png_enemy_green4(load_bitmap("res/imgs/Enemies/enemyGreen4.png")),
        png_enemy_red1(load_bitmap("res/imgs/Enemies/enemyRed1.png")),
        png_enemy_red2(load_bitmap("res/imgs/Enemies/enemyRed2.png")),
        png_enemy_red3(load_bitmap("res/imgs/Enemies/enemyRed3.png")),
        png_enemy_red4(load_bitmap("res/imgs/Enemies/enemyRed4.png")),
        png_enemy_laser(load_bitmap("res/imgs/Lasers/laserRed03.png")),
        fnt_title(load_font("res/fonts/kenvector_future.ttf", 70)),
        fnt_menu(load_font("res/fonts/kenvector_future.ttf", 40))
    { }

    Assets(const Assets& a) :
        png_background(a.png_background),
        png_player(a.png_player),
        png_player_damage1(a.png_player_damage1),
        png_player_damage2(a.png_player_damage2),
        png_player_damage3(a.png_player_damage3),
        png_player_laser(a.png_player_laser),
        png_meteor_brown_big1(a.png_meteor_brown_big1),
        png_meteor_brown_big2(a.png_meteor_brown_big2),
        png_meteor_brown_big3(a.png_meteor_brown_big3),
        png_meteor_brown_big4(a.png_meteor_brown_big4),
        png_meteor_brown_med1(a.png_meteor_brown_med1),
        png_meteor_brown_med2(a.png_meteor_brown_med2),
        png_meteor_brown_small1(a.png_meteor_brown_small1),
        png_meteor_brown_small2(a.png_meteor_brown_small2),
        png_meteor_brown_tiny1(a.png_meteor_brown_tiny1),
        png_meteor_brown_tiny2(a.png_meteor_brown_tiny2),
        png_meteor_grey_big1(a.png_meteor_grey_big1),
        png_meteor_grey_big2(a.png_meteor_grey_big2),
        png_meteor_grey_big3(a.png_meteor_grey_big3),
        png_meteor_grey_big4(a.png_meteor_grey_big4),
        png_meteor_grey_med1(a.png_meteor_grey_med1),
        png_meteor_grey_med2(a.png_meteor_grey_med2),
        png_meteor_grey_small1(a.png_meteor_grey_small1),
        png_meteor_grey_small2(a.png_meteor_grey_small2),
        png_meteor_grey_tiny1(a.png_meteor_grey_tiny1),
        png_meteor_grey_tiny2(a.png_meteor_grey_tiny2),
        png_enemy_black1(a.png_enemy_black1),
        png_enemy_black2(a.png_enemy_black2),
        png_enemy_black3(a.png_enemy_black3),
        png_enemy_black4(a.png_enemy_black4),
        png_enemy_blue1(a.png_enemy_blue1),
        png_enemy_blue2(a.png_enemy_blue2),
        png_enemy_blue3(a.png_enemy_blue3),
        png_enemy_blue4(a.png_enemy_blue4),
        png_enemy_green1(a.png_enemy_green1),
        png_enemy_green2(a.png_enemy_green2),
        png_enemy_green3(a.png_enemy_green3),
        png_enemy_green4(a.png_enemy_green4),
        png_enemy_red1(a.png_enemy_red1),
        png_enemy_red2(a.png_enemy_red2),
        png_enemy_red3(a.png_enemy_red3),
        png_enemy_red4(a.png_enemy_red4),
        png_enemy_laser(a.png_enemy_laser),
        fnt_title(a.fnt_title),
        fnt_menu(a.fnt_menu)
        { }

    ~Assets() {
#ifdef DEBUG
        printf("Destroyed Assets\n");
#endif // DEBUG
        al_destroy_bitmap(png_background);
        al_destroy_bitmap(png_player);
        al_destroy_bitmap(png_player_damage1);
        al_destroy_bitmap(png_player_damage2);
        al_destroy_bitmap(png_player_damage3);
        al_destroy_bitmap(png_player_laser);
        al_destroy_bitmap(png_meteor_brown_big1);
        al_destroy_bitmap(png_meteor_brown_big2);
        al_destroy_bitmap(png_meteor_brown_big3);
        al_destroy_bitmap(png_meteor_brown_big4);
        al_destroy_bitmap(png_meteor_brown_med1);
        al_destroy_bitmap(png_meteor_brown_med2);
        al_destroy_bitmap(png_meteor_brown_small1);
        al_destroy_bitmap(png_meteor_brown_small2);
        al_destroy_bitmap(png_meteor_brown_tiny1);
        al_destroy_bitmap(png_meteor_brown_tiny2);
        al_destroy_bitmap(png_meteor_grey_big1);
        al_destroy_bitmap(png_meteor_grey_big2);
        al_destroy_bitmap(png_meteor_grey_big3);
        al_destroy_bitmap(png_meteor_grey_big4);
        al_destroy_bitmap(png_meteor_grey_med1);
        al_destroy_bitmap(png_meteor_grey_med2);
        al_destroy_bitmap(png_meteor_grey_small1);
        al_destroy_bitmap(png_meteor_grey_small2);
        al_destroy_bitmap(png_meteor_grey_tiny1);
        al_destroy_bitmap(png_meteor_grey_tiny2);
        al_destroy_bitmap(png_enemy_black1);
        al_destroy_bitmap(png_enemy_black2);
        al_destroy_bitmap(png_enemy_black3);
        al_destroy_bitmap(png_enemy_black4);
        al_destroy_bitmap(png_enemy_blue1);
        al_destroy_bitmap(png_enemy_blue2);
        al_destroy_bitmap(png_enemy_blue3);
        al_destroy_bitmap(png_enemy_blue4);
        al_destroy_bitmap(png_enemy_green1);
        al_destroy_bitmap(png_enemy_green2);
        al_destroy_bitmap(png_enemy_green3);
        al_destroy_bitmap(png_enemy_green4);
        al_destroy_bitmap(png_enemy_red1);
        al_destroy_bitmap(png_enemy_red2);
        al_destroy_bitmap(png_enemy_red3);
        al_destroy_bitmap(png_enemy_red4);
        al_destroy_bitmap(png_enemy_laser);
        al_destroy_font(fnt_title);
        al_destroy_font(fnt_menu);
    }

    Assets& operator = (const Assets& a);

    ALLEGRO_BITMAP *png_background,
        *png_player,
        *png_player_damage1,
        *png_player_damage2,
        *png_player_damage3,
        *png_player_laser,
        *png_meteor_brown_big1,
        *png_meteor_brown_big2,
        *png_meteor_brown_big3,
        *png_meteor_brown_big4,
        *png_meteor_brown_med1,
        *png_meteor_brown_med2,
        *png_meteor_brown_small1,
        *png_meteor_brown_small2,
        *png_meteor_brown_tiny1,
        *png_meteor_brown_tiny2,
        *png_meteor_grey_big1,
        *png_meteor_grey_big2,
        *png_meteor_grey_big3,
        *png_meteor_grey_big4,
        *png_meteor_grey_med1,
        *png_meteor_grey_med2,
        *png_meteor_grey_small1,
        *png_meteor_grey_small2,
        *png_meteor_grey_tiny1,
        *png_meteor_grey_tiny2,
        *png_enemy_black1,
        *png_enemy_black2,
        *png_enemy_black3,
        *png_enemy_black4,
        *png_enemy_blue1,
        *png_enemy_blue2,
        *png_enemy_blue3,
        *png_enemy_blue4,
        *png_enemy_green1,
        *png_enemy_green2,
        *png_enemy_green3,
        *png_enemy_green4,
        *png_enemy_red1,
        *png_enemy_red2,
        *png_enemy_red3,
        *png_enemy_red4,
        *png_enemy_laser;

    ALLEGRO_FONT *fnt_title, *fnt_menu;

protected:
    ALLEGRO_BITMAP *load_bitmap(const char *file) {
        auto tmp = al_load_bitmap(file);
        assert(tmp && printf("Loaded %s\n", file));
        return tmp;
    }

    ALLEGRO_FONT *load_font(const char *file, int font) {
        auto tmp = al_load_font(file, font, ALLEGRO_TTF_MONOCHROME);
        assert(tmp && printf("Loaded %s\n", file));
        return tmp;
    }
};

typedef enum {
    Menu,
    Game,
    Leaderboard,
    Options,
    End,
} Stage;

int main(void) {
    initialize();

    int nva = al_get_num_video_adapters();
    assert(nva);

    ALLEGRO_MONITOR_INFO aminfo;
    al_get_monitor_info(0, &aminfo);
    screen_w = aminfo.x2 - aminfo.x1 + 1;
    screen_h = aminfo.y2 - aminfo.y1 + 1;

    ALLEGRO_DISPLAY *display = al_create_display(screen_w, screen_h);
    ALLEGRO_EVENT_QUEUE *evqueue = al_create_event_queue();
    ALLEGRO_TIMER *fps_timer = al_create_timer(1.0 / 120.0);

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

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Local Variables
    ////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
    float fps = 0, delta_time = 0, current_time = 0, last_time = al_get_time();
#endif //DEBUG
    bool render = true, executing = true;

    Assets* assets = new Assets();
    Stage stage = Menu;

    Button *play = new Button("Play", assets->fnt_menu, screen_w / 2, 300, [&stage]() -> void {
                stage = Game;
                              }),
        *leaderboard = new Button("Leaderboard", assets->fnt_menu, screen_w / 2, 400, [&stage]() -> void {
                stage = Leaderboard;
                              }),
        *options = new Button("Options", assets->fnt_menu, screen_w / 2, 500, [&stage]() -> void {
                stage = Options;
                              }),
        *quit = new Button("Quit", assets->fnt_menu, screen_w / 2, 600, [&executing]() -> void {
                executing = false;
                              });

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Game Loop
    ////////////////////////////////////////////////////////////////////////////////////////////////

    while (executing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(evqueue, &event);

#ifdef DEBUG
        current_time = al_get_time();
        delta_time = current_time - last_time;
        fps = 1/(delta_time);
        last_time = current_time;
#endif //DEBUG

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
            default: break;
        }
        switch (stage) { // UPDATE
            case Menu:
                play->Update(&event);
                leaderboard->Update(&event);
                options->Update(&event);
                quit->Update(&event);
                break;
            case Game:

                break;
            case Leaderboard:
                break;
            case Options:

                break;
            case End:

                break;
            default: break;
        }
        if (render && al_is_event_queue_empty(evqueue)) {
            render = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_set_target_bitmap(al_get_backbuffer(display));
            for (float x = 0; x < screen_w; x += al_get_bitmap_width(assets->png_background)) {
                for (float y = 0; y < screen_h; y += al_get_bitmap_height(assets->png_background)) {
                    al_draw_bitmap(assets->png_background, x, y, 0);
                }
            }
#ifdef DEBUG
            //al_draw_textf(assets->fnt_menu, al_map_rgb(255, 255, 255), 10, 5, ALLEGRO_ALIGN_LEFT, "FPS: %i", (int)fps);
#endif // DEBUG
            switch (stage) { // RENDER
            default: break;
            case Menu:
                al_draw_text(assets->fnt_title, al_map_rgb(255, 255, 255), screen_w/2, 100, ALLEGRO_ALIGN_CENTRE, "SPACE SHOOTER III");
                play->Render();
                leaderboard->Render();
                options->Render();
                quit->Render();
                break;
            case Game:

                break;
            case Leaderboard:

                break;
            case Options:

                break;
            case End:

                break;
            }
            al_flip_display();
        }
        render = false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Deinitialization
    ////////////////////////////////////////////////////////////////////////////////////////////////

    al_unregister_event_source(evqueue, al_get_keyboard_event_source());
    al_unregister_event_source(evqueue, al_get_mouse_event_source());
    al_unregister_event_source(evqueue, al_get_display_event_source(display));
    al_unregister_event_source(evqueue, al_get_timer_event_source(fps_timer));

    al_destroy_display(display);
    al_destroy_event_queue(evqueue);
    al_destroy_timer(fps_timer);

    delete assets;
    shutdown();
    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

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
