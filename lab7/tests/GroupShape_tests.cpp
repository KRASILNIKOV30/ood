#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../slides/canvas/ICanvas.h"
#include "../slides/canvas/SvgCanvas.h"
#include "../slides/shapes/Ellipse.h"
#include "../slides/shapes/Rectangle.h"
#include "../slides/shapes/Triangle.h"
#include "../slides/groupShape/GroupShape.h"
#include "../slides/point/AreEqual.h"

using Color = uint32_t;

SCENARIO("GroupShape functionality with SVG output")
{
    GIVEN("A GroupShape with several shapes")
	{
		REQUIRE_THROWS_AS(GroupShape({}), std::logic_error);

        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 50}, 0xFF0000, 0x000000);
        std::shared_ptr<IShape> rectangle = std::make_shared<Circle>(Frame{{100, 100}, 200, 150}, 0x00FF00, 0x000000);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{200, 200}, 120, 100}, 0x0000FF, 0x000000);

        GroupShape group({ ellipse, rectangle, triangle });

    	REQUIRE(group.GetShapesCount() == 3);

        WHEN("Getting the frame of the group")
    	{
        	auto [leftTop, width, height] = group.GetFrame();

            THEN("The frame should be calculated based on the minimum and maximum coordinates")
        	{
                REQUIRE(leftTop.x == 0);
                REQUIRE(leftTop.y == 0);
                REQUIRE(width == 320);
                REQUIRE(height == 300);
            }
        }

        WHEN("Adding another shape to the group")
    	{
            std::shared_ptr<IShape> newEllipse = std::make_shared<Ellipse>(Frame{{150, 350}, 50, 50}, 0xFFFF00, 0x000000);
            group.AddShape(newEllipse);

            THEN("The number of shapes in the group should now be 4")
        	{
                REQUIRE(group.GetShapesCount() == 4);
            }

            THEN("The frame of the group should be updated to include the new shape")
        	{
                auto [leftTop, width, height] = group.GetFrame();
                REQUIRE(leftTop.x == 0);
                REQUIRE(leftTop.y == 0);
                REQUIRE(width == 320);
                REQUIRE(height == 400);
            }
        }

        WHEN("Getting a shape by index") {
            THEN("Getting the first shape should return the ellipse")
        	{
                REQUIRE(group.GetShape(0) == ellipse);
            }

            THEN("Getting the second shape should return the rectangle")
        	{
                REQUIRE(group.GetShape(1) == rectangle);
            }

            THEN("Getting the third shape should return the triangle")
        	{
                REQUIRE(group.GetShape(2) == triangle);
            }
        }

        WHEN("Trying to get a shape by an invalid index")
    	{
            THEN("An exception should be thrown when the index is out of bounds") {
                REQUIRE_THROWS_AS(group.GetShape(3), std::out_of_range);
            }
        }

        WHEN("Drawing the group to a stringstream")
    	{
            std::stringstream ss;
            std::shared_ptr<ICanvas> canvas = std::make_shared<SvgCanvas>(ss);
            group.Draw(canvas);

            THEN("The SVG output should match the expected output")
        	{
                std::string expectedSvg =
                	R"(<svg width="1200" height="800" version="1.1" xmlns="http://www.w3.org/2000/svg">
<ellipse cx="50" cy="25" rx="50" ry="25" style="fill:#ff0000;stroke:#000000;stroke-width:1"/>
<polygon points="100,100 300,100 300,250 100,250 " style="fill:#00ff00;stroke:#000000;stroke-width:1"/>
<polygon points="260,200 320,300 200,300 " style="fill:#0000ff;stroke:#000000;stroke-width:1"/>
)";

                REQUIRE(ss.str() == expectedSvg);
            }
        }
    }
}

SCENARIO("GroupShape fill style functionality with color changes")
{
    GIVEN("A GroupShape with several shapes having the same fill color")
	{
        Color commonFillColor = 0xFF0000;
        Color commonLineColor = 0x000000;

        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 50}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> rectangle = std::make_shared<Circle>(Frame{{100, 100}, 200, 150}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{200, 200}, 120, 100}, commonFillColor, commonLineColor);

        GroupShape group({ ellipse, rectangle, triangle });

        WHEN("Checking the fill color of the group")
    	{
            THEN("The fill color should be the same as the individual shapes") {
                std::optional<Color> groupColor = group.GetFillStyle().GetColor();
                REQUIRE(groupColor.has_value());
                REQUIRE(groupColor.value() == commonFillColor);
            }
        }

        WHEN("Changing the fill color of the group via CompositeFillStyle")
    	{
            Color newColor = 0x00FF00;
        	group.GetFillStyle().SetColor(newColor);

            THEN("The fill color of the group should be updated") {
                std::optional<Color> updatedGroupColor = group.GetFillStyle().GetColor();
                REQUIRE(updatedGroupColor.has_value());
                REQUIRE(updatedGroupColor.value() == newColor);
            }

            THEN("All shapes in the group should have the updated fill color") {
                REQUIRE(ellipse->GetFillStyle().GetColor().value() == newColor);
                REQUIRE(rectangle->GetFillStyle().GetColor().value() == newColor);
                REQUIRE(triangle->GetFillStyle().GetColor().value() == newColor);
            }
        }
    }
}

