//Declare and Import references
#include "pebble.h"
#include "pebble_fonts.h"
#include "translate.h"


//UIDs:
//English: 35a28a4d-0c9f-408f-9c6d-551e65f03186
//Spanish: 3ab59c04-142f-4ff1-b90d-aab93ce54a32
//Italian: 6279f406-1114-4b2f-852d-65b0e8ff2a73

//Screen Resolution: 144 x 168 pixels

#define WEEKDAY_FRAME    (GRect(5, 2, 102, 23)) //,,95,
#define BATT_FRAME       (GRect(103, 4, 40, 22)) //98,,
#define BT_FRAME         (GRect(127, 4, 23, 22))
#define TIME_FRAME       (GRect(0, 15, 144, 152))
#define DATE_FRAME       (GRect(1, 69, 143, 20))
/*
#define MAX_FRAME (GRect(65, 90, 40, 23))
#define MIN_FRAME (GRect(105, 90, 40, 23))
*/

#define LAST_UPDATE_FRAME (GRect(110, 148, 34, 23))
#define LOCATION_FRAME    (GRect(1, 148, 110, 23))
#define WEATHER_FRAME     (GRect(1, 90, 60, 60))
#define WEATHER_HIDDEN_FRAME     (GRect(-70, 90, 60, 60))
#define TEMPERATURE_FRAME (GRect(65, 95, 40, 25))
#define TEMPERATURE_HL_FRAME (GRect(105, 98, 40, 25))
#define WIND_FRAME        (GRect(65, 120, 82, 25))

#define INVERTER_FRAME    (GRect(0,0,144,168))

//******************//
// DEFINE THE ICONS //
//******************//

static const uint32_t WEATHER_ICONS[] = {
    RESOURCE_ID_ICON_CLEAR_DAY,
    RESOURCE_ID_ICON_CLEAR_NIGHT,
    RESOURCE_ID_ICON_WIND,
    RESOURCE_ID_ICON_COLD,
    RESOURCE_ID_ICON_HOT,
    RESOURCE_ID_ICON_PARTLY_CLOUDY_DAY,
    RESOURCE_ID_ICON_PARTLY_CLOUDY_NIGHT,
    RESOURCE_ID_ICON_FOG,
    RESOURCE_ID_ICON_RAIN,
    RESOURCE_ID_ICON_SNOW,
    RESOURCE_ID_ICON_SLEET,
    RESOURCE_ID_ICON_SNOW_SLEET,
    RESOURCE_ID_ICON_RAIN_SLEET,
    RESOURCE_ID_ICON_RAIN_SNOW,
    RESOURCE_ID_ICON_CLOUDY,
    RESOURCE_ID_ICON_THUNDER,
    RESOURCE_ID_ICON_NOT_AVAILABLE,
    RESOURCE_ID_ICON_DRIZZLE,
};

//*************//
// Define KEYS //
//*************//


enum WeatherKey {
    WEATHER_ICON_KEY = 0x0,        // TUPLE_INT
    WEATHER_TEMPERATURE_KEY = 0x1, // TUPLE_CSTRING
    WEATHER_CITY_KEY = 0x2,        //	TUPLE_CSTRING
    INVERT_COLOR_KEY = 0x3,  		   // TUPLE_CSTRING
    LANGUAGE_KEY = 0x4, 			     // TUPLE_CSTRING
    WEATHER_WIND_KEY = 0x5, 			 // TUPLE_CSTRING
    VIBES_BLUETOOTH_KEY = 0x6, 		 // TUPLE_CSTRING
    USE_ANIMATION_KEY = 0x7, 			 // TUPLE_CSTRING
    VIBES_HOUR_KEY = 0x8, 			   // TUPLE_CSTRING
    VIBES_HOUR_START_KEY = 0x9, 	 // TUPLE_CSTRING
    VIBES_HOUR_END_KEY = 0xA, 		 // TUPLE_CSTRING
    WEATHER_TEMPERATURE_HL_KEY = 0xB, // TUPLE_CSTRING
};

typedef struct setting_t {
    int weather_icon_code;
    bool color_inverted;
    bool vibes_bluetooth;
    bool batt_status; //If true, display the battery status all the time; if false, just when running low (<10%)
    bool use_animation;
    bool vibes_hour;
    int vibes_hour_start;
    int vibes_hour_end;
} settings_t;

