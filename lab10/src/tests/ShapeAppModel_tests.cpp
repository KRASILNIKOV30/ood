#include "../appModel/IShapeAppModel.h"
#include "../appModel/ShapeAppModel.h"
#include "../model/Rectangle.h"

#include <catch.hpp>
SCENARIO("shape app model tests")
{
	GIVEN("a shape from a domain shape")
	{
		const IShapePtr domainShape = std::make_unique<Rectangle>("rectId", Frame{ { 10, 20 }, { 30, 40 } });
		const IShapeAppModelPtr shape = std::make_unique<ShapeAppModel>(domainShape.get());

		THEN("can get frame")
		{
			CHECK(shape->GetFrame() == Frame{ { 10, 20 }, { 30, 40 } });
		}

		AND_THEN("can get type")
		{
			CHECK(shape->GetType() == "rectangle");
		}

		AND_THEN("can get id")
		{
			CHECK(shape->GetId() == "rectId");
		}
	}
}
