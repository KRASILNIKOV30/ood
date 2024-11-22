#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../slides/canvas/ICanvas.h"
#include "../slides/canvas/SvgCanvas.h"
#include "../slides/shapes/Ellipse.h"
#include "../slides/shapes/Rectangle.h"
#include "../slides/shapes/Triangle.h"
#include "../slides/groupShape/GroupShape.h"

using Color = uint32_t;

SCENARIO("GroupShape functionality with SVG output") {
    GIVEN("A GroupShape with several shapes") {
        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 50}, 0xFF0000, 0x000000);
        std::shared_ptr<IShape> rectangle = std::make_shared<Rectangle>(Frame{{100, 100}, 200, 150}, 0x00FF00, 0x000000);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{200, 200}, 120, 100}, 0x0000FF, 0x000000);

        GroupShape group({ ellipse, rectangle, triangle });

    	REQUIRE(group.GetShapesCount() == 3);

        WHEN("Getting the frame of the group") {
        	auto [leftTop, width, height] = group.GetFrame();

            THEN("The frame should be calculated based on the minimum and maximum coordinates") {
                REQUIRE(leftTop.x == 0);
                REQUIRE(leftTop.y == 0);
                REQUIRE(width == 320);
                REQUIRE(height == 350);
            }
        }

        WHEN("Adding another shape to the group") {
            std::shared_ptr<IShape> newEllipse = std::make_shared<Ellipse>(Frame{{150, 350}, 50, 50}, 0xFFFF00, 0x000000);
            group.AddShape(newEllipse);

            THEN("The number of shapes in the group should now be 4") {
                REQUIRE(group.GetShapesCount() == 4);
            }

            THEN("The frame of the group should be updated to include the new shape") {
                auto [leftTop, width, height] = group.GetFrame();
                REQUIRE(leftTop.x == 0);
                REQUIRE(leftTop.y == 0);
                REQUIRE(width == 320);
                REQUIRE(height == 400);
            }
        }

        WHEN("Getting a shape by index") {
            THEN("Getting the first shape should return the ellipse") {
                REQUIRE(group.GetShape(0) == ellipse);
            }

            THEN("Getting the second shape should return the rectangle") {
                REQUIRE(group.GetShape(1) == rectangle);
            }

            THEN("Getting the third shape should return the triangle") {
                REQUIRE(group.GetShape(2) == triangle);
            }
        }

        WHEN("Trying to get a shape by an invalid index") {
            THEN("An exception should be thrown when the index is out of bounds") {
                REQUIRE_THROWS_AS(group.GetShape(3), std::out_of_range);
            }
        }

        WHEN("Drawing the group to a stringstream") {
            std::stringstream ss;
            std::shared_ptr<ICanvas> canvas = std::make_shared<SvgCanvas>(ss);
            group.Draw(canvas);

            THEN("The SVG output should match the expected output") {
                std::string expectedSvg =
                    R"(<svg width="1200" height="800" version="1.1" xmlns="http://www.w3.org/2000/svg">
<ellipse cx="0" cy="0" rx="100" ry="50" style="fill:transparent;stroke:#ff0000;stroke-width:3"/>
<polygon points="100,100 300,100 300,250 100,250" style="fill:transparent;stroke:#00ff00;stroke-width:3"/>
<polygon points="200,200 320,300 200,300" style="fill:transparent;stroke:#0000ff;stroke-width:3"/>
</svg>)";

                REQUIRE(ss.str() == expectedSvg);
            }
        }
    }
}

SCENARIO("GroupShape fill style functionality with color changes", "[GroupShape]") {
    GIVEN("A GroupShape with several shapes having the same fill color") {
        Color commonFillColor = 0xFF0000;
        Color commonLineColor = 0x000000;

        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 50}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> rectangle = std::make_shared<Rectangle>(Frame{{100, 100}, 200, 150}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{200, 200}, 120, 100}, commonFillColor, commonLineColor);

        GroupShape group({ ellipse, rectangle, triangle });

        WHEN("Checking the fill color of the group") {
            THEN("The fill color should be the same as the individual shapes, i.e., red") {
                std::optional<Color> groupColor = group.GetFillStyle()->GetColor();
                REQUIRE(groupColor.has_value());
                REQUIRE(groupColor.value() == commonFillColor);
            }
        }

        WHEN("Changing the fill color of the group via CompositeFillStyle") {
            std::shared_ptr<CompositeFillStyle> compositeFillStyle = std::dynamic_pointer_cast<CompositeFillStyle>(group.GetFillStyle());
            Color newColor = 0x00FF00;
            compositeFillStyle->SetColor(newColor);

            THEN("The fill color of the group should be updated") {
                std::optional<Color> updatedGroupColor = group.GetFillStyle()->GetColor();
                REQUIRE(updatedGroupColor.has_value());
                REQUIRE(updatedGroupColor.value() == newColor);
            }

            THEN("All shapes in the group should have the updated fill color") {
                REQUIRE(ellipse->GetFillStyle()->GetColor().value() == newColor);
                REQUIRE(rectangle->GetFillStyle()->GetColor().value() == newColor);
                REQUIRE(triangle->GetFillStyle()->GetColor().value() == newColor);
            }
        }
    }
}

