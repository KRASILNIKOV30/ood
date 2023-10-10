#pragma once
#include "CPictureDraft.h"

class IDesigner
{
public:
	virtual ~IDesigner() = default;
	//Передать по ссылке (исправлено)
	virtual CPictureDraft CreateDraft(std::istream& strm) const = 0;
};
