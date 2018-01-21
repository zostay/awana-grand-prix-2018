#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_COLOR left_color;
ALLEGRO_COLOR right_color;

void set_left_status(int status) {
    int red = status ? 255 : 0;
    left_color = al_map_rgb(red, 0, 0);
}

void set_right_status(int status) {
    int blue = status ? 255 : 0;
    right_color = al_map_rgb(0, 0, blue);
}

void setup() {
    set_left_status(0);
    set_right_status(0);
}

unsigned char program[] = {
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x02, 0x00, 0x02,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x02, 0x00, 0x02,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x02, 0x00, 0x02,
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x02, 0x00, 0x02,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x02, 0x00, 0x02,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x02, 0x00, 0x02,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0xff,
};

int counter = 0;

void loop() {
    if (program[counter] == 0xff) {
        counter = 0;
    }

    set_left_status(program[counter] & 0x01);
    set_right_status(program[counter] & 0x02);

    counter++;
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

        al_draw_filled_rectangle(10.0, 10.0, 490.0, 100.0, left_color);
        al_draw_filled_rectangle(510.0, 10.0, 1000.0, 100.0, right_color);

        al_flip_display();
    }

    al_destroy_display(display);

    return 0;
}