settings_t settings = {
    .weather_icon_code = 0,
    .color_inverted = false,
    .vibes_bluetooth = true,
    .batt_status = true, //If true, display the battery status all the time; if false, just when running low (<10%)
    .use_animation = true,
    .vibes_hour = false,
    .vibes_hour_start = 8,
    .vibes_hour_end = 20
};

//Declare initial window
Window *my_window;

//Define the layers
TextLayer *date_layer;                 // Layer for the date
TextLayer *Time_Layer;                         // Layer for the time
TextLayer *Weekday_Layer;                 //Layer for the weekday
TextLayer *Last_Update;                 // Layer for the last update
TextLayer *Location_Layer;                 // Layer for the last update
TextLayer *Batt_Layer;                        //Layer for the BT connection
TextLayer *BT_Layer;                        //Layer for the BT connection
TextLayer *Temperature_Layer;        //Layer for the Temperature
TextLayer *Temperature_hl_Layer;        //Layer for the Temperature
TextLayer *Wind_Layer;        //Layer for the Temperature

InverterLayer *inverter_layer;

static bool is_accel_stoped = false;

static GBitmap *BT_image;
static BitmapLayer *BT_icon_layer; //Layer for the BT connection

static GBitmap *Batt_image;
static BitmapLayer *Batt_icon_layer; //Layer for the Battery status

static GBitmap *weather_image;
static BitmapLayer *weather_icon_layer; //Layer for the weather info

//Define annimations
static PropertyAnimation *weather_animation_in;
static PropertyAnimation *weather_animation_out;
static GRect weather_from_rect;
static GRect weather_to_rect;


//Define and initialize variables
//FONTS
GFont font_date; // Font for date
GFont font_time; // Font for time
GFont font_update; // Font for last update
GFont font_temperature;        // Font for the temperature
GFont font_wind;        // Font for the wind

//Vibe Control
bool BTConnected = true;

//Time control for weather refresh
static AppTimer *timer;
static AppTimer *accel_start = NULL;
const uint32_t timeout_ms = 1800000; //30min (1min = 60000)

//Date & Time
static char last_update[]="00:00 ";

static char weekday_text[] = "XXXXXXXXXXXX";
static char month_text[] = "XXXXXXXXXXXXX";
static char day_text[] = "31";
static char day_month[]= "31 SEPTEMBER";
static char time_text[] = "00:00";

bool translate_sp = true;
static char language[] = "0"; 	//"0" = English //"E" = Spanish // "I" = Italian // "G" = German
// "C" = Czech // "F" = French // "P" = Portuguese // "X" = Finnish // "D" = Dutch
//"1" = Polish // "S" = Swedish // "2" = Danish //"3" = Catalan

static void send_cmd(void);

//**************************************************//
// Helper function to distroy a property annimation //
//**************************************************//

void destroy_property_animation(PropertyAnimation **prop_animation) {
    if (*prop_animation == NULL) {
        return;
    }
    if (animation_is_scheduled((Animation*) *prop_animation)) {
        animation_unschedule((Animation*) *prop_animation);
    }
    property_animation_destroy(*prop_animation);
    *prop_animation = NULL;
}

void weather_animation_started(Animation *animation, void *data) {
	(void)animation;
	(void)data;
}

void weather_animation_stopped(Animation *animation, void *data) {
	(void)animation;
	(void)data;

  if (weather_image) {gbitmap_destroy(weather_image);}
  weather_image = gbitmap_create_with_resource(WEATHER_ICONS[settings.weather_icon_code]);
	bitmap_layer_set_bitmap(weather_icon_layer, weather_image);

	destroy_property_animation(&weather_animation_in);

	weather_animation_in = property_animation_create_layer_frame(bitmap_layer_get_layer(weather_icon_layer), &weather_to_rect, &weather_from_rect);
	animation_set_duration((Animation*)weather_animation_in, 500);

	animation_set_curve((Animation*)weather_animation_in,AnimationCurveEaseOut);
	animation_schedule((Animation*)weather_animation_in);
}


//**************************//
// Check the Battery Status //
//**************************//

