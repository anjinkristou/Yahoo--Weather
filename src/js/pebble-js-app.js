var CLEAR_DAY = 0;
var CLEAR_NIGHT = 1;
var WINDY = 2;
var COLD = 3;
var HOT = 4;
var PARTLY_CLOUDY_DAY = 5;
var PARTLY_CLOUDY_NIGHT = 6;
var FOG = 7;
var RAIN = 8;
var SNOW = 9;
var SLEET = 10;
var SNOW_SLEET = 11;
var RAIN_SLEET = 12;
var RAIN_SNOW = 13;
var CLOUDY = 14;
var STORM = 15;
var NA = 16;
var DRIZZLE = 17;

var imageId = {
  0 : STORM, //tornado
  1 : STORM, //tropical storm
  2 : STORM, //hurricane
  3 : STORM, //severe thunderstorms
  4 : STORM, //thunderstorms
  5 : RAIN_SNOW, //mixed rain and snow
  6 : RAIN_SLEET, //mixed rain and sleet
  7 : SNOW_SLEET, //mixed snow and sleet
  8 : RAIN_SLEET, //freezing drizzle
  9 : DRIZZLE, //drizzle
  10 : RAIN_SLEET, //freezing rain
  11 : RAIN, //showers
  12 : RAIN, //showers
  13 : SNOW, //snow flurries
  14 : SNOW, //light snow showers
  15 : SNOW, //blowing snow
  16 : SNOW, //snow
  17 : SLEET, //hail
  18 : SLEET, //sleet
  19 : FOG, //dust
  20 : FOG, //foggy
  21 : FOG, //haze
  22 : FOG, //smoky
  23 : WINDY, //blustery
  24 : WINDY, //windya
  25 : COLD, //cold
  26 : CLOUDY, //cloudy
  27 : CLOUDY, //mostly cloudy (night)
  28 : CLOUDY, //mostly cloudy (day)
  29 : PARTLY_CLOUDY_NIGHT, //partly cloudy (night)
  30 : PARTLY_CLOUDY_DAY, //partly cloudy (day)
  31 : CLEAR_NIGHT, //clear (night)
  32 : CLEAR_DAY, //sunny
  33 : CLEAR_NIGHT, //fair (night)
  34 : CLEAR_DAY, //fair (day)
  35 : SNOW_SLEET, //mixed rain and hail
  36 : CLEAR_DAY, //hot
  37 : STORM, //isolated thunderstorms
  38 : STORM, //scattered thunderstorms
  39 : STORM, //scattered thunderstorms
  40 : STORM, //scattered showers
  41 : SNOW, //heavy snow
  42 : SNOW, //scattered snow showers
  43 : SNOW, //heavy snow
  44 : CLOUDY, //partly cloudy
  45 : STORM, //thundershowers
  46 : SNOW, //snow showers
  47 : STORM, //isolated thundershowers
  3200 : NA, //not available
};

function windDirectionFromdegrees(degrees) {
    if (348.75 <= degrees && degrees <= 360) {
        return "N";
    } else if (0 <= degrees && degrees <= 11.25) {
        return "N";
    } else if (11.25 < degrees && degrees <= 33.75) {
        return "NNE";
    } else if (33.75 < degrees && degrees <= 56.25) {
        return "NE";
    } else if (56.25 < degrees && degrees <= 78.75) {
        return "ENE";
    } else if (78.75 < degrees && degrees <= 101.25) {
        return "E";
    } else if (101.25 < degrees && degrees <= 123.75) {
        return "ESE";
    } else if (123.75 < degrees && degrees <= 146.25) {
        return "SE";
    } else if (146.25 < degrees && degrees <= 168.75) {
        return "SSE";
    } else if (168.75 < degrees && degrees <= 191.25) {
        return "S";
    } else if (191.25 < degrees && degrees <= 213.75) {
        return "SSW";
    } else if (213.75 < degrees && degrees <= 236.25) {
        return "SW";
    } else if (236.25 < degrees && degrees <= 258.75) {
        return "WSW";
    } else if (258.75 < degrees && degrees <= 281.25) {
        return "W";
    } else if (281.25 < degrees && degrees <= 303.75) {
        return "WNW";
    } else if (303.75 < degrees && degrees <= 326.25) {
        return "NW";
    } else if (326.25 < degrees && degrees < 348.75) {
        return "NNW";
    }
    return "NA";
}

var options = JSON.parse(localStorage.getItem('options'));
//console.log('read options: ' + JSON.stringify(options));
if (options === null) options = { 
                        "language" : "E",
                         "use_gps" : "true",
                         "location" : "",
                         "units" : "celsius",
                         "invert_color" : "false",
                         "vibes_bluetooth" : "false",
                         "vibes_hour" : "false",
                         "use_animation" : "false"
                      };

function getWeatherFromLatLong(latitude, longitude) {
  var response;
  var woeid = -1;
  var key = "67c03fcba28c45e42a816cd7be114d9e"; //my Flickr API key. If you want to reuse this code, please use your own key.
  var req = new XMLHttpRequest();
  var url = "http://api.flickr.com/services/rest/?method=flickr.places.findByLatLon&api_key=" + key + "&lat=" + latitude + "&lon=" + longitude + "&accuracy=16&format=json&nojsoncallback=1";
  req.open('GET', url, true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if (req.status == 200) {
         console.log(req.responseText);
        response = JSON.parse(req.responseText);
        if (response) {
          woeid = response.places.place[0].woeid;
			//Try this for catch the location name
			var city = response.places.place[0].woe_name;
			
			getWeatherFromWoeid(woeid, city);
        }
      } else {
        console.log("Error WFLL");
      }
    }
  };
  req.send(null);
}

