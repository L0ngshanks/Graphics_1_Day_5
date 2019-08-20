#include "Rasterizer.h"
#include "RasterSurface.h"

int main()
{
	//Shaders
	VertexShader = VS_MoveLeft;
	PixelShader = PS_Red;

	RS_Initialize(RASTER_WIDTH, RASTER_HEIGHT);

	VERTEX_4D tri[3] =
	{
		{ 0.2f, -0.8f, 0.5f, 1, Red },
		{ -.2f, 0.9f, 0.5f, 1, Green },
		{0.92f, -0.04, 0.5f, 1, Blue}
	};

	VERTEX_4D quiz
	{
		 1, 1, 1, 1, 0xFFE86C52 
	};

	while (RS_Update(Raster, NUM_PIXELS))
	{
		SV_Scale = 0.6f;
		VertexShader = VS_MoveLeft;;
		PixelShader = nullptr;

		FillTriange(tri[0], tri[1], tri[2]);

		VertexShader = VS_MoveLeft;
		PixelShader = PS_Red;

		Parametric(tri[0], tri[1]);
		Parametric(tri[1], tri[2]);
		Parametric(tri[2], tri[0]);

		VertexShader = VS_Shrink;
		PixelShader = nullptr;

		FillTriange(tri[0], tri[1], tri[2]);

		//Circle(quiz);
	}

	RS_Shutdown();
	return 0;
};