static void handle_battery(BatteryChargeState charge_state) {
    //static char battery_text[] = "100%";

    //kill previous batt_image to avoid invalid ones.
    if (Batt_image) {gbitmap_destroy(Batt_image);}
    bitmap_layer_set_bitmap(Batt_icon_layer, NULL);

    if (charge_state.is_charging) {
        //snprintf(battery_text, sizeof(battery_text), "charging");
        Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_CHAR);
        bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
    } else {
        //snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);


        //WHILE RUNNING LOW, BATT STATUS WILL ALWAYS DISPLAY
        //set the new batt_image
        //DO NOT display the batt_icon all the time. it is annoying.
        if (charge_state.charge_percent <=10) //If the charge is between 0% and 10%
        {
            Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_EMPTY);
            bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
        }
        //CHECK IF BATTERY STATUS SHOULD DISPLAY ALL THE TIME OR JUST WHILE RUNNING LOW
        else if (settings.batt_status){
            if (charge_state.charge_percent <=20) //If the charge is between 10% and 20%
            {
                Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_20);
                bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
            }

            else if (charge_state.charge_percent <=40) //If the charge is between 20% and 40%
            {
                Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_40);
                bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
            }

            else if (charge_state.charge_percent <=60) //If the charge is between 40% and 60%
            {
                Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_60);
                bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
            }

            else if (charge_state.charge_percent <=80) //If the charge is between 60% and 80%
            {
                Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_80);
                bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
            }

            else if (charge_state.charge_percent >80) //If the charge is between 80% and 100%
            {
                Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_FULL);
                bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
            }

        }

    }
    //text_layer_set_text(Batt_Layer, battery_text);
}

static void accel_starting(void *data) {
	app_log(APP_LOG_LEVEL_DEBUG, __FILE__, __LINE__, "accel_starting");
	is_accel_stoped = false;
	accel_start = NULL;
}

static void vibes_bluetooth()
{
    //************************//
    // Vibes on disconnection //
    //************************//
  
    if(!settings.vibes_bluetooth) return;
  
  is_accel_stoped = true;
  accel_start = NULL;
  accel_start = app_timer_register(2000, &accel_starting, NULL);

    //Vibes on connection
    if (BTConnected == false){
        if (bluetooth_connection_service_peek() == true){
            //Vibes to alert connection
            vibes_double_pulse();
            BTConnected = true;
        }
    }

    //Vibes on disconnect
    if (BTConnected == true){
        //Vibes to alert disconnection
        if (bluetooth_connection_service_peek()== false){
            vibes_long_pulse();
            BTConnected = false;
        }
    }

}

//******************************//
// Handle Bluetooth Connection //
//*****************************//
static void handle_bluetooth(bool connected)
{
    //text_layer_set_text(BT_Layer, connected ? "C" : "D");

    //draw the BT icon if connected
    if(connected ==true)
    {
        if (BT_image) {gbitmap_destroy(BT_image);}
        BT_image = gbitmap_create_with_resource(RESOURCE_ID_BT_CONNECTED);
        bitmap_layer_set_bitmap(BT_icon_layer, BT_image);
        if (BTConnected == false){
            //setup the timer to catch false disconnections (5 secs)
            timer = app_timer_register(5000, vibes_bluetooth, NULL);
        }

    }
    else
    {
        //Kill the previous image
        if (BT_image) {gbitmap_destroy(BT_image);}
        bitmap_layer_set_bitmap(BT_icon_layer, NULL);
        if (BTConnected == true){
            //setup the timer to catch false disconnections (5 secs)
            timer = app_timer_register(5000, vibes_bluetooth, NULL);
        }

    }




} //handle_bluetooth

//**************************//
//** Handle accel **//
//**************************//

void accel_tap_handler(AccelAxisType axis, int32_t direction){
	if (is_accel_stoped == false){
    //Refresh the weather
    send_cmd();
	} else {

	}
}

//**************************//
//** Get the current date **//
//**************************//
void getDate()
{

    //Get the date
    time_t actualPtr = time(NULL);
    struct tm *tz1Ptr = gmtime(&actualPtr);

    //Get the Weekday
    strftime(weekday_text,sizeof(weekday_text),"%A",tz1Ptr);
    //Get the Month + Day (English format)
    strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);
    //Get the Day + Month (Spanish format)
    strftime(day_month,sizeof(day_month),"%e %B",tz1Ptr);


    if(language[0] != '0'){
        //Get the Month
        strftime(month_text,sizeof(month_text),"%B",tz1Ptr);
        //Get the day
        strftime(day_text,sizeof(day_text),"%e",tz1Ptr);
        //Translate to Spanish
        translate_sp = TranslateDate(language[0], month_text, weekday_text);

        if(translate_sp){
            //Concatenate the day to the month
            //If Czech the month is before day
            if (language[0] == 'C'){strncat(month_text,day_text,strlen(day_text));}
            else {memcpy(&month_text, day_text, strlen(day_text));}
        }
        else{
            //Keep the Month + Day (English format)
            strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);
        }
    }


    text_layer_set_text(date_layer, month_text);
    text_layer_set_text(Weekday_Layer, weekday_text); //Update the weekday layer

}



