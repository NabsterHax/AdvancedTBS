/*

	ComboNinja
		by Fraser Cameron

*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <vector>

#include "Globals.h"
#include "Ninja.h"

bool keys[] = {false, false, false, false, false, false};
bool mouse[] = {false, false};
float mouseX = 0;
float mouseY = 0;

std::vector<SwordAnim>* basicSwordAnims;


void HandleKey(int keycode, bool pressed);
void HandleMouse(int btn, bool pressed);
void InitSwordAnims();

int main()
{
	bool gameRunning = true;

	//TODO: have these set by file, and editable in options menu.
	int maxFPS = 1000;
	int limitedFPS = true;
	bool VSync = false;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_TIMER *tickTimer;
	ALLEGRO_TIMER *drawTimer;
	ALLEGRO_FONT *font18;

	//====================================
	// INIT AND CREATE DISPLAY
	//====================================
	if(!al_init()) 
	{
		al_show_native_message_box(NULL, NULL, NULL, 
			"failed to initialize allegro!", NULL, NULL);                   
		return -1;
	}

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);

	display = al_create_display(WIDTH, HEIGHT);

	if(!display) 
	{
		al_show_native_message_box(NULL, NULL, NULL, 
			"failed to initialize display!", NULL, NULL);
		return -1;
	}

	//====================================
	// ADDON INSTALL
	//====================================
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	eventQueue = al_create_event_queue();
	tickTimer = al_create_timer(1.0 / TICKRATE);
	drawTimer = al_create_timer(1.0 / maxFPS);

	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(tickTimer));
	al_register_event_source(eventQueue, al_get_timer_event_source(drawTimer));

	//====================================
	// GAMEPLAY INIT
	//====================================

	font18 = al_load_font("arial.ttf", 18, 0);

	InitSwordAnims();

	ALLEGRO_BITMAP* swordImg = al_load_bitmap("swordBlack.png");
	Ninja* player = new Ninja(100, 100, swordImg, basicSwordAnims);
	

	//====================================
	// GAME LOOP VARS
	//====================================
	int frameSkips;
	float interpolation;
	bool draw;
	double timeOfTick;
	ALLEGRO_EVENT ev;

	//====================================
	// GAME LOOP START
	//====================================
	al_wait_for_vsync();
	timeOfTick = al_get_time();
	al_start_timer(tickTimer);
	al_start_timer(drawTimer);

	while(gameRunning)
	{
		frameSkips = 0;
		draw = false;

		//Update + event loop
		while(frameSkips < MAX_FRAMESKIP && !al_is_event_queue_empty(eventQueue))
		{
			al_get_next_event(eventQueue, &ev);
			
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				gameRunning = false;
			}
			else if(ev.type == ALLEGRO_EVENT_TIMER)
			{
				if(ev.timer.source == tickTimer)
				{
					timeOfTick = al_get_time();
					//update game objects
					player->Update(keys, mouse, mouseX, mouseY);
				}
				else if(ev.timer.source == drawTimer)
				{
					draw = true;
				}
			}
			else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				mouseX = ev.mouse.x;
				mouseY = ev.mouse.y;
			}
			else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				HandleMouse(ev.mouse.button, true);
			}
			else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				HandleMouse(ev.mouse.button, false);
			}
			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				HandleKey(ev.keyboard.keycode, true);
			}
			else if(ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				HandleKey(ev.keyboard.keycode, false);
			}
		}

		if(draw || !limitedFPS)
		{
			interpolation = (al_get_time() - timeOfTick) * double(TICKRATE);
			//Objects draw themselves
			player->Draw(interpolation);

			//debug
			//al_draw_textf(font18, al_map_rgb(255, 0, 255),10, 10, 0, "curFrame: %i", player->debugAnim());

			if(VSync) { al_wait_for_vsync(); }
			al_flip_display();
			al_clear_to_color(al_map_rgb(127, 127, 127));
		}
	}

	//====================================
	// DESTROY OBJECTS
	//====================================

	delete player;
	delete basicSwordAnims;

	al_destroy_bitmap(swordImg);

	al_destroy_font(font18);
	al_destroy_timer(tickTimer);
	al_destroy_timer(drawTimer);
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);
}

void HandleKey(int keycode, bool pressed)
{
	switch(keycode)
	{
	case ALLEGRO_KEY_W:
		keys[W] = pressed;
		break;
	case ALLEGRO_KEY_A:
		keys[A] = pressed;
		break;
	case ALLEGRO_KEY_S:
		keys[S] = pressed;
		break;
	case ALLEGRO_KEY_D:
		keys[D] = pressed;
		break;
	case ALLEGRO_KEY_SPACE:
		keys[SPACE] = pressed;
		break;
	case ALLEGRO_KEY_LSHIFT:
		keys[SHIFT] = pressed;
		break;
	}
}

void HandleMouse(int btn, bool pressed)
{
	switch(btn)
	{
	case 1:
		mouse[LEFT] = pressed;
	case 2:
		mouse[RIGHT] = pressed;
	}
}

void InitSwordAnims()
{
	basicSwordAnims = new std::vector<SwordAnim>();
	
	std::vector<SwordFrame> anim;
	//Idle
	anim.push_back(SwordFrame(13, -13, 1.7, false, 60));
	anim.push_back(SwordFrame(13, -12, 1.75, false, 60));
	basicSwordAnims->push_back(SwordAnim(anim, true));
	anim.clear();

	//Swing1
	anim.push_back(SwordFrame(13, -13, 1.7, false, 10));
	anim.push_back(SwordFrame(10, -13, 1.0, false, 10));
	anim.push_back(SwordFrame(0, -13, 0, false, 10));
	anim.push_back(SwordFrame(-7, -15, -1, false, 20));
	anim.push_back(SwordFrame(-7, -15, -1.7, false, 30));
	basicSwordAnims->push_back(SwordAnim(anim));
	anim.clear();

	//Swing2
	anim.push_back(SwordFrame(10, -10, 0, false, 2));

	basicSwordAnims->push_back(SwordAnim(anim));
	anim.clear();
}