#include "luanics/statistics/Concepts.hpp"
#include "luanics/testing/Unit.hpp"

namespace luanics::statistics {

/// Does not conform to statistics::BasicConcept
template <typename ObservationT>
class NonConformingStatistics {
public:
	void record(double const observation) {}
	// Not Countable
	// Not Meanable
};

/// Conforms to statistics::BasicConcept
template <typename ObservationT>
class BasicConceptConformingStatistics {
public:
	void record(ObservationT const observation) {}
	std::size_t count() const {return {};}
	ObservationT total() const {return {};}
	double mean() const {return 0.0;}
	ObservationT min() const {return {};}
	ObservationT max() const {return {};}
};

/// Conforms to statistics::Concept
template <typename ObservationT>
class ConceptConformingStatistics : public BasicConceptConformingStatistics<ObservationT> {
public:
	double stdDev() const {return 0.0;}
};

BEGIN_TEST_SET(StatisticsConcept)

TEST(BasicConcept) {
	EXPECT_FALSE((BasicConcept<NonConformingStatistics, int>));
	EXPECT_TRUE((BasicConcept<BasicConceptConformingStatistics, int>));
	EXPECT_TRUE((BasicConcept<ConceptConformingStatistics, int>));

	EXPECT_FALSE((BasicConcept<NonConformingStatistics, double>));
	EXPECT_TRUE((BasicConcept<BasicConceptConformingStatistics, double>));
	EXPECT_TRUE((BasicConcept<ConceptConformingStatistics, double>));
}

TEST(Concept) {
	EXPECT_FALSE((Concept<NonConformingStatistics, int>));
	EXPECT_FALSE((Concept<BasicConceptConformingStatistics, int>));
	EXPECT_TRUE((Concept<ConceptConformingStatistics, int>));

	EXPECT_FALSE((Concept<NonConformingStatistics, double>));
	EXPECT_FALSE((Concept<BasicConceptConformingStatistics, double>));
	EXPECT_TRUE((Concept<ConceptConformingStatistics, double>));
}

END_TEST_SET()

} // namespace luanics::statistics
