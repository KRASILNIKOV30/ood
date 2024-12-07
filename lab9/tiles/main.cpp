#include <iostream>
#include "Drawer.h"

constexpr int STAR_COUNT = 20;

Image DrawLandscape() {
	constexpr Size size{1440, 1080};
	Image image{ size, 0xffffff };

	FillRect(image, {0, 0}, size, 0x87CEEB);

	FillRect(image, {0, 800}, {1440, 280}, 0x32CD32);

	FillCircle(image, {1200, 200}, 100, 0xFFFF00);

	FillRect(image, {600, 500}, {400, 300}, 0x8B4513);

	 constexpr Point roofTop = {800, 400};
	DrawLine(image, {600, 500}, roofTop, 0x8B0000);
	DrawLine(image, {1000, 500}, roofTop, 0x8B0000);

	FillRect(image, {700, 550}, {50, 50}, 0xADD8E6);
	FillRect(image, {850, 600}, {100, 100}, 0x654321);

	FillRect(image, {400, 650}, {50, 150}, 0x8B4513);
	FillCircle(image, {425, 600}, 100, 0x228B22);

	FillCircle(image, {375, 550}, 15, 0xFF0000);
	FillCircle(image, {475, 550}, 15, 0xFF0000);
	FillCircle(image, {425, 650}, 15, 0xFF0000);

	DrawCircle(image, {400, 850}, 10, 0xFF0000);
	DrawCircle(image, {600, 880}, 10, 0xFF0000);
	DrawCircle(image, {800, 850}, 10, 0xFF0000);
	DrawCircle(image, {1000, 880}, 10, 0xFF0000);

	DrawCircle(image, {500, 900}, 10, 0x0000FF);
	DrawCircle(image, {700, 910}, 10, 0x0000FF);
	DrawCircle(image, {1100, 920}, 10, 0x0000FF);

	DrawCircle(image, {300, 910}, 10, 0xFFFF00);
	DrawCircle(image, {900, 950}, 10, 0xFFFF00);

	DrawCircle(image, {1200, 950}, 10, 0xFF1493);
	DrawCircle(image, {1100, 800}, 10, 0xFF1493);
	DrawCircle(image, {1300, 870}, 10, 0xFF1493);

	return image;
}


int main()
{
	{
		Image img = LoadImage(
		"                  \n"
			" CCCC             \n"
			"CC  CC   ##    ## \n"
			"CC      ####  ####\n"
			"CC  CC   ##    ## \n"
			" CCCC             \n");
		Print(img, std::cout);
	}

	{
		Save(DrawLandscape(), "landscape.ppm");
	}
}