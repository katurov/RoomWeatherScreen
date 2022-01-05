import 	requests
import  io
from    PIL               import Image, ImageDraw, ImageFont
from 	time			  import sleep



def getLocalWeatherIcons ( forecast ) :

	images_array = []

	for grp in forecast :
		try :
			r 	 		= requests.get("http://openweathermap.org/img/wn/{}.png".format(grp[1]))
			icon 		= Image.open( io.BytesIO( r.content ) ).convert("RGBA")
			ready_icon 	= Image.composite(icon, Image.new('RGB', icon.size, 'black'), icon)

			images_array.append([grp[0], ready_icon])
		except :
			images_array.append([grp[0], Image.new('RGB', (50,50), 'black')])

	return images_array


def getLocalWeather () :
	try :
		r = requests.get(url="http://192.168.0.2/json/weather/")
		w = r.json()
	except :
		return (0.00,0.00,0.00,0.00,[[0.00, "01n"],[0.00, "01n"],[0.00, "01n"]])

	try :
		street_temp  = w.get("STR")[0]
	except :
		street_temp  = 0.00

	try :
		bedroom_temp = w.get("BDR")[0]
		bedroom_pres = w.get("BDR")[1]
		bedroom_hum  = w.get("BDR")[2]
	except :
		bedroom_temp = 0.00
		bedroom_pres = 0.00
		bedroom_hum  = 0.00


	try :
		forecast 	 = w.get("FTR")
	except :
		forecast	 = [[0.00, "01n"],[0.00, "01n"],[0.00, "01n"]]

	return (
		street_temp,
		bedroom_temp,
		bedroom_pres,
		bedroom_hum,
		getLocalWeatherIcons ( forecast )
		)


def getLocalWeatherImage ( weather ) :
	global	width, height

	# Load a TTF Font
	bfont = ImageFont.truetype("ModernAntiqua-Regular.ttf", 100)
	mfont = ImageFont.truetype("ModernAntiqua-Regular.ttf", 30)

	image = Image.new("RGB", (width, height))

	# Get drawing object to draw on image.
	draw = ImageDraw.Draw(image)

	# Draw a green filled box as the background
	draw.rectangle((0, 0, width, height), fill=(0, 0, 0))

	street_temp_text = "{:3.1f}".format(weather[0])
	(font_width, font_height) = bfont.getsize(street_temp_text)
	draw.text(
		(width // 2 - font_width // 2, 2),
		street_temp_text,
		font=bfont,
		fill=(255, 255, 0),
	)

	bedroom_temp_text = "{:3.1f}".format(weather[1])
	(font_width, font_height) = bfont.getsize(bedroom_temp_text)
	left_border = width // 2 - font_width // 2
	right_border = left_border + font_width
	draw.text(
		(left_border, height - font_height - 50),
		bedroom_temp_text,
		font=bfont,
		fill=(255, 255, 0),
	)

	bedroom_hum_text = "{:3.1f}%".format(weather[3])
	(font_width, font_height) = mfont.getsize(bedroom_hum_text)
	up_line = height - font_height - 1
	draw.text(
		(right_border - font_width, up_line),
		bedroom_hum_text,
		font=mfont,
		fill=(255, 0, 255),
	)

	bedroom_press_text = "{:3.0f}".format(weather[2])
	(font_width, font_height) = mfont.getsize(bedroom_press_text)
	draw.text(
		(left_border + 2, up_line),
		bedroom_press_text,
		font=mfont,
		fill=(255, 0, 255),
	)

	icon_positions = [22, 95, 168]

	for (i, grp) in enumerate(weather[4]) :
		try :
			image.paste( grp[1] , (icon_positions[i], 95))
		except :
			pass
			
		ft_text = "{:3.0f}".format(grp[0])
		(font_width, font_height) = mfont.getsize(ft_text)
		draw.text(
			(icon_positions[i] + 25 - font_width // 2, 140),
			ft_text,
			font=mfont,
			fill=(255, 0, 255),
		)


	return image





if __name__ == '__main__':

	weather = getLocalWeather ()


	height = 320
	width  = 240
	image  = getLocalWeatherImage ( weather )
	image.save("big.png")


	height = 160
	width  = 128
	image2  = image.resize((width, height))
	image2.save("small.png")


#
#
# WHAT