function getWeatherFromLocation(location_name) {
  var response;
  var woeid = -1;

   //var query = encodeURI("select woeid from geo.places(1) where text=\"" + location_name + "\"");
  var query = encodeURI("select woeid, name from geo.places(1) where text=\"" + location_name + "\"");
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";
  var req = new XMLHttpRequest();
  req.open('GET', url, true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if (req.status == 200) {
         console.log(req.responseText);
        response = JSON.parse(req.responseText);
        if (response) {
          woeid = response.query.results.place.woeid;
			//Try to get city
			var city = response.query.results.place.name;
          getWeatherFromWoeid(woeid, city);
        }
      } else {
        console.log("Error WFL");
      }
    }
  };
  req.send(null);
}

//function getWeatherFromWoeid(woeid) {
function getWeatherFromWoeid(woeid, city) {
	
	/*if Hong Kong then override the woeid with a valid one*/
	if (woeid ==24865698){woeid=12467924;}
  var celsius = options.units == 'celsius';
	/*Works fine
  var query = encodeURI("select item.condition from weather.forecast where woeid = " + woeid +
                        " and u = " + (celsius ? "\"c\"" : "\"f\""));
						*/
	
	var query = encodeURI("select item.condition, item.forecast, wind from weather.forecast where woeid = " + woeid +
                        " and u = " + (celsius ? "\"c\"" : "\"f\"")+" | truncate(count=1)");
	
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";

  var response;
  var req = new XMLHttpRequest();
   console.log(url);
  req.open('GET', url, true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if (req.status == 200) {
        response = JSON.parse(req.responseText);
        if (response) {
          var condition = response.query.results.channel.item.condition;
          var forecast = response.query.results.channel.item.forecast;
          var wind_record = response.query.results.channel.wind;
          //temperature = condition.temp + (celsius ? "\u00B0C" : "\u00B0F"); //Use this format if you want to display the unit
			var temperature = condition.temp + "\u00B0";
      var icon = imageId[condition.code];
          var wind_speed = Math.round(celsius ? wind_record.speed *1000 /60 /60 : wind_record.speed);
      var wind_direction = windDirectionFromdegrees(wind_record.direction);
      var wind = wind_speed + " " + wind_direction;
			//var inverted == 'B';
			//if (options['color_inverted']=true) {inverted == 'W';}
          console.log("icon: " + icon + " temp: " + temperature + " city: " + city + " wind: " + wind);
          Pebble.sendAppMessage({
            "icon":icon,
            "temperature":temperature,
             "wind": wind,
            //Put here the output parameters to "Main.C"
            "city":city,
            "invert_color" : (options.invert_color == "true" ? 1 : 0),
            "language" : options.language,
            "vibes_bluetooth" : (options.vibes_bluetooth == "true" ? 1 : 0),
            "vibes_hour" : (options.vibes_hour == "true" ? 1 : 0),
            "use_animation" : (options.use_animation == "true" ? 1 : 0),
          });
        }
      } else {
        console.log("Error WFW");
      }
    }
  };
  req.send(null);
}

var locationOptions = { "timeout": 15000, "maximumAge": 60000 };

function updateWeather() {
  if (options.use_gps == "true") {
    window.navigator.geolocation.getCurrentPosition(locationSuccess,
                                                    locationError,
                                                    locationOptions);
  } else {
    getWeatherFromLocation(options.location);
  }
}

function locationSuccess(pos) {
  var coordinates = pos.coords;
  getWeatherFromLatLong(coordinates.latitude, coordinates.longitude);
}

function locationError(err) {
  console.warn('location error (' + err.code + '): ' + err.message);
  Pebble.sendAppMessage({
    "icon":16,
    "temperature":"",
    "wind":""
    //Put here the output parameters to "Main.C"
  });
}

Pebble.addEventListener('showConfiguration', function(e) {
  var uri = 'https://raw.github.com/anjinkristou/Yahoo--WeatherV2/master/src/js/settings.html?' + //Here you need to enter your configuration webservice
    'language=' + encodeURIComponent(options.language) +
	'&use_gps=' + encodeURIComponent(options.use_gps) +
    '&location=' + encodeURIComponent(options.location) +
    '&units=' + encodeURIComponent(options.units) +
    '&invert_color=' + encodeURIComponent(options.invert_color) +
    '&vibes_bluetooth=' + encodeURIComponent(options.vibes_bluetooth) +
    '&vibes_hour=' + encodeURIComponent(options.vibes_hour) +
    '&use_animation=' + encodeURIComponent(options.use_animation);

	//console.log('showing configuration at uri: ' + uri);

  Pebble.openURL(uri);
});

Pebble.addEventListener('webviewclosed', function(e) {
  if (e.response) {
    options = JSON.parse(decodeURIComponent(e.response));
    localStorage.setItem('options', JSON.stringify(options));
    console.log('storing options: ' + JSON.stringify(options));
    updateWeather();
  } else {
    console.log('no options received');
  }
});

//Receive the Pebble's call to refresh the weather info
Pebble.addEventListener("appmessage",
                        function(e) {
                          updateWeather();
                        });

//Initiate the Appsync (This event is called just once)
Pebble.addEventListener("ready", function(e) {
  console.log("connect!" + e.ready);
  updateWeather();

});
