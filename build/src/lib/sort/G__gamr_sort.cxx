// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_sort
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "Sorter.hh"
#include "GatedTimeDifference.hh"
#include "TimeDifference.hh"
#include "CoincidenceMatrixPair.hh"
#include "Matrix.hh"
#include "TimeDifferencePairs.hh"
#include "TimeWalkCal.hh"
#include "CoincidenceCubeDiff.hh"
#include "CoincidenceMatrix.hh"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace GamR {
   namespace Sort {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLSort_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Sort", 0 /*version*/, "Sorter.hh", 26,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLSort_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLSort_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace {
  void TriggerDictionaryInitialization_libgamr_sort_Impl() {
    static const char* headers[] = {
"Sorter.hh",
"GatedTimeDifference.hh",
"TimeDifference.hh",
"CoincidenceMatrixPair.hh",
"Matrix.hh",
"TimeDifferencePairs.hh",
"TimeWalkCal.hh",
"CoincidenceCubeDiff.hh",
"CoincidenceMatrix.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/sort",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/sort",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/sort/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_sort dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_sort dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Sorter.hh"
#include "GatedTimeDifference.hh"
#include "TimeDifference.hh"
#include "CoincidenceMatrixPair.hh"
#include "Matrix.hh"
#include "TimeDifferencePairs.hh"
#include "TimeWalkCal.hh"
#include "CoincidenceCubeDiff.hh"
#include "CoincidenceMatrix.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_sort",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_sort_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_sort_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_sort() {
  TriggerDictionaryInitialization_libgamr_sort_Impl();
}
