# Use Arduino IDE for this code

It works

Look into Python folder to know how to generate letters.

Use settings for WiFi and Server URL.

My server have JSON like this:

```
{
    "BDR": [
        23.95,
        744.88,
        48.44,
        79.69,
        796.93,
        1.14,
        29.21
    ],
    "STR": [
        17.6,
        744.64,
        0.0
    ],
    "updated": {
        "STR": "2022-01-05 11:57",
        "DUST": "2022-01-05 11:58",
        "BDR": "2022-01-05 11:58"
    },
    "FTR": [
        [
            13.26,
            "04d"
        ],
        [
            10.95,
            "04n"
        ],
        [
            7.38,
            "04n"
        ]
    ],
    "ENV": [
        24.450528485421092,
        745.5715801155607,
        41.00942146651297
    ],
    "CPU": [
        0.825,
        22,
        78,
        0.65,
        68.125
    ],
    "DUST": 27
}
```

"FTR" block is a [weather forecast from OpenWeather](https://openweathermap.org/weather-conditions).
