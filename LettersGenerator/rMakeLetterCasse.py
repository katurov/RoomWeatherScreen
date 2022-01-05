import  io
from    PIL               import Image, ImageDraw, ImageFont


if __name__ == '__main__':
	bfont = ImageFont.truetype("ModernAntiqua-Regular.ttf", 100)
	mfont = ImageFont.truetype("ModernAntiqua-Regular.ttf", 30)

	(f_width, f_height) = bfont.getsize( '-01234567890.%' )
	for x in '-01234567890.' :
		(width, height) = bfont.getsize( x )
		image = Image.new("RGB", (width, f_height))
		draw = ImageDraw.Draw(image)
		draw.rectangle((0, 0, width, f_height), fill=(0, 0, 0))
		draw.text( (0, f_height - height), x, font=bfont, fill=(255, 255, 0) )
		image.save("b{}.png".format(x))

	(f_width, f_height) = mfont.getsize( '-01234567890.%' )
	for x in '-01234567890.%' :
		(width, height) = mfont.getsize( x )
		image = Image.new("RGB", (width, f_height))
		draw = ImageDraw.Draw(image)
		draw.rectangle((0, 0, width, f_height), fill=(0, 0, 0))
		draw.text( (0, f_height - height), x, font=mfont, fill=(255, 0, 255) )
		image.save("m{}.png".format(x))


#
#
# WHAT by katurov@gmail.com