SCENARIO("GroupShape line style updates automatically when new shape with different line style is added", "[GroupShape]") {
    GIVEN("A GroupShape with several shapes having the same line style") {
        Color commonLineColor = 0x000000;
        double commonLineWidth = 2.0;
        Color commonFillColor = 0xFF0000;

        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Frame{{0, 0}, 100, 50}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> rectangle = std::make_shared<Rectangle>(Frame{{100, 100}, 200, 150}, commonFillColor, commonLineColor);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(Frame{{200, 200}, 120, 100}, commonFillColor, commonLineColor);

        GroupShape group({ ellipse, rectangle, triangle });

        std::shared_ptr<CompositeLineStyle> compositeLineStyle = std::dynamic_pointer_cast<CompositeLineStyle>(group.GetLineStyle());
        std::optional<Color> initialGroupLineColor = compositeLineStyle->GetColor();
        std::optional<double> initialGroupLineWidth = compositeLineStyle->GetLineWidth();

        REQUIRE(initialGroupLineColor.has_value());
        REQUIRE(initialGroupLineColor.value() == commonLineColor);
        REQUIRE(initialGroupLineWidth.has_value());
        REQUIRE(initialGroupLineWidth.value() == commonLineWidth);

        WHEN("A new shape with a different line style is added to the group") {
            Color newLineColor = 0x00FF00;
            double newLineWidth = 4.0;
            std::shared_ptr<IShape> newRectangle = std::make_shared<Rectangle>(Frame{{300, 300}, 100, 50}, commonFillColor, newLineColor);
            group.AddShape(newRectangle);

            THEN("The group's line style should now reflect the new shape's line style") {
                std::optional<Color> updatedGroupLineColor = compositeLineStyle->GetColor();
                std::optional<double> updatedGroupLineWidth = compositeLineStyle->GetLineWidth();

                REQUIRE_FALSE(updatedGroupLineColor.has_value());
                REQUIRE_FALSE(updatedGroupLineWidth.has_value());
            }
        }
    }
}

SCENARIO("GroupShape correctly resizes and repositions its shapes when SetFrame is called") {
    GIVEN("A GroupShape with several shapes") {
        Frame initialFrame = {{0, 0}, 100, 100};
        std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(initialFrame, 0xFF0000, 0x000000);
        std::shared_ptr<IShape> rectangle = std::make_shared<Rectangle>(initialFrame, 0x00FF00, 0x000000);
        std::shared_ptr<IShape> triangle = std::make_shared<Triangle>(initialFrame, 0x0000FF, 0x000000);

        GroupShape group({ ellipse, rectangle, triangle });

        WHEN("SetFrame is called to resize and reposition the group") {
            Frame newFrame = {{50, 50}, 200, 200};
            group.SetFrame(newFrame);

            THEN("The shapes within the group should resize and reposition proportionally") {
                Frame ellipseFrame = ellipse->GetFrame();
                Frame rectangleFrame = rectangle->GetFrame();
                Frame triangleFrame = triangle->GetFrame();

                REQUIRE(ellipseFrame.leftTop.x == Approx(50 + 0).epsilon(0.01));
                REQUIRE(ellipseFrame.leftTop.y == Approx(50 + 0).epsilon(0.01));
                REQUIRE(ellipseFrame.width == Approx(200).epsilon(0.01));
                REQUIRE(ellipseFrame.height == Approx(200).epsilon(0.01));

                REQUIRE(rectangleFrame.leftTop.x == Approx(50 + 0).epsilon(0.01));
                REQUIRE(rectangleFrame.leftTop.y == Approx(50 + 0).epsilon(0.01));
                REQUIRE(rectangleFrame.width == Approx(200).epsilon(0.01));
                REQUIRE(rectangleFrame.height == Approx(200).epsilon(0.01));

                REQUIRE(triangleFrame.leftTop.x == Approx(50 + 0).epsilon(0.01));
                REQUIRE(triangleFrame.leftTop.y == Approx(50 + 0).epsilon(0.01));
                REQUIRE(triangleFrame.width == Approx(200).epsilon(0.01));
                REQUIRE(triangleFrame.height == Approx(200).epsilon(0.01));
            }
        }
    }
}
