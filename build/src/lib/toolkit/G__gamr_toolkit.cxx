// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_toolkit
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
#include "MonteCarlo.hh"
#include "Gate.hh"
#include "Peak.hh"
#include "Misc.hh"

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
            instance("GamR", 0 /*version*/, "MonteCarlo.hh", 11,
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
   namespace TK {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLTK_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::TK", 0 /*version*/, "MonteCarlo.hh", 12,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLTK_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLTK_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   static void *new_GamRcLcLTKcLcLGate(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLGate(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLGate(void *p);
   static void deleteArray_GamRcLcLTKcLcLGate(void *p);
   static void destruct_GamRcLcLTKcLcLGate(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::Gate*)
   {
      ::GamR::TK::Gate *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::TK::Gate >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::Gate", ::GamR::TK::Gate::Class_Version(), "Gate.hh", 31,
                  typeid(::GamR::TK::Gate), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::TK::Gate::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::Gate) );
      instance.SetNew(&new_GamRcLcLTKcLcLGate);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLGate);
      instance.SetDelete(&delete_GamRcLcLTKcLcLGate);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLGate);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLGate);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::Gate*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::Gate*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::Gate*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLTKcLcLGateMap(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLGateMap(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLGateMap(void *p);
   static void deleteArray_GamRcLcLTKcLcLGateMap(void *p);
   static void destruct_GamRcLcLTKcLcLGateMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::GateMap*)
   {
      ::GamR::TK::GateMap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::TK::GateMap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::GateMap", ::GamR::TK::GateMap::Class_Version(), "Gate.hh", 133,
                  typeid(::GamR::TK::GateMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::TK::GateMap::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::GateMap) );
      instance.SetNew(&new_GamRcLcLTKcLcLGateMap);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLGateMap);
      instance.SetDelete(&delete_GamRcLcLTKcLcLGateMap);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLGateMap);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLGateMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::GateMap*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::GateMap*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::GateMap*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLPeak_Dictionary();
   static void GamRcLcLTKcLcLPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLPeak(void *p);
   static void destruct_GamRcLcLTKcLcLPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::Peak*)
   {
      ::GamR::TK::Peak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::Peak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::Peak", "Peak.hh", 36,
                  typeid(::GamR::TK::Peak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::Peak) );
      instance.SetNew(&new_GamRcLcLTKcLcLPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::Peak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::Peak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::Peak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::Peak*)nullptr)->GetClass();
      GamRcLcLTKcLcLPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLTKcLcLBPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLBPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLBPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLBPeak(void *p);
   static void destruct_GamRcLcLTKcLcLBPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::BPeak*)
   {
      ::GamR::TK::BPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::TK::BPeak >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::BPeak", ::GamR::TK::BPeak::Class_Version(), "Peak.hh", 56,
                  typeid(::GamR::TK::BPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::TK::BPeak::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::BPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLBPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLBPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLBPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLBPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLBPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::BPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::BPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::BPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLFPeak_Dictionary();
   static void GamRcLcLTKcLcLFPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLFPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLFPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLFPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLFPeak(void *p);
   static void destruct_GamRcLcLTKcLcLFPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::FPeak*)
   {
      ::GamR::TK::FPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::FPeak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::FPeak", "Peak.hh", 116,
                  typeid(::GamR::TK::FPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLFPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::FPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLFPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLFPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLFPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLFPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLFPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::FPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::FPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::FPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLFPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::FPeak*)nullptr)->GetClass();
      GamRcLcLTKcLcLFPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLFPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLGaussianPeak_Dictionary();
   static void GamRcLcLTKcLcLGaussianPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLGaussianPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLGaussianPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLGaussianPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLGaussianPeak(void *p);
   static void destruct_GamRcLcLTKcLcLGaussianPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::GaussianPeak*)
   {
      ::GamR::TK::GaussianPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::GaussianPeak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::GaussianPeak", "Peak.hh", 147,
                  typeid(::GamR::TK::GaussianPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLGaussianPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::GaussianPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLGaussianPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLGaussianPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLGaussianPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLGaussianPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLGaussianPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::GaussianPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::GaussianPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::GaussianPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLGaussianPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::GaussianPeak*)nullptr)->GetClass();
      GamRcLcLTKcLcLGaussianPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLGaussianPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLStepGaussianPeak_Dictionary();
   static void GamRcLcLTKcLcLStepGaussianPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLStepGaussianPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLStepGaussianPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLStepGaussianPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLStepGaussianPeak(void *p);
   static void destruct_GamRcLcLTKcLcLStepGaussianPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::StepGaussianPeak*)
   {
      ::GamR::TK::StepGaussianPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::StepGaussianPeak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::StepGaussianPeak", "Peak.hh", 182,
                  typeid(::GamR::TK::StepGaussianPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLStepGaussianPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::StepGaussianPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLStepGaussianPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLStepGaussianPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLStepGaussianPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLStepGaussianPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLStepGaussianPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::StepGaussianPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::StepGaussianPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::StepGaussianPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLStepGaussianPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::StepGaussianPeak*)nullptr)->GetClass();
      GamRcLcLTKcLcLStepGaussianPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLStepGaussianPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLOneTailGaussianPeak_Dictionary();
   static void GamRcLcLTKcLcLOneTailGaussianPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLOneTailGaussianPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLOneTailGaussianPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLOneTailGaussianPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLOneTailGaussianPeak(void *p);
   static void destruct_GamRcLcLTKcLcLOneTailGaussianPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::OneTailGaussianPeak*)
   {
      ::GamR::TK::OneTailGaussianPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::OneTailGaussianPeak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::OneTailGaussianPeak", "Peak.hh", 225,
                  typeid(::GamR::TK::OneTailGaussianPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLOneTailGaussianPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::OneTailGaussianPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLOneTailGaussianPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLOneTailGaussianPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLOneTailGaussianPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLOneTailGaussianPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLOneTailGaussianPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::OneTailGaussianPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::OneTailGaussianPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::OneTailGaussianPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLOneTailGaussianPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::OneTailGaussianPeak*)nullptr)->GetClass();
      GamRcLcLTKcLcLOneTailGaussianPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLOneTailGaussianPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLOneTailStepGaussianPeak_Dictionary();
   static void GamRcLcLTKcLcLOneTailStepGaussianPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLOneTailStepGaussianPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p);
   static void destruct_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::OneTailStepGaussianPeak*)
   {
      ::GamR::TK::OneTailStepGaussianPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::OneTailStepGaussianPeak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::OneTailStepGaussianPeak", "Peak.hh", 258,
                  typeid(::GamR::TK::OneTailStepGaussianPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLOneTailStepGaussianPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::OneTailStepGaussianPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLOneTailStepGaussianPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLOneTailStepGaussianPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLOneTailStepGaussianPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLOneTailStepGaussianPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLOneTailStepGaussianPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::OneTailStepGaussianPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::OneTailStepGaussianPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::OneTailStepGaussianPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLOneTailStepGaussianPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::OneTailStepGaussianPeak*)nullptr)->GetClass();
      GamRcLcLTKcLcLOneTailStepGaussianPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLOneTailStepGaussianPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLTwoTailGaussianPeak_Dictionary();
   static void GamRcLcLTKcLcLTwoTailGaussianPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLTwoTailGaussianPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p);
   static void destruct_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::TwoTailGaussianPeak*)
   {
      ::GamR::TK::TwoTailGaussianPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::TwoTailGaussianPeak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::TwoTailGaussianPeak", "Peak.hh", 297,
                  typeid(::GamR::TK::TwoTailGaussianPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLTwoTailGaussianPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::TwoTailGaussianPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLTwoTailGaussianPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLTwoTailGaussianPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLTwoTailGaussianPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLTwoTailGaussianPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLTwoTailGaussianPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::TwoTailGaussianPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::TwoTailGaussianPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::TwoTailGaussianPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLTwoTailGaussianPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::TwoTailGaussianPeak*)nullptr)->GetClass();
      GamRcLcLTKcLcLTwoTailGaussianPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLTwoTailGaussianPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLTKcLcLTwoTailStepGaussianPeak_Dictionary();
   static void GamRcLcLTKcLcLTwoTailStepGaussianPeak_TClassManip(TClass*);
   static void *new_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p = nullptr);
   static void *newArray_GamRcLcLTKcLcLTwoTailStepGaussianPeak(Long_t size, void *p);
   static void delete_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p);
   static void deleteArray_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p);
   static void destruct_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::TK::TwoTailStepGaussianPeak*)
   {
      ::GamR::TK::TwoTailStepGaussianPeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::TK::TwoTailStepGaussianPeak));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::TK::TwoTailStepGaussianPeak", "Peak.hh", 331,
                  typeid(::GamR::TK::TwoTailStepGaussianPeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLTKcLcLTwoTailStepGaussianPeak_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::TK::TwoTailStepGaussianPeak) );
      instance.SetNew(&new_GamRcLcLTKcLcLTwoTailStepGaussianPeak);
      instance.SetNewArray(&newArray_GamRcLcLTKcLcLTwoTailStepGaussianPeak);
      instance.SetDelete(&delete_GamRcLcLTKcLcLTwoTailStepGaussianPeak);
      instance.SetDeleteArray(&deleteArray_GamRcLcLTKcLcLTwoTailStepGaussianPeak);
      instance.SetDestructor(&destruct_GamRcLcLTKcLcLTwoTailStepGaussianPeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::TK::TwoTailStepGaussianPeak*)
   {
      return GenerateInitInstanceLocal((::GamR::TK::TwoTailStepGaussianPeak*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::TK::TwoTailStepGaussianPeak*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLTKcLcLTwoTailStepGaussianPeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::TwoTailStepGaussianPeak*)nullptr)->GetClass();
      GamRcLcLTKcLcLTwoTailStepGaussianPeak_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLTKcLcLTwoTailStepGaussianPeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh");
   }

} // end of namespace ROOT