//*****************//
// AppSync options //
//*****************//

static AppSync sync;
static uint8_t sync_buffer[256];

static void sync_tuple_changed_callback(const uint32_t key,
                                        const Tuple* new_tuple,
                                        const Tuple* old_tuple,
                                        void* context) {


    // App Sync keeps new_tuple in sync_buffer, so we may use it directly
    switch (key) {
      case WEATHER_ICON_KEY:{
        //if (weather_image) {gbitmap_destroy(weather_image);}

        //weather_image = gbitmap_create_with_resource(WEATHER_ICONS[new_tuple->value->uint8]);
        //bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
        //persist_write_int(WEATHER_ICON_KEY, new_tuple->value->uint8);
        settings.weather_icon_code = new_tuple->value->uint8;
      if(settings.use_animation){
        destroy_property_animation(&weather_animation_out);
        weather_animation_out = property_animation_create_layer_frame(bitmap_layer_get_layer(weather_icon_layer), &weather_from_rect, &weather_to_rect);
        animation_set_duration((Animation*)weather_animation_out, 500);  
        animation_set_curve((Animation*)weather_animation_out,AnimationCurveEaseOut);
        animation_set_handlers((Animation*)weather_animation_out, (AnimationHandlers) {
      		.started = (AnimationStartedHandler) weather_animation_started,
      		.stopped = (AnimationStoppedHandler) weather_animation_stopped
      	}, 0);
      
        animation_schedule((Animation*)weather_animation_out);
      }else{
        if (weather_image) {gbitmap_destroy(weather_image);}
        weather_image = gbitmap_create_with_resource(WEATHER_ICONS[new_tuple->value->uint8]);
        bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
      }
      }break;

      case WEATHER_TEMPERATURE_KEY:{
        //Update the temperature
        text_layer_set_text(Temperature_Layer, new_tuple->value->cstring);
        //Set the time on which weather was retrived
        memcpy(&last_update, time_text, strlen(time_text));
        text_layer_set_text(Last_Update, last_update);
      }break;
      
      case WEATHER_TEMPERATURE_HL_KEY:{
        //Update the temperature
        text_layer_set_text(Temperature_hl_Layer, new_tuple->value->cstring);
      }break;

      case WEATHER_WIND_KEY:{
        //Update the wind
        //text_layer_set_text(Wind_Layer, new_tuple->value->cstring);
        text_layer_set_text(Wind_Layer, new_tuple->value->cstring);
      }break;

      case WEATHER_CITY_KEY:{
        text_layer_set_text(Location_Layer, new_tuple->value->cstring);
      }break;

      case INVERT_COLOR_KEY:{
        settings.color_inverted = new_tuple->value->uint8 != 0;
        persist_write_bool(INVERT_COLOR_KEY, settings.color_inverted);

        layer_set_hidden((Layer*)inverter_layer, !settings.color_inverted);

      }break;
      case VIBES_BLUETOOTH_KEY:{
        settings.vibes_bluetooth = new_tuple->value->uint8 != 0;
        persist_write_bool(VIBES_BLUETOOTH_KEY, settings.vibes_bluetooth);
      }break;
      
      case VIBES_HOUR_KEY:{
        settings.vibes_hour = new_tuple->value->uint8 != 0;
        persist_write_bool(VIBES_HOUR_KEY, settings.vibes_hour);
      }break;
      
      case VIBES_HOUR_START_KEY:{
        settings.vibes_hour_start = new_tuple->value->uint8;
        persist_write_bool(VIBES_HOUR_START_KEY, settings.vibes_hour_start);
      }break;
      
      case VIBES_HOUR_END_KEY:{
        settings.vibes_hour_end = new_tuple->value->uint8;
        persist_write_bool(VIBES_HOUR_END_KEY, settings.vibes_hour_end);
      }break;
      
      case USE_ANIMATION_KEY:{
        settings.use_animation = new_tuple->value->uint8 != 0;
        persist_write_bool(USE_ANIMATION_KEY, settings.use_animation);
      }break;

      case LANGUAGE_KEY:{
        memcpy(&language, new_tuple->value->cstring, strlen(new_tuple->value->cstring));
        persist_write_bool(LANGUAGE_KEY, new_tuple->value->cstring);
        //Init the date
        getDate();
      }break;
    }
}


