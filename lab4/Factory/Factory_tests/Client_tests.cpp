#include "../../../external/catch2/catch.hpp"
#include "../Factory/CClient.h"
#include "../Factory/Common.h"
#include "../Factory/CPainter.h"
#include "../Factory/IDesigner.h"
#include "../Factory/MockCanvas.h"
#include <sstream>

namespace
{
	class MockDesigner final : public IDesigner
	{
	public:
		CPictureDraft CreateDraft(std::istream& strm) const override
		{
			std::cout << "Create draft" << std::endl;
			return CPictureDraft(Shapes());
		}
	};
}

SCENARIO_METHOD(CoutBufferFixture, "Client test")
{
	GIVEN("Client, designer and painter")
	{
		MockCanvas canvas;
		MockDesigner designer;
		CPainter painter;
		std::stringstream strm;
		CClient client(strm, canvas);

		WHEN("Client make picture")
		{
			client.MakePicture(designer, painter);

			THEN("Draft has been created")
			{
				CHECK(GetOutput() == "Create draft\n");
			}
		}
	}
}
