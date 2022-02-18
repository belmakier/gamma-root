// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_ornl
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
#include "OakRidge.hh"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace GamR {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamR_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR", 0 /*version*/, "OakRidge.hh", 17,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamR_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamR_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace GamR {
   namespace ORNL {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLORNL_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::ORNL", 0 /*version*/, "OakRidge.hh", 25,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLORNL_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLORNL_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   static void *new_GamRcLcLORNLcLcLBananaGate(void *p = nullptr);
   static void *newArray_GamRcLcLORNLcLcLBananaGate(Long_t size, void *p);
   static void delete_GamRcLcLORNLcLcLBananaGate(void *p);
   static void deleteArray_GamRcLcLORNLcLcLBananaGate(void *p);
   static void destruct_GamRcLcLORNLcLcLBananaGate(void *p);
   static Long64_t merge_GamRcLcLORNLcLcLBananaGate(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::ORNL::BananaGate*)
   {
      ::GamR::ORNL::BananaGate *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::ORNL::BananaGate >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::ORNL::BananaGate", ::GamR::ORNL::BananaGate::Class_Version(), "OakRidge.hh", 26,
                  typeid(::GamR::ORNL::BananaGate), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::ORNL::BananaGate::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::ORNL::BananaGate) );
      instance.SetNew(&new_GamRcLcLORNLcLcLBananaGate);
      instance.SetNewArray(&newArray_GamRcLcLORNLcLcLBananaGate);
      instance.SetDelete(&delete_GamRcLcLORNLcLcLBananaGate);
      instance.SetDeleteArray(&deleteArray_GamRcLcLORNLcLcLBananaGate);
      instance.SetDestructor(&destruct_GamRcLcLORNLcLcLBananaGate);
      instance.SetMerge(&merge_GamRcLcLORNLcLcLBananaGate);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::ORNL::BananaGate*)
   {
      return GenerateInitInstanceLocal((::GamR::ORNL::BananaGate*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::ORNL::BananaGate*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace GamR {
   namespace ORNL {
//______________________________________________________________________________
atomic_TClass_ptr BananaGate::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BananaGate::Class_Name()
{
   return "GamR::ORNL::BananaGate";
}

//______________________________________________________________________________
const char *BananaGate::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::ORNL::BananaGate*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BananaGate::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::ORNL::BananaGate*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BananaGate::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::ORNL::BananaGate*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BananaGate::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::ORNL::BananaGate*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::ORNL
} // namespace GamR::ORNL
namespace GamR {
   namespace ORNL {
//______________________________________________________________________________
void BananaGate::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::ORNL::BananaGate.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::ORNL::BananaGate::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::ORNL::BananaGate::Class(),this);
   }
}

} // namespace GamR::ORNL
} // namespace GamR::ORNL
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLORNLcLcLBananaGate(void *p) {
      return  p ? new(p) ::GamR::ORNL::BananaGate : new ::GamR::ORNL::BananaGate;
   }
   static void *newArray_GamRcLcLORNLcLcLBananaGate(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::ORNL::BananaGate[nElements] : new ::GamR::ORNL::BananaGate[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLORNLcLcLBananaGate(void *p) {
      delete ((::GamR::ORNL::BananaGate*)p);
   }
   static void deleteArray_GamRcLcLORNLcLcLBananaGate(void *p) {
      delete [] ((::GamR::ORNL::BananaGate*)p);
   }
   static void destruct_GamRcLcLORNLcLcLBananaGate(void *p) {
      typedef ::GamR::ORNL::BananaGate current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_GamRcLcLORNLcLcLBananaGate(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::GamR::ORNL::BananaGate*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::GamR::ORNL::BananaGate

namespace {
  void TriggerDictionaryInitialization_libgamr_ornl_Impl() {
    static const char* headers[] = {
"OakRidge.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/ornl",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/ornl",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/ornl/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_ornl dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace ORNL{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/ornl/OakRidge.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$OakRidge.hh")))  BananaGate;}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_ornl dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "OakRidge.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::ORNL::BananaGate", payloadCode, "@",
"GamR::ORNL::BananaGate::fgIsA", payloadCode, "@",
"GamR::ORNL::readAllBananas", payloadCode, "@",
"GamR::ORNL::readBanana", payloadCode, "@",
"GamR::ORNL::writeAllBananas", payloadCode, "@",
"GamR::ORNL::writeBananas", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_ornl",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_ornl_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_ornl_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_ornl() {
  TriggerDictionaryInitialization_libgamr_ornl_Impl();
}
