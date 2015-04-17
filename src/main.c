#include <pebble.h>

#define PERSIST_STARTZEIT 10
#define PERSIST_ZEIT6 11
#define PERSIST_ZEIT630 12
#define PERSIST_ZEIT8 13
#define PERSIST_ZEIT9 14
#define PERSIST_ZEIT915 15
#define PERSIST_ZEIT10 16
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
	setzeZeiten();
anzeigeAktualisieren();
}



static void click_config_provider(void *context) {

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
    }
	if (persist_exists(PERSIST_ZEIT6)) {
	  zeit6h=persist_read_int(PERSIST_ZEIT6);
    }
	if (persist_exists(PERSIST_ZEIT6)) {
	  zeit630h=persist_read_int(PERSIST_ZEIT630);
    }
	if (persist_exists(PERSIST_ZEIT8)) {
	  zeit8h=persist_read_int(PERSIST_ZEIT8);
    }
	if (persist_exists(PERSIST_ZEIT9)) {
	  zeit9h=persist_read_int(PERSIST_ZEIT9);
    }
	if (persist_exists(PERSIST_ZEIT915)) {
	  zeit915h=persist_read_int(PERSIST_ZEIT915);
    }
	if (persist_exists(PERSIST_ZEIT10)) {
	  zeit10h=persist_read_int(PERSIST_ZEIT10);
    }
	
	text_layerStartLabel = text_layer_create(GRect(5, 5, 2*SCREENWIDTH/3, 25));
	text_layer_set_text(text_layerStartLabel,"Start:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layerStartLabel));
	
	text_layerStart = text_layer_create(GRect(2*SCREENWIDTH/3, 5, SCREENWIDTH/3-5, 25));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layerStart));
	text_layer_set_text_alignment(text_layerStart, GTextAlignmentRight);
	
	
	text_layer6Label = text_layer_create(GRect(5,25,2*SCREENWIDTH/3, 45));
	text_layer_set_text(text_layer6Label,"30 min Pause:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer6Label));
	
	text_layer6 = text_layer_create(GRect(2*SCREENWIDTH/3, 25, SCREENWIDTH/3-5, 45));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer6));
	text_layer_set_text_alignment(text_layer6, GTextAlignmentRight);
	
	
	text_layer630Label = text_layer_create(GRect(5,45, 2*SCREENWIDTH/3, 65));
	text_layer_set_text(text_layer630Label,"Pause (Ende):");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer630Label));
	
	text_layer630 = text_layer_create(GRect(2*SCREENWIDTH/3, 45, SCREENWIDTH/3-5, 65));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer630));
	text_layer_set_text_alignment(text_layer630, GTextAlignmentRight);
	
	text_layer8Label = text_layer_create(GRect(5,65, 2*SCREENWIDTH/3, 85));
	text_layer_set_text(text_layer8Label,"8h:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer8Label));
	
	text_layer8 = text_layer_create(GRect(2*SCREENWIDTH/3, 65, SCREENWIDTH/3-5, 85));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer8));
	text_layer_set_text_alignment(text_layer8, GTextAlignmentRight);
	
	text_layer9Label = text_layer_create(GRect(5,85, 2*SCREENWIDTH/3, 105));
	text_layer_set_text(text_layer9Label,"15 min Pause:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer9Label));
	
	text_layer9 = text_layer_create(GRect(2*SCREENWIDTH/3, 85, SCREENWIDTH/3-5, 105));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer9));
	text_layer_set_text_alignment(text_layer9, GTextAlignmentRight);
	
	
	text_layer915Label = text_layer_create(GRect(5,105, 2*SCREENWIDTH/3, 125));
	text_layer_set_text(text_layer915Label,"Pause (Ende):");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer915Label));
	
	text_layer915 = text_layer_create(GRect(2*SCREENWIDTH/3, 105, SCREENWIDTH/3-5, 125));	
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer915));
	text_layer_set_text_alignment(text_layer915, GTextAlignmentRight);
 
	
	text_layer10Label = text_layer_create(GRect(5,125, 2*SCREENWIDTH/3, 145));
	text_layer_set_text(text_layer10Label,"10h:");
 	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer10Label));
	
	text_layer10 = text_layer_create(GRect(2*SCREENWIDTH/3, 125, SCREENWIDTH/3-5, 145));	
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
	persist_write_int(PERSIST_ZEIT6,zeit6h);
	persist_write_int(PERSIST_ZEIT630,zeit630h);
	persist_write_int(PERSIST_ZEIT8,zeit8h);
	persist_write_int(PERSIST_ZEIT9,zeit9h);
	persist_write_int(PERSIST_ZEIT915,zeit915h);
	persist_write_int(PERSIST_ZEIT10,zeit10h); 


	
}

void setzeZeiten(void)
	{
	int h;  
	int hAusgleich1=0; //wird gesetzt, falls Minuten >60 nach 1. Pause
	int hAusgleich2=0; //wird gesetzt, falls Minuten >60 nach 2: Pause
	int m;   // vor der Pause
	int m2;  // nach der 1. Pause
	int m3;  // nach der 2. Pause
	
	startzeit =time(NULL);		
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

	//startzeit=  clock_to_timestamp(TODAY, h, m);	
	
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