SCENARIO("GroupShape line style updates automatically when new shape with different line style is added", "[GroupShape]")
{
    GIVEN("A GroupShape with several shapes having the same line style")
	{
        Color commonLineColor = 0x000000;
        Color commonFillColor = 0xFF0000;

        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 50}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> rectangle = std::make_shared<Circle>(Frame{{100, 100}, 200, 150}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{200, 200}, 120, 100}, commonFillColor, commonLineColor);

        GroupShape group({ ellipse, rectangle, triangle });

        auto initialGroupLineColor = group.GetLineStyle().GetColor();

        REQUIRE(initialGroupLineColor.has_value());
        REQUIRE(initialGroupLineColor.value() == commonLineColor);
    	REQUIRE(group.GetLineStyle().isEnabled());
    	REQUIRE(group.GetLineStyle().GetLineWidth().value() == 1);

        WHEN("A new shape with a different line style is added to the group")
    	{
            Color newLineColor = 0x00FF00;
            auto newRectangle = std::make_shared<Circle>(Frame{{300, 300}, 100, 50}, commonFillColor, newLineColor);
            group.AddShape(newRectangle);

            THEN("The group's line style should now reflect the new shape's line style")
        	{
                std::optional<Color> updatedGroupLineColor = group.GetLineStyle().GetColor();
                REQUIRE_FALSE(updatedGroupLineColor.has_value());
            }
        }

    	WHEN("Get composite line style")
        {
        	REQUIRE(group.GetLineStyle().GetColor().value() == commonLineColor);

        	AND_WHEN("Add new shape to group")
        	{
        		Color newLineColor = 0x00FF00;
        		auto newRectangle = std::make_shared<Circle>(Frame{{300, 300}, 100, 50}, commonFillColor, newLineColor);
        		newRectangle->GetLineStyle().SetEnabled(false);
        		group.AddShape(newRectangle);

        		THEN("line style updated")
        		{
        			REQUIRE_FALSE(group.GetLineStyle().GetColor().has_value());
        			REQUIRE_FALSE(group.GetLineStyle().isEnabled().has_value());
        		}
        	}
        }
    }
}

SCENARIO("GroupShape correctly resizes and repositions its shapes when SetFrame is called")
{
    GIVEN("A GroupShape with several shapes")
	{
        Frame initialFrame = {{0, 0}, 100, 100};
        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 100}, 0xFF0000, 0x000000);
        std::shared_ptr<IShape> rectangle = std::make_shared<Circle>(Frame{{50, 100}, 150, 100}, 0x00FF00, 0x000000);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{50, 50}, 100, 200}, 0x0000FF, 0x000000);

        GroupShape group({ ellipse, rectangle, triangle });

        WHEN("SetFrame is called to resize and reposition the group")
    	{
            Frame newFrame = {{100, 50}, 200, 400};
            group.SetFrame(newFrame);

            THEN("The shapes within the group should resize and reposition proportionally")
        	{
                Frame ellipseFrame = ellipse->GetFrame();
                Frame rectangleFrame = rectangle->GetFrame();
                Frame triangleFrame = triangle->GetFrame();

                CHECK(AreEqual(ellipseFrame.leftTop.x, 100));
                CHECK(AreEqual(ellipseFrame.leftTop.y, 50));
                CHECK(AreEqual(ellipseFrame.width, 100));
                CHECK(AreEqual(ellipseFrame.height, 160));

                CHECK(AreEqual(rectangleFrame.leftTop.x, 150));
                CHECK(AreEqual(rectangleFrame.leftTop.y, 210));
                CHECK(AreEqual(rectangleFrame.width, 150));
                CHECK(AreEqual(rectangleFrame.height, 160));

                CHECK(AreEqual(triangleFrame.leftTop.x, 150));
                CHECK(AreEqual(triangleFrame.leftTop.y, 130));
                CHECK(AreEqual(triangleFrame.width, 100));
                CHECK(AreEqual(triangleFrame.height, 320));
            }
        }
    }
}

SCENARIO("get group by pointer")
{
	GIVEN("A GroupShape with several shapes")
	{
		std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 50}, 0xFF0000, 0x000000);
		std::shared_ptr<IShape> rectangle = std::make_shared<Circle>(Frame{{100, 100}, 200, 150}, 0x00FF00, 0x000000);
		std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{200, 200}, 120, 100}, 0x0000FF, 0x000000);

		std::shared_ptr<IShape> shape = std::make_shared<GroupShape>(std::initializer_list{ellipse, rectangle, triangle});

		WHEN("get shape")
		{
			auto const group = shape->GetGroup();

			CHECK(group == shape);
		}
	}
}