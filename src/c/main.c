#include <pebble.h>

#define PERSIST_STARTZEIT 10

#define PAUSE1 30
#define PAUSE2 15
	
#define TRUE 1
#define FALSE 0
#define SCREENWIDTH 144
#define SCREENHEIGHT 168 

Window *my_window;
TextLayer *text_layerStartLabel;
TextLayer *text_layerStart;
TextLayer *text_layer6Label;
TextLayer *text_layer6;
TextLayer *text_layer630Label;
TextLayer *text_layer630;
TextLayer *text_layer8Label;
TextLayer *text_layer8;
TextLayer *text_layer9Label;
TextLayer *text_layer9;
TextLayer *text_layer915Label;
TextLayer *text_layer915;
TextLayer *text_layer10Label;
TextLayer *text_layer10;

time_t startzeit;
time_t zeit6h;
time_t zeit630h; //6+Pause
time_t zeit8h; // 8h + Pause!
time_t zeit9h; // 9+Pause
time_t zeit915h; //9+Pause1 + Pause2
time_t zeit10h;
char bufferStartzeit[]="00:00";
char bufferZeit6[]="00:00";
char bufferZeit630[]="00:00";
char bufferZeit8[]="00:00";
char bufferZeit9[]="00:00";
char bufferZeit915[]="00:00";
char bufferZeit10[]="00:00";


void anzeigeAktualisieren(void);
void setzeBuffer(time_t zeit, char buf[]);
void setzeZeiten(void);


static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	// Setze aktuelle Zeit als Startzeit
	startzeit =time(NULL);	
	setzeZeiten();
anzeigeAktualisieren();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	// Öffne Fenster um Startzeit einzustellen
	startzeit =time(NULL);	
	setzeZeiten();
anzeigeAktualisieren();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
}


void handle_init(void) {
  my_window = window_create();
 window_set_click_config_provider(my_window, click_config_provider);
	startzeit=0;
	zeit6h=0;
  	zeit630h=0;
 	zeit8h=0;
 	zeit9h=0;
 	zeit915h=0;
	zeit10h=0;
	
	if (persist_exists(PERSIST_STARTZEIT)) {
	  startzeit=persist_read_int(PERSIST_STARTZEIT);
		setzeZeiten();
    }

	int offsetRoundLabel = PBL_IF_ROUND_ELSE(50,0);
	int offsetRoundZeit = PBL_IF_ROUND_ELSE(5,0);
	int offsetRoundY=PBL_IF_ROUND_ELSE(5,0);
	
	text_layerStartLabel = text_layer_create(GRect(5+offsetRoundLabel, 5+offsetRoundY, 2*SCREENWIDTH/3+offsetRoundLabel, 25+offsetRoundY));
	text_layer_set_text(text_layerStartLabel,"Start:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layerStartLabel));
	
	text_layerStart = text_layer_create(GRect(2*SCREENWIDTH/3-offsetRoundZeit, 5+offsetRoundY, SCREENWIDTH/3-5, 25+offsetRoundY));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layerStart));
	text_layer_set_text_alignment(text_layerStart, GTextAlignmentRight);
	
	
	offsetRoundLabel = PBL_IF_ROUND_ELSE(18,0);
	offsetRoundZeit = PBL_IF_ROUND_ELSE(-5,0);
	
	
	text_layer6Label = text_layer_create(GRect(5+offsetRoundLabel,25+offsetRoundY,2*SCREENWIDTH/3+offsetRoundLabel, 45+offsetRoundY));
	text_layer_set_text(text_layer6Label,"30 min Pause:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer6Label));
	
	text_layer6 = text_layer_create(GRect(2*SCREENWIDTH/3-offsetRoundZeit, 25+offsetRoundY, SCREENWIDTH/3-5-offsetRoundZeit, 45+offsetRoundY));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer6));
	text_layer_set_text_alignment(text_layer6, GTextAlignmentRight);
	
	offsetRoundLabel = PBL_IF_ROUND_ELSE(14,0);
	offsetRoundZeit = PBL_IF_ROUND_ELSE(-5,0);
	text_layer630Label = text_layer_create(GRect(5+offsetRoundLabel,45+offsetRoundY, 2*SCREENWIDTH/3+offsetRoundLabel, 65+offsetRoundY));
	text_layer_set_text(text_layer630Label,"Pause (Ende):");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer630Label));
	
	text_layer630 = text_layer_create(GRect(2*SCREENWIDTH/3-offsetRoundZeit, 45+offsetRoundY, SCREENWIDTH/3-5-offsetRoundZeit, 65+offsetRoundY));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer630));
	text_layer_set_text_alignment(text_layer630, GTextAlignmentRight);
	
	offsetRoundLabel = PBL_IF_ROUND_ELSE(80,0);
	offsetRoundZeit = PBL_IF_ROUND_ELSE(-5,0);	
	
	text_layer8Label = text_layer_create(GRect(5+offsetRoundLabel,65+offsetRoundY, 2*SCREENWIDTH/3+offsetRoundLabel, 85+offsetRoundY));
	text_layer_set_text(text_layer8Label,"8h:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer8Label));
	
	text_layer8 = text_layer_create(GRect(2*SCREENWIDTH/3-offsetRoundZeit, 65+offsetRoundY, SCREENWIDTH/3-5-offsetRoundZeit, 85+offsetRoundY));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer8));
	text_layer_set_text_alignment(text_layer8, GTextAlignmentRight);
	
	
	offsetRoundLabel = PBL_IF_ROUND_ELSE(18,0);
	offsetRoundZeit = PBL_IF_ROUND_ELSE(-5,0);
	
	text_layer9Label = text_layer_create(GRect(5+offsetRoundLabel,85+offsetRoundY, 2*SCREENWIDTH/3+offsetRoundLabel, 105+offsetRoundY));
	text_layer_set_text(text_layer9Label,"15 min Pause:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer9Label));
	
	text_layer9 = text_layer_create(GRect(2*SCREENWIDTH/3-offsetRoundZeit, 85+offsetRoundY, SCREENWIDTH/3-5-offsetRoundZeit, 105+offsetRoundY));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer9));
	text_layer_set_text_alignment(text_layer9, GTextAlignmentRight);
	
	offsetRoundLabel = PBL_IF_ROUND_ELSE(13,0);
	offsetRoundZeit = PBL_IF_ROUND_ELSE(-5,0);
	
	text_layer915Label = text_layer_create(GRect(5+offsetRoundLabel,105+offsetRoundY, 2*SCREENWIDTH/3+offsetRoundLabel, 125+offsetRoundY));
	text_layer_set_text(text_layer915Label,"Pause (Ende):");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer915Label));
	
	text_layer915 = text_layer_create(GRect(2*SCREENWIDTH/3-offsetRoundZeit, 105+offsetRoundY, SCREENWIDTH/3-5-offsetRoundZeit, 125+offsetRoundY));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer915));
	text_layer_set_text_alignment(text_layer915, GTextAlignmentRight);
	
	
 	offsetRoundLabel = PBL_IF_ROUND_ELSE(75,0);
	offsetRoundZeit = PBL_IF_ROUND_ELSE(-5,0);
	
	text_layer10Label = text_layer_create(GRect(5+offsetRoundLabel,125+offsetRoundY, 2*SCREENWIDTH/3+offsetRoundLabel, 145+offsetRoundY));
	text_layer_set_text(text_layer10Label,"10h:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer10Label));
	
	text_layer10 = text_layer_create(GRect(2*SCREENWIDTH/3-offsetRoundZeit, 125+offsetRoundY, SCREENWIDTH/3-5-offsetRoundZeit, 145+offsetRoundY));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer10));
	text_layer_set_text_alignment(text_layer10, GTextAlignmentRight);
    //Change the TextLayer text to show the new time!
  
	anzeigeAktualisieren();
	  window_stack_push(my_window, true);
}