namespace GamR {
   namespace TK {
//______________________________________________________________________________
atomic_TClass_ptr Gate::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Gate::Class_Name()
{
   return "GamR::TK::Gate";
}

//______________________________________________________________________________
const char *Gate::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::Gate*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Gate::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::Gate*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Gate::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::Gate*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Gate::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::Gate*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::TK
} // namespace GamR::TK
namespace GamR {
   namespace TK {
//______________________________________________________________________________
atomic_TClass_ptr GateMap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *GateMap::Class_Name()
{
   return "GamR::TK::GateMap";
}

//______________________________________________________________________________
const char *GateMap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::GateMap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int GateMap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::GateMap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GateMap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::GateMap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GateMap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::GateMap*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::TK
} // namespace GamR::TK
namespace GamR {
   namespace TK {
//______________________________________________________________________________
atomic_TClass_ptr BPeak::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *BPeak::Class_Name()
{
   return "GamR::TK::BPeak";
}

//______________________________________________________________________________
const char *BPeak::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::BPeak*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int BPeak::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::BPeak*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BPeak::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::BPeak*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BPeak::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::TK::BPeak*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::TK
} // namespace GamR::TK
namespace GamR {
   namespace TK {
//______________________________________________________________________________
void Gate::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::TK::Gate.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::TK::Gate::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::TK::Gate::Class(),this);
   }
}

} // namespace GamR::TK
} // namespace GamR::TK
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLGate(void *p) {
      return  p ? new(p) ::GamR::TK::Gate : new ::GamR::TK::Gate;
   }
   static void *newArray_GamRcLcLTKcLcLGate(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::TK::Gate[nElements] : new ::GamR::TK::Gate[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLGate(void *p) {
      delete ((::GamR::TK::Gate*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLGate(void *p) {
      delete [] ((::GamR::TK::Gate*)p);
   }
   static void destruct_GamRcLcLTKcLcLGate(void *p) {
      typedef ::GamR::TK::Gate current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::Gate

namespace GamR {
   namespace TK {
//______________________________________________________________________________
void GateMap::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::TK::GateMap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::TK::GateMap::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::TK::GateMap::Class(),this);
   }
}

} // namespace GamR::TK
} // namespace GamR::TK
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLGateMap(void *p) {
      return  p ? new(p) ::GamR::TK::GateMap : new ::GamR::TK::GateMap;
   }
   static void *newArray_GamRcLcLTKcLcLGateMap(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::TK::GateMap[nElements] : new ::GamR::TK::GateMap[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLGateMap(void *p) {
      delete ((::GamR::TK::GateMap*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLGateMap(void *p) {
      delete [] ((::GamR::TK::GateMap*)p);
   }
   static void destruct_GamRcLcLTKcLcLGateMap(void *p) {
      typedef ::GamR::TK::GateMap current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::GateMap

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::Peak : new ::GamR::TK::Peak;
   }
   static void *newArray_GamRcLcLTKcLcLPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::Peak[nElements] : new ::GamR::TK::Peak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLPeak(void *p) {
      delete ((::GamR::TK::Peak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLPeak(void *p) {
      delete [] ((::GamR::TK::Peak*)p);
   }
   static void destruct_GamRcLcLTKcLcLPeak(void *p) {
      typedef ::GamR::TK::Peak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::Peak

namespace GamR {
   namespace TK {
//______________________________________________________________________________
void BPeak::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::TK::BPeak.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::TK::BPeak::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::TK::BPeak::Class(),this);
   }
}

} // namespace GamR::TK
} // namespace GamR::TK
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLBPeak(void *p) {
      return  p ? new(p) ::GamR::TK::BPeak : new ::GamR::TK::BPeak;
   }
   static void *newArray_GamRcLcLTKcLcLBPeak(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::TK::BPeak[nElements] : new ::GamR::TK::BPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLBPeak(void *p) {
      delete ((::GamR::TK::BPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLBPeak(void *p) {
      delete [] ((::GamR::TK::BPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLBPeak(void *p) {
      typedef ::GamR::TK::BPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::BPeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLFPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::FPeak : new ::GamR::TK::FPeak;
   }
   static void *newArray_GamRcLcLTKcLcLFPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::FPeak[nElements] : new ::GamR::TK::FPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLFPeak(void *p) {
      delete ((::GamR::TK::FPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLFPeak(void *p) {
      delete [] ((::GamR::TK::FPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLFPeak(void *p) {
      typedef ::GamR::TK::FPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::FPeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLGaussianPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::GaussianPeak : new ::GamR::TK::GaussianPeak;
   }
   static void *newArray_GamRcLcLTKcLcLGaussianPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::GaussianPeak[nElements] : new ::GamR::TK::GaussianPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLGaussianPeak(void *p) {
      delete ((::GamR::TK::GaussianPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLGaussianPeak(void *p) {
      delete [] ((::GamR::TK::GaussianPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLGaussianPeak(void *p) {
      typedef ::GamR::TK::GaussianPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::GaussianPeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLStepGaussianPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::StepGaussianPeak : new ::GamR::TK::StepGaussianPeak;
   }
   static void *newArray_GamRcLcLTKcLcLStepGaussianPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::StepGaussianPeak[nElements] : new ::GamR::TK::StepGaussianPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLStepGaussianPeak(void *p) {
      delete ((::GamR::TK::StepGaussianPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLStepGaussianPeak(void *p) {
      delete [] ((::GamR::TK::StepGaussianPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLStepGaussianPeak(void *p) {
      typedef ::GamR::TK::StepGaussianPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::StepGaussianPeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLOneTailGaussianPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::OneTailGaussianPeak : new ::GamR::TK::OneTailGaussianPeak;
   }
   static void *newArray_GamRcLcLTKcLcLOneTailGaussianPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::OneTailGaussianPeak[nElements] : new ::GamR::TK::OneTailGaussianPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLOneTailGaussianPeak(void *p) {
      delete ((::GamR::TK::OneTailGaussianPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLOneTailGaussianPeak(void *p) {
      delete [] ((::GamR::TK::OneTailGaussianPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLOneTailGaussianPeak(void *p) {
      typedef ::GamR::TK::OneTailGaussianPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::OneTailGaussianPeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::OneTailStepGaussianPeak : new ::GamR::TK::OneTailStepGaussianPeak;
   }
   static void *newArray_GamRcLcLTKcLcLOneTailStepGaussianPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::OneTailStepGaussianPeak[nElements] : new ::GamR::TK::OneTailStepGaussianPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p) {
      delete ((::GamR::TK::OneTailStepGaussianPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p) {
      delete [] ((::GamR::TK::OneTailStepGaussianPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLOneTailStepGaussianPeak(void *p) {
      typedef ::GamR::TK::OneTailStepGaussianPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::OneTailStepGaussianPeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::TwoTailGaussianPeak : new ::GamR::TK::TwoTailGaussianPeak;
   }
   static void *newArray_GamRcLcLTKcLcLTwoTailGaussianPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::TwoTailGaussianPeak[nElements] : new ::GamR::TK::TwoTailGaussianPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p) {
      delete ((::GamR::TK::TwoTailGaussianPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p) {
      delete [] ((::GamR::TK::TwoTailGaussianPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLTwoTailGaussianPeak(void *p) {
      typedef ::GamR::TK::TwoTailGaussianPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::TwoTailGaussianPeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::TwoTailStepGaussianPeak : new ::GamR::TK::TwoTailStepGaussianPeak;
   }
   static void *newArray_GamRcLcLTKcLcLTwoTailStepGaussianPeak(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::TK::TwoTailStepGaussianPeak[nElements] : new ::GamR::TK::TwoTailStepGaussianPeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p) {
      delete ((::GamR::TK::TwoTailStepGaussianPeak*)p);
   }
   static void deleteArray_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p) {
      delete [] ((::GamR::TK::TwoTailStepGaussianPeak*)p);
   }
   static void destruct_GamRcLcLTKcLcLTwoTailStepGaussianPeak(void *p) {
      typedef ::GamR::TK::TwoTailStepGaussianPeak current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::TK::TwoTailStepGaussianPeak

namespace ROOT {
   static TClass *vectorlEGamRcLcLTKcLcLGategR_Dictionary();
   static void vectorlEGamRcLcLTKcLcLGategR_TClassManip(TClass*);
   static void *new_vectorlEGamRcLcLTKcLcLGategR(void *p = nullptr);
   static void *newArray_vectorlEGamRcLcLTKcLcLGategR(Long_t size, void *p);
   static void delete_vectorlEGamRcLcLTKcLcLGategR(void *p);
   static void deleteArray_vectorlEGamRcLcLTKcLcLGategR(void *p);
   static void destruct_vectorlEGamRcLcLTKcLcLGategR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GamR::TK::Gate>*)
   {
      vector<GamR::TK::Gate> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GamR::TK::Gate>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GamR::TK::Gate>", -2, "c++/v1/vector", 471,
                  typeid(vector<GamR::TK::Gate>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGamRcLcLTKcLcLGategR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GamR::TK::Gate>) );
      instance.SetNew(&new_vectorlEGamRcLcLTKcLcLGategR);
      instance.SetNewArray(&newArray_vectorlEGamRcLcLTKcLcLGategR);
      instance.SetDelete(&delete_vectorlEGamRcLcLTKcLcLGategR);
      instance.SetDeleteArray(&deleteArray_vectorlEGamRcLcLTKcLcLGategR);
      instance.SetDestructor(&destruct_vectorlEGamRcLcLTKcLcLGategR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GamR::TK::Gate> >()));

      ::ROOT::AddClassAlternate("vector<GamR::TK::Gate>","std::__1::vector<GamR::TK::Gate, std::__1::allocator<GamR::TK::Gate> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GamR::TK::Gate>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGamRcLcLTKcLcLGategR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GamR::TK::Gate>*)nullptr)->GetClass();
      vectorlEGamRcLcLTKcLcLGategR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGamRcLcLTKcLcLGategR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGamRcLcLTKcLcLGategR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::TK::Gate> : new vector<GamR::TK::Gate>;
   }
   static void *newArray_vectorlEGamRcLcLTKcLcLGategR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::TK::Gate>[nElements] : new vector<GamR::TK::Gate>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGamRcLcLTKcLcLGategR(void *p) {
      delete ((vector<GamR::TK::Gate>*)p);
   }
   static void deleteArray_vectorlEGamRcLcLTKcLcLGategR(void *p) {
      delete [] ((vector<GamR::TK::Gate>*)p);
   }
   static void destruct_vectorlEGamRcLcLTKcLcLGategR(void *p) {
      typedef vector<GamR::TK::Gate> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GamR::TK::Gate>

namespace ROOT {
   static TClass *maplEstringcOGamRcLcLTKcLcLGategR_Dictionary();
   static void maplEstringcOGamRcLcLTKcLcLGategR_TClassManip(TClass*);
   static void *new_maplEstringcOGamRcLcLTKcLcLGategR(void *p = nullptr);
   static void *newArray_maplEstringcOGamRcLcLTKcLcLGategR(Long_t size, void *p);
   static void delete_maplEstringcOGamRcLcLTKcLcLGategR(void *p);
   static void deleteArray_maplEstringcOGamRcLcLTKcLcLGategR(void *p);
   static void destruct_maplEstringcOGamRcLcLTKcLcLGategR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,GamR::TK::Gate>*)
   {
      map<string,GamR::TK::Gate> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,GamR::TK::Gate>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,GamR::TK::Gate>", -2, "c++/v1/map", 900,
                  typeid(map<string,GamR::TK::Gate>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOGamRcLcLTKcLcLGategR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,GamR::TK::Gate>) );
      instance.SetNew(&new_maplEstringcOGamRcLcLTKcLcLGategR);
      instance.SetNewArray(&newArray_maplEstringcOGamRcLcLTKcLcLGategR);
      instance.SetDelete(&delete_maplEstringcOGamRcLcLTKcLcLGategR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOGamRcLcLTKcLcLGategR);
      instance.SetDestructor(&destruct_maplEstringcOGamRcLcLTKcLcLGategR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,GamR::TK::Gate> >()));

      ::ROOT::AddClassAlternate("map<string,GamR::TK::Gate>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, GamR::TK::Gate, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, GamR::TK::Gate> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,GamR::TK::Gate>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOGamRcLcLTKcLcLGategR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,GamR::TK::Gate>*)nullptr)->GetClass();
      maplEstringcOGamRcLcLTKcLcLGategR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOGamRcLcLTKcLcLGategR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOGamRcLcLTKcLcLGategR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::TK::Gate> : new map<string,GamR::TK::Gate>;
   }
   static void *newArray_maplEstringcOGamRcLcLTKcLcLGategR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::TK::Gate>[nElements] : new map<string,GamR::TK::Gate>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOGamRcLcLTKcLcLGategR(void *p) {
      delete ((map<string,GamR::TK::Gate>*)p);
   }
   static void deleteArray_maplEstringcOGamRcLcLTKcLcLGategR(void *p) {
      delete [] ((map<string,GamR::TK::Gate>*)p);
   }
   static void destruct_maplEstringcOGamRcLcLTKcLcLGategR(void *p) {
      typedef map<string,GamR::TK::Gate> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,GamR::TK::Gate>

namespace {
  void TriggerDictionaryInitialization_libgamr_toolkit_Impl() {
    static const char* headers[] = {
"MonteCarlo.hh",
"Gate.hh",
"Peak.hh",
"Misc.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/toolkit",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/toolkit",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/toolkit/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_toolkit dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Gate.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Gate.hh")))  Gate;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Gate.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Gate.hh")))  GateMap;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  Peak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  BPeak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  FPeak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  GaussianPeak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  StepGaussianPeak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  OneTailGaussianPeak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  OneTailStepGaussianPeak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  TwoTailGaussianPeak;}}
namespace GamR{namespace TK{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/toolkit/Peak.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Peak.hh")))  TwoTailStepGaussianPeak;}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_toolkit dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "MonteCarlo.hh"
#include "Gate.hh"
#include "Peak.hh"
#include "Misc.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::TK::BPeak", payloadCode, "@",
"GamR::TK::BPeak::fgIsA", payloadCode, "@",
"GamR::TK::ClickBPeak", payloadCode, "@",
"GamR::TK::Elements", payloadCode, "@",
"GamR::TK::FPeak", payloadCode, "@",
"GamR::TK::FitBPeak", payloadCode, "@",
"GamR::TK::Gate", payloadCode, "@",
"GamR::TK::Gate::fgIsA", payloadCode, "@",
"GamR::TK::GateMap", payloadCode, "@",
"GamR::TK::GateMap::fgIsA", payloadCode, "@",
"GamR::TK::GaussianPeak", payloadCode, "@",
"GamR::TK::GetElement", payloadCode, "@",
"GamR::TK::GetZA", payloadCode, "@",
"GamR::TK::MonteCarlo", payloadCode, "@",
"GamR::TK::OneTailGaussianPeak", payloadCode, "@",
"GamR::TK::OneTailStepGaussianPeak", payloadCode, "@",
"GamR::TK::Peak", payloadCode, "@",
"GamR::TK::StepGaussianPeak", payloadCode, "@",
"GamR::TK::TwoTailGaussianPeak", payloadCode, "@",
"GamR::TK::TwoTailStepGaussianPeak", payloadCode, "@",
"GamR::TK::operator<<", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_toolkit",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_toolkit_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_toolkit_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_toolkit() {
  TriggerDictionaryInitialization_libgamr_toolkit_Impl();
}