//************************//
// Capture the Tick event //
//************************//
void handle_tick(struct tm *tick_time, TimeUnits units_changed)
{
    if (units_changed & MINUTE_UNIT)
    {
        //Format the time
        if (clock_is_24h_style())
        {
            strftime(time_text, sizeof(time_text), "%H:%M", tick_time);
        }
        else
        {
            strftime(time_text, sizeof(time_text), "%I:%M", tick_time);
        }


        text_layer_set_text(Time_Layer, time_text);

        //Check Battery Status
        handle_battery(battery_state_service_peek());

        //Check BT Status
        handle_bluetooth(bluetooth_connection_service_peek());
      
      if(settings.vibes_hour && 
         tick_time->tm_hour >= settings.vibes_hour_start &&
         tick_time->tm_hour <= settings.vibes_hour_end &&
         tick_time->tm_min == 0){
          //Vibes to alert hour
            vibes_short_pulse();
      }

    } //MINUTE CHANGES
    if (units_changed & DAY_UNIT){
        //Update the date
        getDate();}


} //HANDLE_TICK


//************************************************//
// TIMER to refresh the weather data every 30 min //
//************************************************//
static void send_cmd(void) {
    //Tuplet value = TupletInteger(1, 1);
    Tuplet value = TupletCString(WEATHER_CITY_KEY,"loading...");

    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    if (iter == NULL) {
        return;
    }

    dict_write_tuplet(iter, &value);
    dict_write_end(iter);

    app_message_outbox_send();

    //JavaScript call is broken after 2h. Not sure if that is because lack of memory or Pebble App is breaking this.
    //Check that weather info is updated, and close the AppMessage and create a new session if not.
}

static void timer_callback(void *context) {

    //Developer vibe: confirm that timer is not killed
    //vibes_double_pulse();

    timer = app_timer_register(timeout_ms, timer_callback, NULL);

    //Refresh the weather
    send_cmd();


}


//****************************//
// Initialize the application //
//****************************//

