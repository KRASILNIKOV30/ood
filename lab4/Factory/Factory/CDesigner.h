#pragma once
#include "CShapeFactory.h"
#include "IDesigner.h"

class CDesigner final : public IDesigner
{
public:
	CPictureDraft CreateDraft(std::istream& strm) const override
	{
		Shapes shapes;
		std::string shapeDescr;
		while (!strm.eof() && !strm.fail() && std::getline(strm, shapeDescr))
		{
			try
			{
				shapes.push_back(factory.CreateShape(shapeDescr));
			}
			catch (std::exception const& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		return CPictureDraft(std::move(shapes));
	}

private:
	CShapeFactory factory;
};
