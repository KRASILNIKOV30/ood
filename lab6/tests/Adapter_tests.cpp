#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lib/GraphicsLib.h"
#include "../lib/ModernGraphicsLib.h"
#include "../ModernGraphicsRendererObjectAdapter.h"
#include "../ModernGraphicsRendererClassAdapter.h"
#include "../lib/ShapeDrawingLib.h"

SCENARIO("object adapter tests")
{
	GIVEN("modern renderer")
	{
		std::stringstream ss;
		modern_graphics_lib::ModernGraphicsRenderer renderer(ss);

		WHEN("draw triangle")
		{
			{
				ModernGraphicsRendererObjectAdapter modernCanvas(renderer);
				THEN("adapters start point is (0, 0)")
				{
					renderer.BeginDraw();
					modernCanvas.LineTo(2, 2);
					renderer.EndDraw();
					CHECK(ss.str() == "<draw>\n"
  						"<line fromX=0 fromY=0 toX=2 toY=2/>\n"
  						"  <color r=0 g=0 b=0 a=1 />\n"
  						"</line>\n"
  						"</draw>\n"
  					);
				}
				const shape_drawing_lib::CanvasPainter painter(modernCanvas);
				const shape_drawing_lib::Triangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x0085ff);
				renderer.BeginDraw();
				painter.Draw(triangle);
				renderer.EndDraw();
			}

			THEN("triangle is drawn")
			{
				CHECK(ss.str() == "<draw>\n"
  					"<line fromX=10 fromY=15 toX=100 toY=200/>\n"
  					"  <color r=0 g=0.52 b=1 a=1 />\n"
  					"</line>\n"
  					"<line fromX=100 fromY=200 toX=150 toY=250/>\n"
  					"  <color r=0 g=0.52 b=1 a=1 />\n"
  					"</line>\n"
  					"<line fromX=150 fromY=250 toX=10 toY=15/>\n"
  					"  <color r=0 g=0.52 b=1 a=1 />\n"
  					"</line>\n"
  					"</draw>\n"
				);
			}
		}

		WHEN("draw rectangle")
		{
			{
				ModernGraphicsRendererObjectAdapter modernCanvas(renderer);
				const shape_drawing_lib::CanvasPainter painter(modernCanvas);
				const shape_drawing_lib::Rectangle rect({ 0, 0 }, 20, 10, 0xff00ff);
				renderer.BeginDraw();
				painter.Draw(rect);
				renderer.EndDraw();
			}

			THEN("rectangle is drawn")
			{
				CHECK(ss.str() == "<draw>\n"
					  "<line fromX=0 fromY=0 toX=20 toY=0/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "<line fromX=20 fromY=0 toX=20 toY=10/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "<line fromX=20 fromY=10 toX=0 toY=10/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "<line fromX=0 fromY=10 toX=0 toY=0/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "</draw>\n"
				);
			}
		}
	}
}

SCENARIO("class adapter tests")
{
	GIVEN("modern renderer")
	{
		std::stringstream ss;

		WHEN("draw triangle")
		{
			{
				ModernGraphicsRendererClassAdapter modernCanvas(ss);
				THEN("adapters start point is (0, 0)")
				{
					modernCanvas.BeginDraw();
					modernCanvas.LineTo(2, 2);
					modernCanvas.EndDraw();
					CHECK(ss.str() == "<draw>\n"
  						"<line fromX=0 fromY=0 toX=2 toY=2/>\n"
  						"  <color r=0 g=0 b=0 a=1 />\n"
  						"</line>\n"
  						"</draw>\n"
  					);
				}
				const shape_drawing_lib::CanvasPainter painter(modernCanvas);
				const shape_drawing_lib::Triangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x0085ff);
				modernCanvas.BeginDraw();
				painter.Draw(triangle);
				modernCanvas.EndDraw();
			}

			THEN("triangle is drawn")
			{
				CHECK(ss.str() == "<draw>\n"
  					"<line fromX=10 fromY=15 toX=100 toY=200/>\n"
  					"  <color r=0 g=0.52 b=1 a=1 />\n"
  					"</line>\n"
  					"<line fromX=100 fromY=200 toX=150 toY=250/>\n"
  					"  <color r=0 g=0.52 b=1 a=1 />\n"
  					"</line>\n"
  					"<line fromX=150 fromY=250 toX=10 toY=15/>\n"
  					"  <color r=0 g=0.52 b=1 a=1 />\n"
  					"</line>\n"
  					"</draw>\n"
				);
			}
		}

		WHEN("draw rectangle")
		{
			ModernGraphicsRendererClassAdapter modernCanvas(ss);
			const shape_drawing_lib::CanvasPainter painter(modernCanvas);
			const shape_drawing_lib::Rectangle rect({ 0, 0 }, 20, 10, 0xff00ff);
			modernCanvas.BeginDraw();
			painter.Draw(rect);
			modernCanvas.EndDraw();

			THEN("rectangle is drawn")
			{
				CHECK(ss.str() == "<draw>\n"
					  "<line fromX=0 fromY=0 toX=20 toY=0/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "<line fromX=20 fromY=0 toX=20 toY=10/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "<line fromX=20 fromY=10 toX=0 toY=10/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "<line fromX=0 fromY=10 toX=0 toY=0/>\n"
					  "  <color r=1 g=0 b=1 a=1 />\n"
					  "</line>\n"
					  "</draw>\n"
				);
			}
		}
	}
}