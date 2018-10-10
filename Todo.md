# TODO

* Keep simple core::Reporter interface since it minimizes impact on Composite/Component/Leaf.
* Most should use AugmentedReporter interface. Then can move them into core. core::FailFirstFilter. core::MatchingFilter. core::IndentingReporter (takes vector giving names of levels). Only GtestStyleReporter is unit test specific.

* I don't think I would need the 

* ReportAugmenter adapts from core::Reporter to core::AugmentedReporter.

Chained operations two ways:
* Launch-time selected virtual interface
* Edit-time selected templated

Show performance.

* Consider adding color animation to the particle system to prove point of DOD v OOD.

* Mention drawbacks of generic testing hierarchy:
  * Can't be sure aren't adding the wrong child to the wrong parent. Compare this to TestSuite::add(TestSet *) or Composite<Level::TestSuite>::add(Composite<Level::TestSet> *).
  * Doing level-specific reporting becomes more error prone also.
* Pros
  * One set of code for multiple uses. Simpler and more reliable.
  * 
  
 * Mention slight overhead of function local static members. Must check each time if initialized.
 