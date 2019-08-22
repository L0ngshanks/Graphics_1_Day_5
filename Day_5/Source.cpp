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
				VEC_2D uv = { (float)x / RASTER_WIDTH, (float)y / RASTER_HEIGHT };

				float texel_x = uv.x * _1_cave_brownsmall_width;
				float texel_y = uv.y * _1_cave_brownsmall_height;

				unsigned int index = Coordinates(texel_x, texel_y, _1_cave_brownsmall_width);

				unsigned int _upper_blend;
				unsigned int _lower_blend;

				unsigned int _1_color = _1_cave_brownsmall_pixels[index];
				float x_ratio = texel_x -(int)texel_x;
				float y_ratio = texel_y - (int)texel_y;
				
				if (texel_x < _1_cave_brownsmall_width)
				{
					unsigned int _upper_color_1 = _1_cave_brownsmall_pixels[Coordinates(texel_x, texel_y, _1_cave_brownsmall_width)];
					unsigned int _upper_color_2 = _1_cave_brownsmall_pixels[Coordinates(texel_x + 1, texel_y, _1_cave_brownsmall_width)];
					_upper_blend = ColorBlend(_upper_color_1, _upper_color_2, x_ratio);
				}

				if (texel_y < _1_cave_brownsmall_height)
				{
					unsigned int _lower_color_1 = _1_cave_brownsmall_pixels[Coordinates(texel_x + _1_cave_brownsmall_width, texel_y, _1_cave_brownsmall_width)];
					unsigned int _lower_color_2 = _1_cave_brownsmall_pixels[Coordinates(texel_x + _1_cave_brownsmall_width + 1, texel_y, _1_cave_brownsmall_width)];

					_lower_blend = ColorBlend(_lower_color_1, _lower_color_2, x_ratio);
				}

				unsigned int _blended_color = ColorBlend(_upper_blend, _lower_blend, y_ratio);

				//unsigned int _3_color = _3_Human_TGA_pixels[Coordinates(x, y, RASTER_HEIGHT)];

				//float _1_Blue_Ratio = ((_1_color & 0xFF000000) >> 24) / 255.0f;
				//float _3_Blue_Ratio = ((_3_color & 0xFF000000) >> 24) / 255.0f;

				//if (_1_Blue_Ratio > _3_Blue_Ratio)
				//	PlotPixel(x, y, ColorBlend(0x00000000, 0xFFE14A56, _3_Blue_Ratio));
				//else
				//	PlotPixel(x, y, ColorBlend(0x00000000, 0xFF7A09EE, _1_Blue_Ratio));

				unsigned int _ul_color = 0.0f;
				PlotPixel(x, y, ColorShift(_blended_color));
			}
	}

	RS_Shutdown();
	return 0;
};