void anzeigeAktualisieren(void){

	setzeBuffer(startzeit,bufferStartzeit);
	text_layer_set_text(text_layerStart,bufferStartzeit);
	
	setzeBuffer(zeit6h,bufferZeit6);
	text_layer_set_text(text_layer6,bufferZeit6);

	setzeBuffer(zeit630h,bufferZeit630);
	text_layer_set_text(text_layer630,bufferZeit630);
	
	setzeBuffer(zeit8h,bufferZeit8);
	text_layer_set_text(text_layer8,bufferZeit8);
	
	setzeBuffer(zeit9h,bufferZeit9);
	text_layer_set_text(text_layer9,bufferZeit9);
	
	setzeBuffer(zeit915h,bufferZeit915);
	text_layer_set_text(text_layer915,bufferZeit915);
	
	setzeBuffer(zeit10h,bufferZeit10);
	text_layer_set_text(text_layer10,bufferZeit10);
}
	
void setzeBuffer(time_t zeit, char buf[]){
	struct tm *t;	
 	t = localtime(&zeit);
    strftime(buf, sizeof("00:00"), "%H:%M", t);
}

void handle_deinit(void) {
	text_layer_destroy(text_layerStartLabel);
	text_layer_destroy(text_layerStart);
	text_layer_destroy(text_layer6Label);
	text_layer_destroy(text_layer6);
	text_layer_destroy(text_layer630Label);
	text_layer_destroy(text_layer630);
	text_layer_destroy(text_layer8Label);
	text_layer_destroy(text_layer8);
	text_layer_destroy(text_layer9Label);
	text_layer_destroy(text_layer9);
	text_layer_destroy(text_layer915Label);
	text_layer_destroy(text_layer915);
	text_layer_destroy(text_layer10Label);
	text_layer_destroy(text_layer10);

	window_destroy(my_window);
		
	persist_write_int(PERSIST_STARTZEIT,startzeit);
	
}

void setzeZeiten(void)
	{
	int h;  
	int hAusgleich1=0; //wird gesetzt, falls Minuten >60 nach 1. Pause
	int hAusgleich2=0; //wird gesetzt, falls Minuten >60 nach 2. Pause
	int m;   // vor der Pause
	int m2;  // nach der 1. Pause
	int m3;  // nach der 2. Pause
	
	//startzeit =time(NULL);		
	struct tm *tm_struct = localtime(&startzeit);
	h = tm_struct->tm_hour;
	m = tm_struct->tm_min;
	
	// Minuten berechnen 
	m2=m+PAUSE1;
	if (m2>60){
	    hAusgleich1=1;
		m2=m2-60;
	}
    m3=m2+PAUSE2;
    if (m3>60){
	    hAusgleich2=1;
		m3=m3-60;
	}


	zeit6h =  clock_to_timestamp(TODAY, h+6, m);	
	zeit630h=clock_to_timestamp(TODAY, h+6+hAusgleich1, m2);	
	zeit8h=	clock_to_timestamp(TODAY, h+8+hAusgleich1, m2);
	zeit9h=clock_to_timestamp(TODAY, h+9+hAusgleich1, m2);
	zeit915h= clock_to_timestamp(TODAY, h+9+hAusgleich1+ hAusgleich2, m3);
	zeit10h=clock_to_timestamp(TODAY, h+10+hAusgleich1+ hAusgleich2, m3);
    }



int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
