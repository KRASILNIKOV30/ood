#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

void FlyWithWings()
{
	static int flyCounter = 0;
	std::cout << ++flyCounter << ": I'm flying with wings!!" << std::endl;
	/*auto fn = [&] () mutable 
	{
		
	};
	fn();*/
}

#endif
