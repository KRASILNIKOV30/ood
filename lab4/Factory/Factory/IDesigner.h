#pragma once
#include "CPictureDraft.h"

class IDesigner
{
public:
	virtual ~IDesigner() = default;
	//�������� �� ������ (����������)
	virtual CPictureDraft CreateDraft(std::istream& strm) const = 0;
};