void handle_init(void)
{
    //Define Resources
    ResHandle res_d;
    ResHandle res_u;
    ResHandle res_t;
    ResHandle res_temp;
    ResHandle res_wind;


    // Setup messaging
    const int inbound_size = 256;
    const int outbound_size = 256;

    app_message_open(inbound_size, outbound_size);

    Tuplet initial_values[] = {
        TupletInteger(WEATHER_ICON_KEY, (uint8_t) 16), //INITIALIZE TO "N/A"
        TupletCString(WEATHER_TEMPERATURE_KEY, ""),
        TupletCString(WEATHER_TEMPERATURE_HL_KEY, ""),
        TupletCString(WEATHER_CITY_KEY, ""),
        TupletInteger(INVERT_COLOR_KEY, persist_read_bool(INVERT_COLOR_KEY)),
        TupletInteger(VIBES_BLUETOOTH_KEY, persist_read_bool(VIBES_BLUETOOTH_KEY)),
        TupletInteger(VIBES_HOUR_KEY, persist_read_bool(VIBES_HOUR_KEY)),
        TupletInteger(VIBES_HOUR_START_KEY, persist_read_bool(VIBES_HOUR_START_KEY)),
        TupletInteger(VIBES_HOUR_END_KEY, persist_read_bool(VIBES_HOUR_END_KEY)),
        TupletInteger(USE_ANIMATION_KEY, persist_read_bool(USE_ANIMATION_KEY)),
        TupletCString(LANGUAGE_KEY, "0"),
        TupletCString(WEATHER_WIND_KEY, ""),
    }; //TUPLET INITIAL VALUES

    app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values,
                  ARRAY_LENGTH(initial_values), sync_tuple_changed_callback,
                  NULL, NULL);

    //load persistent storage options
    settings.color_inverted = persist_read_bool(INVERT_COLOR_KEY);
    settings.vibes_bluetooth = persist_read_bool(VIBES_BLUETOOTH_KEY);
    settings.vibes_hour = persist_read_bool(VIBES_HOUR_KEY);
    settings.vibes_hour_start = persist_read_bool(VIBES_HOUR_START_KEY);
    settings.vibes_hour_end = persist_read_bool(VIBES_HOUR_END_KEY);
    settings.use_animation = persist_read_bool(USE_ANIMATION_KEY);
    persist_read_string(LANGUAGE_KEY, language, sizeof(language));

    //Init the date
    //getDate();

    //Create the main window
    my_window = window_create();
    window_stack_push(my_window, true /* Animated */);
    //Define the Black vs. White layout
    window_set_background_color(my_window, GColorBlack);
  
  //set the weather frame start and end animation positions
   weather_from_rect = WEATHER_FRAME;
   weather_to_rect = WEATHER_HIDDEN_FRAME;



    //Load the custom fonts
    res_t = resource_get_handle(RESOURCE_ID_FUTURA_CONDENSED_53); // Time font
    res_d = resource_get_handle(RESOURCE_ID_FUTURA_17); // Date font
    res_u = resource_get_handle(RESOURCE_ID_FUTURA_10); // Last Update font
    res_temp = resource_get_handle(RESOURCE_ID_FUTURA_24); //Temperature
    res_wind = resource_get_handle(RESOURCE_ID_FUTURA_18); //Temperature


    font_date = fonts_load_custom_font(res_d);
    font_update = fonts_load_custom_font(res_u);
    font_time = fonts_load_custom_font(res_t);
    font_temperature = fonts_load_custom_font(res_temp);
    font_wind = fonts_load_custom_font(res_wind);
    //font_temperature = fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT);


    //LOAD THE LAYERS
    //Display the Weekday layer
    Weekday_Layer = text_layer_create(WEEKDAY_FRAME);

    text_layer_set_text_color(Weekday_Layer, GColorWhite);

    text_layer_set_background_color(Weekday_Layer, GColorClear);
    text_layer_set_font(Weekday_Layer, font_date);
    text_layer_set_text_alignment(Weekday_Layer, GTextAlignmentLeft);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Weekday_Layer));

    //Display the Batt layer
    Batt_icon_layer = bitmap_layer_create(BATT_FRAME);
    bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(Batt_icon_layer));

    //Display the BT layer
    BT_icon_layer = bitmap_layer_create(BT_FRAME);
    bitmap_layer_set_bitmap(BT_icon_layer, BT_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(BT_icon_layer));

    //Display the Time layer
    Time_Layer = text_layer_create(TIME_FRAME);

    text_layer_set_text_color(Time_Layer, GColorWhite);

    text_layer_set_background_color(Time_Layer, GColorClear);
    text_layer_set_font(Time_Layer, font_time);
    text_layer_set_text_alignment(Time_Layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Time_Layer));

    //Display the Date layer
    date_layer = text_layer_create(DATE_FRAME);

    text_layer_set_text_color(date_layer, GColorWhite);
    
    text_layer_set_background_color(date_layer, GColorClear);
    text_layer_set_font(date_layer, font_date);
    text_layer_set_text_alignment(date_layer, GTextAlignmentRight);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(date_layer));

    //Display the Weather layer
    weather_icon_layer = bitmap_layer_create(WEATHER_FRAME);
    bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(weather_icon_layer));

    //Display the Temperature layer
    Temperature_Layer = text_layer_create(TEMPERATURE_FRAME);

    text_layer_set_text_color(Temperature_Layer, GColorWhite);

    text_layer_set_background_color(Temperature_Layer, GColorClear);
    text_layer_set_font(Temperature_Layer, font_temperature);
    text_layer_set_text_alignment(Temperature_Layer, GTextAlignmentRight);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Temperature_Layer));
  
    //Display the Temperature layer
    Temperature_hl_Layer = text_layer_create(TEMPERATURE_HL_FRAME);

    text_layer_set_text_color(Temperature_hl_Layer, GColorWhite);

    text_layer_set_background_color(Temperature_hl_Layer, GColorClear);
    text_layer_set_font(Temperature_hl_Layer, font_update);
    text_layer_set_text_alignment(Temperature_hl_Layer, GTextAlignmentLeft);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Temperature_hl_Layer));

    //Display the Wind layer
    Wind_Layer = text_layer_create(WIND_FRAME);

    text_layer_set_text_color(Wind_Layer, GColorWhite);

    text_layer_set_background_color(Wind_Layer, GColorClear);
    text_layer_set_font(Wind_Layer, font_wind);
    text_layer_set_text_alignment(Wind_Layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Wind_Layer));

    //Display the Location layer
    Location_Layer = text_layer_create(LOCATION_FRAME);

    text_layer_set_text_color(Location_Layer, GColorWhite);

    text_layer_set_background_color(Location_Layer, GColorClear);
    text_layer_set_font(Location_Layer, font_update);
    text_layer_set_text_alignment(Location_Layer, GTextAlignmentRight);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Location_Layer));

    //Display the Last Update layer
    Last_Update = text_layer_create(LAST_UPDATE_FRAME);

    text_layer_set_text_color(Last_Update, GColorWhite);

    text_layer_set_background_color(Last_Update, GColorClear);
    text_layer_set_font(Last_Update, font_update);
    text_layer_set_text_alignment(Last_Update, GTextAlignmentRight);
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Last_Update));

    inverter_layer = inverter_layer_create(INVERTER_FRAME);
    layer_add_child(window_get_root_layer(my_window),(Layer*)inverter_layer);
    layer_set_hidden((Layer*)inverter_layer, !settings.color_inverted);
    /*

         // Setup messaging
                const int inbound_size = 64;
                const int outbound_size = 64;
                app_message_open(inbound_size, outbound_size);

                Tuplet initial_values[] = {
                TupletInteger(WEATHER_ICON_KEY, (uint8_t) 16), //INITIALIZE TO "N/A"
                TupletCString(WEATHER_TEMPERATURE_KEY, ""),
                TupletCString(WEATHER_CITY_KEY, ""),
                TupleCstring (COLOR_INVERTED_KEY,""),

                }; //TUPLET INITIAL VALUES

                 app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values,
                ARRAY_LENGTH(initial_values), sync_tuple_changed_callback,
                NULL, NULL);
    */

    // Ensures time is displayed immediately (will break if NULL tick event accessed).
    // (This is why it's a good idea to have a separate routine to do the update itself.)

    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    handle_tick(current_time, MINUTE_UNIT);
    tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);

    //Enable the Battery check event
    battery_state_service_subscribe(&handle_battery);
    //Enable the Bluetooth check event
    bluetooth_connection_service_subscribe(&handle_bluetooth);

    //setup the timer to refresh the weather info every 30min
    //const uint32_t timeout_ms = 1800000;
    timer = app_timer_register(timeout_ms, timer_callback, NULL);
  
    //
    accel_tap_service_subscribe(accel_tap_handler);

} //HANDLE_INIT



