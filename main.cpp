/*

	AdvancedTBS
		main.cpp

*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Globals.h"
#include "Map.h"

Map* testMap;

void Update();
void Draw(float interpolation);

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

	//====================================
	// INIT AND CREATE DISPLAY
	//====================================
	if(!al_init()) 
	{
		al_show_native_message_box(NULL, "Error", "", 
			"failed to initialize allegro!", NULL, NULL);                   
		return -1;
	}

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);

	display = al_create_display(WIDTH, HEIGHT);

	if(!display) 
	{
		al_show_native_message_box(NULL, "Error", "", 
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

	ALLEGRO_BITMAP* terrainTileSheet = al_load_bitmap("Resources/TerrainTiles.png");
	testMap = new Map(10, 10, terrainTileSheet);
	testMap->setTerrainAt(2, 9, WATER);

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
					Update();
				}
				else if(ev.timer.source == drawTimer)
				{
					draw = true;
				}
			}
		}

		if(draw || !limitedFPS)
		{
			interpolation = (al_get_time() - timeOfTick) * double(TICKRATE);
			//Objects draw themselves
			Draw(interpolation);

			if(VSync) { al_wait_for_vsync(); }
			al_flip_display();
			al_clear_to_color(al_map_rgb(127, 127, 127));
		}
	}

	//====================================
	// DESTROY OBJECTS
	//====================================

	delete testMap;

	al_destroy_timer(tickTimer);
	al_destroy_timer(drawTimer);
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);
}

void Update()
{
}

void Draw(float interpolation)
{
	testMap->Draw(interpolation);
}