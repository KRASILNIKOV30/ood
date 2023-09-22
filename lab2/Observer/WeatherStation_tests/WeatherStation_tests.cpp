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

	class SelfRemovingObserver : public IObserver<int>
	{
	public:
		SelfRemovingObserver(Subject* subject)
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

	class PrioritingObserver : public IObserver<int>
	{
	public:
		PrioritingObserver(std::string&& str, std::ostream& stream)
			: m_str(std::move(str))
			, m_stream(stream)
		{}

		void Update(int const&) override
		{
			m_stream << m_str << " observer was updated" << std::endl;
		}

	private:
		std::string m_str;
		std::ostream& m_stream;
	};
}


SCENARIO("Notifying of self removing")
{
	GIVEN("Subject and self removing observer")
	{
		Subject subject;
		SelfRemovingObserver observer(&subject);
		
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

SCENARIO("Prioriting observers")
{
	GIVEN("Subject and prioriting observers")
	{
		std::stringstream stream;
		Subject subject;
		PrioritingObserver firstObserver("The first", stream);
		PrioritingObserver secondObserver("The second", stream);
		PrioritingObserver thirdObserver("The third", stream);

		WHEN("Register observers in random order but with priorities")
		{
			subject.RegisterObserver(secondObserver, 2);
			subject.RegisterObserver(thirdObserver, 1);
			subject.RegisterObserver(firstObserver, 3);

			AND_WHEN("Notify observers")
			{
				subject.NotifyObservers();

				THEN("Observers was notified in right order")
				{
					CHECK(stream.str() ==
						"The first observer was updated\n"
						"The second observer was updated\n"
						"The third observer was updated\n"
					);
				}
			}
		}
	}
}