//**********************//
// Kill the application //
//**********************//
void handle_deinit(void)
{
    //text_layer_destroy(text_layer);

    //Unsuscribe services
    tick_timer_service_unsubscribe();
    battery_state_service_unsubscribe();
    bluetooth_connection_service_unsubscribe();
    accel_tap_service_unsubscribe();

    //if (BT_image){gbitmap_destroy(BT_image);}
    //if (Batt_image){gbitmap_destroy(Batt_image);}
    //if (weather_image){gbitmap_destroy(weather_image);}

    //Deallocate layers
    text_layer_destroy(Time_Layer);
    text_layer_destroy(date_layer);
    text_layer_destroy(Weekday_Layer);
    text_layer_destroy(Temperature_Layer);
    text_layer_destroy(Temperature_hl_Layer);
    text_layer_destroy(Wind_Layer);
    text_layer_destroy(Location_Layer);
    text_layer_destroy(Last_Update);

    inverter_layer_destroy(inverter_layer);

    //Deallocate custom fonts
    fonts_unload_custom_font(font_date);
    fonts_unload_custom_font(font_update);
    fonts_unload_custom_font(font_time);
    fonts_unload_custom_font(font_temperature);
    fonts_unload_custom_font(font_wind);

    //Deallocate the main window
    window_destroy(my_window);

} //HANDLE_DEINIT


//*************//
// ENTRY POINT //
//*************//
int main(void)
{
    handle_init();
    app_event_loop();
    handle_deinit();
}
