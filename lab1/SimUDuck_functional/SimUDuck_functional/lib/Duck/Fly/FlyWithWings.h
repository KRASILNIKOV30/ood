#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

FlyStrategy MakeFlyWithWings()
{
	return [flyCounter = 0u] () mutable -> void
	{
		flyCounter++;
		std::cout << flyCounter << ": I'm flying with wings!!" << std::endl;
	};
}

#endif
