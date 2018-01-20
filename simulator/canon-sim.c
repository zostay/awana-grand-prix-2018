#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_COLOR canon_color;

void set_canon_color(int r, int g, int b) {
    canon_color = al_map_rgb(r, g, b);
}

int bang_step = 0;

#define BANG_WHITE 0
#define BANG_FLASHY 4
#define BANG_YELLOW 10
#define BANG_RED 14
#define BANG_BLACK 30

#define MIN_DELAY 30
#define MAX_DELAY 30

void setup() {
    set_canon_color(0, 0, 0);
}

int min(int one, int two) {
    return one < two ? one : two;
}

int fade(int from, int to) {
    if (bang_step < from) 
        return 255;
    else if (bang_step > to)
        return 0;
    else {
        float num = bang_step - from;
        float den = to - from;
        return 255 - (int) 255 * (num/den);
    }
}

float frand(float a) {
    return ((float)rand()/(float)(RAND_MAX)) * a;
}

void loop() {
    if (++bang_step > BANG_BLACK && frand(100.0) <= 1.4) {
        bang_step = BANG_WHITE;
    }

    if (bang_step > BANG_BLACK + MAX_DELAY) {
        bang_step = BANG_WHITE;
    }

    printf("step = %d\n", bang_step);

    if (bang_step == BANG_WHITE) {
        set_canon_color(255, 255, 255);
    }
    else if (bang_step <= BANG_FLASHY) {
        set_canon_color(frand(1.0) * 255, frand(1.0) * 255, frand(1.0) * 255);
    }
    else {
        set_canon_color(
            min(fade(BANG_RED, BANG_BLACK), fade(BANG_WHITE, BANG_BLACK)),
            min(fade(BANG_WHITE, BANG_RED), fade(BANG_WHITE, BANG_BLACK)),
            min(fade(BANG_WHITE, BANG_YELLOW), fade(BANG_WHITE, BANG_BLACK))
        );
    }
}

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(600, 120);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize primitives!\n");
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    setup();

    while (1) {
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);

        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

        if (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        loop();

        al_draw_filled_rectangle(10.0, 10.0, 1000.0, 100.0, canon_color);

        al_flip_display();
    }

    al_destroy_display(display);

    return 0;
}
