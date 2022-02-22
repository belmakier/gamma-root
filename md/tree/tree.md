# About the Event Tree {#tree}

@tableofcontents

One of the foundations of GamROOT is the event tree. It was designed to reduce duplication of code, minimize the effort to write complex sorts, and provide a standard, familiar form of data analysis regardless of the experiment. GamROOT is heavily object oriented (and makes no apology) and the GamROOT event tree is no exception. As ~100% of physicists I've met (initially) have strong negative feelings towards object orientatied programming, here I explain the objects contained in the event tree and their rather intuitive link to reality. To first order, just think of objects as containers.

# Event and Detector objects {#tevent_tedetector}

Firstly, any experiment involves taking data. These datums are often associated with a detector. It's possible that multiple datums are associated with a single detector. In nuclear physics, it's common to have an array of detectors; some of these are identical and may be logically grouped. Finally, a coincidence event may be constructed where any combination of your available detectors may have fired. Thus we express our GamR::Tree::TEvent as a container of groups of detectors and the detectors contain the measurements:

+ GamR::Tree::TEvent
  + GamR::Tree::TDetector (Group 1)
    + e.g. contains: UShort_t, UShort_t
  + GamR::Tree::TDetector (Group 2)
    + also contains: UShort_t, UShort_t but physically different
  + .....
  + GamR::Tree::TDetector (Group N)
    + UChar_t, Char_t, ..., any number of basic data types less than 64 bits long.

Above represents the abstract structure of every GamROOT Event Tree. However, as C++ is a strongly typed language -- and in order to serialize to and from disk and memory safely -- specializations must be made i.e. explicitly defining the data types (detectors are also datatypes, just composite ones) backing all these containers. Consider the following experiment, you have an array where you have 3 logical groups. Group 1 contains detectors with 2 unsigned long integers and 1 float, Group 2 contains detectors that have 2 unsigned shorts, and Group 3 detectors with 1 integer. The corresponding GamROOT Event Tree would contain the following types:

```{.cc}
// Detectors
using MyEvent_TDetector0 = GamR::Tree::TDetector<ULong64_t, ULong64_t, Float_t>; // Detector type for Group 1;
using MyEvent_TDetector1 = GamR::Tree::TDetector<UShort_t, UShort_t>;            // Detector type for Group 2;
using MyEvent_TDetector2 = GamR::Tree::TDetector<Int_t>;                         // Detector type for Group 3;
// Event
using MyEvent_TEvent = GamR::Tree::TEvent<MyEvent_TDetector0, MyEvent_TDetector1, MyEvent_TDetector2>;
```

In general all that matters is that the template arguments of any GamR::Tree::TDetector are basic data types, and the template arguments of GamR::Tree::TEvent are made of these detectors. Utilizing templates enables us to enforce a rigid abstract form that collaborators can get familiar with but still have  the flexibility to support arbitrarily large detector arrays and complex tagging, all with a single code base.

![Diagram of a specialization of the GamROOT Event Tree. In this specialization, the first group are some detectors with 3 measurements, the second 2, and the third 1. In general, a GamR::Tree::TEvent contains any number of vectors of any specialization of GamR::Tree::TDetector. The vectors are dynamically sized and only contain the detectors that have fired for that event. The detector objects contain an ID, raw datums, calibrated measurements, and an efficiency.](assets/tree/gamrtree_event.svg)

@defgroup Tree
@addtogroup Tree
@copydoc treetypes
@{
@}
