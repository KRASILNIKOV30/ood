#include "../../../external/catch2/catch.hpp"
#include "../Observer/WeatherData.h"
#include "../Observer/Observer.h"


namespace
{
	class Subject : public CObservable<int>
	{
	protected:
		int GetChangedData() const override
		{
			return 0;
		}
	};

	class SelfDeletingObserver : public IObserver<int>
	{
	public:
		SelfDeletingObserver(Subject* subject)
			: m_observable(subject)
		{
		}

		void Update(int const&) override
		{
			m_observable->RemoveObserver(*this);
		}

	private:
		Subject* m_observable;
	};
}


SCENARIO("Safe notifying")
{
	GIVEN("Self deleting observer")
	{
		Subject subject;
		SelfDeletingObserver observer(&subject);
		
		WHEN("Register observer")
		{
			subject.RegisterObserver(observer);

			THEN("Can notify observer")
			{
				CHECK_NOTHROW(subject.NotifyObservers());
			}
		}
	}
}