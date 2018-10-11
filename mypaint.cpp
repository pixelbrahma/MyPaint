#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <exception>
#include <iostream>
#include <allegro5\allegro_image.h>

enum KEYS{up,down,right,left};

void rgb(void);

int main(void)
{
	int height = 768;
	int width = 1366;

	int fps = 60;
	int size = 5;
	bool draw = false;

	int r = 0;
	int g = 0;
	int b = 0;

	bool done = false;
	int pos_x = width/2;
	int pos_y = height/2;
	bool keys[] = {false,false,false,false};
	int speed = 5;
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *saveClear = NULL;

	if(!al_init())
		return -1;

	display = al_create_display(width,height);

	if(!display)
		return -1;

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	al_install_keyboard();
	al_install_mouse();

	timer = al_create_timer(1.0/fps);
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue,al_get_mouse_event_source());
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_timer_event_source(timer));

	ALLEGRO_FONT *font60 = al_load_font("LCALLIG.ttf",60,0);
	ALLEGRO_FONT *font50 = al_load_font("COLONNA.ttf",50,0);

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_rest(2.0); 
	
	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			pos_x += keys[right] * speed;
			pos_x -= keys[left] * speed;
			pos_y += keys[down] * speed;
			pos_y -= keys[up] * speed;
		}
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP: keys[up] = true;
					break;
				case ALLEGRO_KEY_DOWN: keys[down] = true;
					break;
				case ALLEGRO_KEY_RIGHT: keys[right] = true;
					break;
				case ALLEGRO_KEY_LEFT: keys[left] = true;
					break;
				case ALLEGRO_KEY_TAB: al_clear_to_color(al_map_rgb(0,0,0));
					break;
				case ALLEGRO_KEY_SPACE: r=0;g=0;b=0;
					break;
				case ALLEGRO_KEY_R: r=255;g=0;b=0;
					break;
				case ALLEGRO_KEY_G:if(g == 255)
								   {
									   r=100;g=100;b=100;
								   }
								   else
								   {
										r=0;g=255;b=0;
								   }
					break;
				case ALLEGRO_KEY_B: if(b==255)
									{
										r= 170;g=100;b=0;
									}
									else
									{
										r= 0;g=0;b=255;
									}
					break;
				case ALLEGRO_KEY_Y: r=255;g=255;b=0;
					break;
				case ALLEGRO_KEY_O: r=255;g=127;b=0;
					break;
				case ALLEGRO_KEY_P: if(b == 255)
									{
										r= 170;g=15;b=240;
									}
									else
									{
										r=255;g=65;b=255;
									}
									break;
				case ALLEGRO_KEY_D: if(g == 15)
									{
									   r= 0;g=60;b=0;
									}
									else if(g == 60)
									{
										r=120;g=50;b=0;
									}
									else
									{
										r=15;g=15;b=50;
									}
					break;
				case ALLEGRO_KEY_V: r=90;g=15;b=90;
					break;
				case ALLEGRO_KEY_C: r=60;g=255;b=255;
					break;
				case ALLEGRO_KEY_L: r=100;g=255;b=0;
					break;
				case ALLEGRO_KEY_S: r=127;g=127;b=127;
					break;
				case ALLEGRO_KEY_T:r=10;g=100;b=10;  
					break;
				case ALLEGRO_KEY_M: r=100;g=0;b=0;
					break;
				case ALLEGRO_KEY_W: r=255;g=255;b=255;
					break;
				case ALLEGRO_KEY_ENTER: saveClear = al_load_bitmap("SaveFile.bmp");
										al_set_target_bitmap(saveClear);
										al_clear_to_color(al_map_rgb(0,0,0));
										al_save_bitmap("SaveFile.bmp", al_get_backbuffer(display));
										al_set_target_bitmap(al_get_backbuffer(display));
										break;
				case ALLEGRO_KEY_Q: rgb();
					break;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE: done = true;
										break;
				case ALLEGRO_KEY_UP:	keys[up] = false;
										break;
				case ALLEGRO_KEY_DOWN: keys[down] = false;
										break;
				case ALLEGRO_KEY_RIGHT: keys[right] = false;
										break;
				case ALLEGRO_KEY_LEFT: keys[left] = false;
										break;
				case ALLEGRO_KEY_ALT:	size += 3;
										break;
				case ALLEGRO_KEY_LCTRL: size -= 3;
										break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y + 15;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1)
				draw = true;
		}
		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if(ev.mouse.button &1)
				draw = false;
		}

		
		if(size <= 0) 
			size = 2;
		else if( size >=51)
			size = 51;

		al_set_target_bitmap(al_get_backbuffer(display));

		if(draw)
		{
			al_draw_filled_circle(pos_x,pos_y,size,al_map_rgb(r,g,b));
			al_hide_mouse_cursor(display);
			al_flip_display();
		}
		
		if(!draw)
			al_show_mouse_cursor(display);
	}
	
	al_stop_timer(timer);

	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(saveClear);
	al_destroy_display(display);
	al_destroy_timer(timer);

	return 0;
}

void rgb(void)
{
	ALLEGRO_DISPLAY *rgb = NULL;
	ALLEGRO_FONT *font50 = al_load_font("comic.ttf",50,0);

	al_create_display(600, 300);

	al_draw_text(font50, al_map_rgb(0, 255, 0), 80, 80, ALLEGRO_ALIGN_CENTRE, "other display");

	al_flip_display();
	al_rest(5.0);

	al_destroy_display(rgb);
	return;
}