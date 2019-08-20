#include "Rasterizer.h"
#include "RasterSurface.h"

int main()
{
	//Shaders
	VertexShader = VS_MoveLeft;
	//PixelShader = PS_Red;

	RS_Initialize(RASTER_WIDTH, RASTER_HEIGHT);

	VERTEX_4D tri[6] =
	{
		{ -.9f, .9f, 0.0f, 1, Red, {0.0f,0.0f} },
		{ .9f, 0.9f, 0.0f, 1, Green, {1.0f,0.0f} },
		{.9f, -0.9, 0.0f, 1, Blue, {0.0f,1.0f} },
		{-.9f, -0.9, 0.0f, 1, Blue, {0.0f,1.0f} },
	};

	VERTEX_4D quiz
	{
		 1, 1, 1, 1, 0xFFE86C52 
	};

	while (RS_Update(Raster, NUM_PIXELS))
	{
		SV_Scale = 1.0f;
		VertexShader = nullptr;

		//FillTriange(tri[0], tri[1], tri[2]);
		//FillTriange(tri[3], tri[4], tri[5]);

		VertexShader = nullptr;
		//PixelShader = PS_Castle;
		//PixelShader = PS_Red;

		//Parametric(tri[0], tri[1]);
		//Parametric(tri[1], tri[2]);
		//Parametric(tri[2], tri[3]);
		//Parametric(tri[3], tri[0]);

		//VertexShader = VS_Shrink;
		//PixelShader = nullptr;

		//FillTriange(tri[0], tri[1], tri[2]);

		//Circle(quiz);

		for(int y = 0; y < RASTER_HEIGHT; ++y)
			for (int x = 0; x < RASTER_WIDTH; ++x)
			{
				unsigned int _1_color = _1_Chainsaw_TGA_pixels[Coordinates(x, y, RASTER_WIDTH)];
				unsigned int _3_color = _3_Human_TGA_pixels[Coordinates(x, y, RASTER_HEIGHT)];

				float _1_Blue_Ratio = ((_1_color & 0xFF000000) >> 24) / 255.0f;
				float _3_Blue_Ratio = ((_3_color & 0xFF000000) >> 24) / 255.0f;

				if (_1_Blue_Ratio > _3_Blue_Ratio)
					PlotPixel(x, y, ColorBlend(0x00000000, 0xFFE14A56, _3_Blue_Ratio));
				else
					PlotPixel(x, y, ColorBlend(0x00000000, 0xFF7A09EE, _1_Blue_Ratio));
			}
	}

	RS_Shutdown();
	return 0;
};