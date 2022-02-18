// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_angdist
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
#include "PopulationParameter.hh"
#include "WignerD.hh"
#include "AngDist.hh"
#include "AngCorr.hh"
#include "TDPAD.hh"
#include "GaussianDistr.hh"
#include "StatTensor.hh"
#include "SolidAttenuation.hh"

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
            instance("GamR", 0 /*version*/, "PopulationParameter.hh", 19,
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
   namespace AngDist {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLAngDist_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::AngDist", 0 /*version*/, "PopulationParameter.hh", 20,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLAngDist_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLAngDist_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   static TClass *GamRcLcLAngDistcLcLPopulationParameter_Dictionary();
   static void GamRcLcLAngDistcLcLPopulationParameter_TClassManip(TClass*);
   static void delete_GamRcLcLAngDistcLcLPopulationParameter(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLPopulationParameter(void *p);
   static void destruct_GamRcLcLAngDistcLcLPopulationParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::PopulationParameter*)
   {
      ::GamR::AngDist::PopulationParameter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::AngDist::PopulationParameter));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::PopulationParameter", "PopulationParameter.hh", 22,
                  typeid(::GamR::AngDist::PopulationParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLAngDistcLcLPopulationParameter_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::PopulationParameter) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLPopulationParameter);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLPopulationParameter);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLPopulationParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::PopulationParameter*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::PopulationParameter*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::PopulationParameter*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLAngDistcLcLPopulationParameter_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::PopulationParameter*)nullptr)->GetClass();
      GamRcLcLAngDistcLcLPopulationParameter_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLAngDistcLcLPopulationParameter_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/angdist/PopulationParameter.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLAngDistcLcLSolidAttenuation_Dictionary();
   static void GamRcLcLAngDistcLcLSolidAttenuation_TClassManip(TClass*);
   static void delete_GamRcLcLAngDistcLcLSolidAttenuation(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLSolidAttenuation(void *p);
   static void destruct_GamRcLcLAngDistcLcLSolidAttenuation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::SolidAttenuation*)
   {
      ::GamR::AngDist::SolidAttenuation *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::AngDist::SolidAttenuation));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::SolidAttenuation", "SolidAttenuation.hh", 22,
                  typeid(::GamR::AngDist::SolidAttenuation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLAngDistcLcLSolidAttenuation_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::SolidAttenuation) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLSolidAttenuation);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLSolidAttenuation);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLSolidAttenuation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::SolidAttenuation*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::SolidAttenuation*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::SolidAttenuation*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLAngDistcLcLSolidAttenuation_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::SolidAttenuation*)nullptr)->GetClass();
      GamRcLcLAngDistcLcLSolidAttenuation_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLAngDistcLcLSolidAttenuation_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/angdist/SolidAttenuation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLAngDistcLcLStatTensor_Dictionary();
   static void GamRcLcLAngDistcLcLStatTensor_TClassManip(TClass*);
   static void delete_GamRcLcLAngDistcLcLStatTensor(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLStatTensor(void *p);
   static void destruct_GamRcLcLAngDistcLcLStatTensor(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::StatTensor*)
   {
      ::GamR::AngDist::StatTensor *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::AngDist::StatTensor));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::StatTensor", "StatTensor.hh", 22,
                  typeid(::GamR::AngDist::StatTensor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLAngDistcLcLStatTensor_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::StatTensor) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLStatTensor);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLStatTensor);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLStatTensor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::StatTensor*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::StatTensor*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::StatTensor*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLAngDistcLcLStatTensor_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::StatTensor*)nullptr)->GetClass();
      GamRcLcLAngDistcLcLStatTensor_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLAngDistcLcLStatTensor_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/angdist/StatTensor.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLAngDistcLcLAngCorr_Dictionary();
   static void GamRcLcLAngDistcLcLAngCorr_TClassManip(TClass*);
   static void delete_GamRcLcLAngDistcLcLAngCorr(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLAngCorr(void *p);
   static void destruct_GamRcLcLAngDistcLcLAngCorr(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::AngCorr*)
   {
      ::GamR::AngDist::AngCorr *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::AngDist::AngCorr));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::AngCorr", "AngCorr.hh", 30,
                  typeid(::GamR::AngDist::AngCorr), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLAngDistcLcLAngCorr_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::AngCorr) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLAngCorr);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLAngCorr);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLAngCorr);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::AngCorr*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::AngCorr*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::AngCorr*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLAngDistcLcLAngCorr_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::AngCorr*)nullptr)->GetClass();
      GamRcLcLAngDistcLcLAngCorr_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLAngDistcLcLAngCorr_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/angdist/AngCorr.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_GamRcLcLAngDistcLcLAngCorrFit(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLAngCorrFit(void *p);
   static void destruct_GamRcLcLAngDistcLcLAngCorrFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::AngCorrFit*)
   {
      ::GamR::AngDist::AngCorrFit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::AngDist::AngCorrFit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::AngCorrFit", ::GamR::AngDist::AngCorrFit::Class_Version(), "AngCorr.hh", 76,
                  typeid(::GamR::AngDist::AngCorrFit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::AngDist::AngCorrFit::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::AngCorrFit) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLAngCorrFit);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLAngCorrFit);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLAngCorrFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::AngCorrFit*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::AngCorrFit*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::AngCorrFit*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLAngDistcLcLSpinPrec_Dictionary();
   static void GamRcLcLAngDistcLcLSpinPrec_TClassManip(TClass*);
   static void delete_GamRcLcLAngDistcLcLSpinPrec(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLSpinPrec(void *p);
   static void destruct_GamRcLcLAngDistcLcLSpinPrec(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::SpinPrec*)
   {
      ::GamR::AngDist::SpinPrec *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::AngDist::SpinPrec));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::SpinPrec", "TDPAD.hh", 33,
                  typeid(::GamR::AngDist::SpinPrec), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLAngDistcLcLSpinPrec_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::SpinPrec) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLSpinPrec);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLSpinPrec);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLSpinPrec);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::SpinPrec*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::SpinPrec*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::SpinPrec*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLAngDistcLcLSpinPrec_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::SpinPrec*)nullptr)->GetClass();
      GamRcLcLAngDistcLcLSpinPrec_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLAngDistcLcLSpinPrec_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/angdist/TDPAD.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLAngDistcLcLGaussianDistr_Dictionary();
   static void GamRcLcLAngDistcLcLGaussianDistr_TClassManip(TClass*);
   static void delete_GamRcLcLAngDistcLcLGaussianDistr(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLGaussianDistr(void *p);
   static void destruct_GamRcLcLAngDistcLcLGaussianDistr(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::GaussianDistr*)
   {
      ::GamR::AngDist::GaussianDistr *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::AngDist::GaussianDistr));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::GaussianDistr", "GaussianDistr.hh", 19,
                  typeid(::GamR::AngDist::GaussianDistr), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLAngDistcLcLGaussianDistr_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::GaussianDistr) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLGaussianDistr);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLGaussianDistr);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLGaussianDistr);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::GaussianDistr*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::GaussianDistr*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::GaussianDistr*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLAngDistcLcLGaussianDistr_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::GaussianDistr*)nullptr)->GetClass();
      GamRcLcLAngDistcLcLGaussianDistr_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLAngDistcLcLGaussianDistr_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/angdist/GaussianDistr.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLAngDistcLcLDoubleGaussianDistr_Dictionary();
   static void GamRcLcLAngDistcLcLDoubleGaussianDistr_TClassManip(TClass*);
   static void delete_GamRcLcLAngDistcLcLDoubleGaussianDistr(void *p);
   static void deleteArray_GamRcLcLAngDistcLcLDoubleGaussianDistr(void *p);
   static void destruct_GamRcLcLAngDistcLcLDoubleGaussianDistr(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::AngDist::DoubleGaussianDistr*)
   {
      ::GamR::AngDist::DoubleGaussianDistr *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::AngDist::DoubleGaussianDistr));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::AngDist::DoubleGaussianDistr", "GaussianDistr.hh", 116,
                  typeid(::GamR::AngDist::DoubleGaussianDistr), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLAngDistcLcLDoubleGaussianDistr_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::AngDist::DoubleGaussianDistr) );
      instance.SetDelete(&delete_GamRcLcLAngDistcLcLDoubleGaussianDistr);
      instance.SetDeleteArray(&deleteArray_GamRcLcLAngDistcLcLDoubleGaussianDistr);
      instance.SetDestructor(&destruct_GamRcLcLAngDistcLcLDoubleGaussianDistr);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::AngDist::DoubleGaussianDistr*)
   {
      return GenerateInitInstanceLocal((::GamR::AngDist::DoubleGaussianDistr*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::AngDist::DoubleGaussianDistr*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLAngDistcLcLDoubleGaussianDistr_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::DoubleGaussianDistr*)nullptr)->GetClass();
      GamRcLcLAngDistcLcLDoubleGaussianDistr_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLAngDistcLcLDoubleGaussianDistr_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/angdist/GaussianDistr.hh");
   }

} // end of namespace ROOT

namespace GamR {
   namespace AngDist {
//______________________________________________________________________________
atomic_TClass_ptr AngCorrFit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *AngCorrFit::Class_Name()
{
   return "GamR::AngDist::AngCorrFit";
}

//______________________________________________________________________________
const char *AngCorrFit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::AngCorrFit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int AngCorrFit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::AngCorrFit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AngCorrFit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::AngCorrFit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AngCorrFit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::AngDist::AngCorrFit*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::AngDist
} // namespace GamR::AngDist
namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLPopulationParameter(void *p) {
      delete ((::GamR::AngDist::PopulationParameter*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLPopulationParameter(void *p) {
      delete [] ((::GamR::AngDist::PopulationParameter*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLPopulationParameter(void *p) {
      typedef ::GamR::AngDist::PopulationParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::PopulationParameter

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLSolidAttenuation(void *p) {
      delete ((::GamR::AngDist::SolidAttenuation*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLSolidAttenuation(void *p) {
      delete [] ((::GamR::AngDist::SolidAttenuation*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLSolidAttenuation(void *p) {
      typedef ::GamR::AngDist::SolidAttenuation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::SolidAttenuation

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLStatTensor(void *p) {
      delete ((::GamR::AngDist::StatTensor*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLStatTensor(void *p) {
      delete [] ((::GamR::AngDist::StatTensor*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLStatTensor(void *p) {
      typedef ::GamR::AngDist::StatTensor current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::StatTensor

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLAngCorr(void *p) {
      delete ((::GamR::AngDist::AngCorr*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLAngCorr(void *p) {
      delete [] ((::GamR::AngDist::AngCorr*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLAngCorr(void *p) {
      typedef ::GamR::AngDist::AngCorr current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::AngCorr

namespace GamR {
   namespace AngDist {
//______________________________________________________________________________
void AngCorrFit::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::AngDist::AngCorrFit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::AngDist::AngCorrFit::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::AngDist::AngCorrFit::Class(),this);
   }
}

} // namespace GamR::AngDist
} // namespace GamR::AngDist
namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLAngCorrFit(void *p) {
      delete ((::GamR::AngDist::AngCorrFit*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLAngCorrFit(void *p) {
      delete [] ((::GamR::AngDist::AngCorrFit*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLAngCorrFit(void *p) {
      typedef ::GamR::AngDist::AngCorrFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::AngCorrFit

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLSpinPrec(void *p) {
      delete ((::GamR::AngDist::SpinPrec*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLSpinPrec(void *p) {
      delete [] ((::GamR::AngDist::SpinPrec*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLSpinPrec(void *p) {
      typedef ::GamR::AngDist::SpinPrec current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::SpinPrec

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLGaussianDistr(void *p) {
      delete ((::GamR::AngDist::GaussianDistr*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLGaussianDistr(void *p) {
      delete [] ((::GamR::AngDist::GaussianDistr*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLGaussianDistr(void *p) {
      typedef ::GamR::AngDist::GaussianDistr current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::GaussianDistr

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLAngDistcLcLDoubleGaussianDistr(void *p) {
      delete ((::GamR::AngDist::DoubleGaussianDistr*)p);
   }
   static void deleteArray_GamRcLcLAngDistcLcLDoubleGaussianDistr(void *p) {
      delete [] ((::GamR::AngDist::DoubleGaussianDistr*)p);
   }
   static void destruct_GamRcLcLAngDistcLcLDoubleGaussianDistr(void *p) {
      typedef ::GamR::AngDist::DoubleGaussianDistr current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::AngDist::DoubleGaussianDistr

namespace ROOT {
   static TClass *vectorlEvectorlEcomplexlEdoublegRsPgRsPgR_Dictionary();
   static void vectorlEvectorlEcomplexlEdoublegRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p);
   static void destruct_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<complex<double> > >*)
   {
      vector<vector<complex<double> > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<complex<double> > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<complex<double> > >", -2, "c++/v1/vector", 471,
                  typeid(vector<vector<complex<double> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEcomplexlEdoublegRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<complex<double> > >) );
      instance.SetNew(&new_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<complex<double> > > >()));

      ::ROOT::AddClassAlternate("vector<vector<complex<double> > >","std::__1::vector<std::__1::vector<std::__1::complex<double>, std::__1::allocator<std::__1::complex<double> > >, std::__1::allocator<std::__1::vector<std::__1::complex<double>, std::__1::allocator<std::__1::complex<double> > > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<complex<double> > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEcomplexlEdoublegRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<complex<double> > >*)nullptr)->GetClass();
      vectorlEvectorlEcomplexlEdoublegRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEcomplexlEdoublegRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<complex<double> > > : new vector<vector<complex<double> > >;
   }
   static void *newArray_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<complex<double> > >[nElements] : new vector<vector<complex<double> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p) {
      delete ((vector<vector<complex<double> > >*)p);
   }
   static void deleteArray_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p) {
      delete [] ((vector<vector<complex<double> > >*)p);
   }
   static void destruct_vectorlEvectorlEcomplexlEdoublegRsPgRsPgR(void *p) {
      typedef vector<vector<complex<double> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<complex<double> > >

namespace ROOT {
   static TClass *vectorlEshortgR_Dictionary();
   static void vectorlEshortgR_TClassManip(TClass*);
   static void *new_vectorlEshortgR(void *p = nullptr);
   static void *newArray_vectorlEshortgR(Long_t size, void *p);
   static void delete_vectorlEshortgR(void *p);
   static void deleteArray_vectorlEshortgR(void *p);
   static void destruct_vectorlEshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<short>*)
   {
      vector<short> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<short>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<short>", -2, "c++/v1/vector", 471,
                  typeid(vector<short>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEshortgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<short>) );
      instance.SetNew(&new_vectorlEshortgR);
      instance.SetNewArray(&newArray_vectorlEshortgR);
      instance.SetDelete(&delete_vectorlEshortgR);
      instance.SetDeleteArray(&deleteArray_vectorlEshortgR);
      instance.SetDestructor(&destruct_vectorlEshortgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<short> >()));

      ::ROOT::AddClassAlternate("vector<short>","std::__1::vector<short, std::__1::allocator<short> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<short>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<short>*)nullptr)->GetClass();
      vectorlEshortgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEshortgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<short> : new vector<short>;
   }
   static void *newArray_vectorlEshortgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<short>[nElements] : new vector<short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEshortgR(void *p) {
      delete ((vector<short>*)p);
   }
   static void deleteArray_vectorlEshortgR(void *p) {
      delete [] ((vector<short>*)p);
   }
   static void destruct_vectorlEshortgR(void *p) {
      typedef vector<short> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<short>

namespace ROOT {
   static TClass *vectorlEpairlEdoublecOdoublegRsPgR_Dictionary();
   static void vectorlEpairlEdoublecOdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEpairlEdoublecOdoublegRsPgR(void *p = nullptr);
   static void *newArray_vectorlEpairlEdoublecOdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEpairlEdoublecOdoublegRsPgR(void *p);
   static void deleteArray_vectorlEpairlEdoublecOdoublegRsPgR(void *p);
   static void destruct_vectorlEpairlEdoublecOdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<pair<double,double> >*)
   {
      vector<pair<double,double> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<pair<double,double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<pair<double,double> >", -2, "c++/v1/vector", 471,
                  typeid(vector<pair<double,double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEpairlEdoublecOdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<pair<double,double> >) );
      instance.SetNew(&new_vectorlEpairlEdoublecOdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEpairlEdoublecOdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEpairlEdoublecOdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEpairlEdoublecOdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEpairlEdoublecOdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<pair<double,double> > >()));

      ::ROOT::AddClassAlternate("vector<pair<double,double> >","std::__1::vector<std::__1::pair<double, double>, std::__1::allocator<std::__1::pair<double, double> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<pair<double,double> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEpairlEdoublecOdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<pair<double,double> >*)nullptr)->GetClass();
      vectorlEpairlEdoublecOdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEpairlEdoublecOdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEpairlEdoublecOdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<double,double> > : new vector<pair<double,double> >;
   }
   static void *newArray_vectorlEpairlEdoublecOdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<double,double> >[nElements] : new vector<pair<double,double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEpairlEdoublecOdoublegRsPgR(void *p) {
      delete ((vector<pair<double,double> >*)p);
   }
   static void deleteArray_vectorlEpairlEdoublecOdoublegRsPgR(void *p) {
      delete [] ((vector<pair<double,double> >*)p);
   }
   static void destruct_vectorlEpairlEdoublecOdoublegRsPgR(void *p) {
      typedef vector<pair<double,double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<pair<double,double> >

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = nullptr);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "c++/v1/vector", 471,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      ::ROOT::AddClassAlternate("vector<int>","std::__1::vector<int, std::__1::allocator<int> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)nullptr)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = nullptr);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "c++/v1/vector", 471,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      ::ROOT::AddClassAlternate("vector<double>","std::__1::vector<double, std::__1::allocator<double> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)nullptr)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEcomplexlEdoublegRsPgR_Dictionary();
   static void vectorlEcomplexlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEcomplexlEdoublegRsPgR(void *p = nullptr);
   static void *newArray_vectorlEcomplexlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEcomplexlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEcomplexlEdoublegRsPgR(void *p);
   static void destruct_vectorlEcomplexlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<complex<double> >*)
   {
      vector<complex<double> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<complex<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<complex<double> >", -2, "c++/v1/vector", 471,
                  typeid(vector<complex<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEcomplexlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<complex<double> >) );
      instance.SetNew(&new_vectorlEcomplexlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEcomplexlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEcomplexlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEcomplexlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEcomplexlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<complex<double> > >()));

      ::ROOT::AddClassAlternate("vector<complex<double> >","std::__1::vector<std::__1::complex<double>, std::__1::allocator<std::__1::complex<double> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<complex<double> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEcomplexlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<complex<double> >*)nullptr)->GetClass();
      vectorlEcomplexlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEcomplexlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEcomplexlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<complex<double> > : new vector<complex<double> >;
   }
   static void *newArray_vectorlEcomplexlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<complex<double> >[nElements] : new vector<complex<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEcomplexlEdoublegRsPgR(void *p) {
      delete ((vector<complex<double> >*)p);
   }
   static void deleteArray_vectorlEcomplexlEdoublegRsPgR(void *p) {
      delete [] ((vector<complex<double> >*)p);
   }
   static void destruct_vectorlEcomplexlEdoublegRsPgR(void *p) {
      typedef vector<complex<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<complex<double> >

namespace ROOT {
   static TClass *vectorlETGraphmUgR_Dictionary();
   static void vectorlETGraphmUgR_TClassManip(TClass*);
   static void *new_vectorlETGraphmUgR(void *p = nullptr);
   static void *newArray_vectorlETGraphmUgR(Long_t size, void *p);
   static void delete_vectorlETGraphmUgR(void *p);
   static void deleteArray_vectorlETGraphmUgR(void *p);
   static void destruct_vectorlETGraphmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGraph*>*)
   {
      vector<TGraph*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGraph*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGraph*>", -2, "c++/v1/vector", 471,
                  typeid(vector<TGraph*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGraphmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGraph*>) );
      instance.SetNew(&new_vectorlETGraphmUgR);
      instance.SetNewArray(&newArray_vectorlETGraphmUgR);
      instance.SetDelete(&delete_vectorlETGraphmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGraphmUgR);
      instance.SetDestructor(&destruct_vectorlETGraphmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGraph*> >()));

      ::ROOT::AddClassAlternate("vector<TGraph*>","std::__1::vector<TGraph*, std::__1::allocator<TGraph*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TGraph*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGraphmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TGraph*>*)nullptr)->GetClass();
      vectorlETGraphmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGraphmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGraphmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGraph*> : new vector<TGraph*>;
   }
   static void *newArray_vectorlETGraphmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGraph*>[nElements] : new vector<TGraph*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGraphmUgR(void *p) {
      delete ((vector<TGraph*>*)p);
   }
   static void deleteArray_vectorlETGraphmUgR(void *p) {
      delete [] ((vector<TGraph*>*)p);
   }
   static void destruct_vectorlETGraphmUgR(void *p) {
      typedef vector<TGraph*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TGraph*>

namespace ROOT {
   static TClass *vectorlETF1mUgR_Dictionary();
   static void vectorlETF1mUgR_TClassManip(TClass*);
   static void *new_vectorlETF1mUgR(void *p = nullptr);
   static void *newArray_vectorlETF1mUgR(Long_t size, void *p);
   static void delete_vectorlETF1mUgR(void *p);
   static void deleteArray_vectorlETF1mUgR(void *p);
   static void destruct_vectorlETF1mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TF1*>*)
   {
      vector<TF1*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TF1*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TF1*>", -2, "c++/v1/vector", 471,
                  typeid(vector<TF1*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETF1mUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TF1*>) );
      instance.SetNew(&new_vectorlETF1mUgR);
      instance.SetNewArray(&newArray_vectorlETF1mUgR);
      instance.SetDelete(&delete_vectorlETF1mUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETF1mUgR);
      instance.SetDestructor(&destruct_vectorlETF1mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TF1*> >()));

      ::ROOT::AddClassAlternate("vector<TF1*>","std::__1::vector<TF1*, std::__1::allocator<TF1*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TF1*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETF1mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TF1*>*)nullptr)->GetClass();
      vectorlETF1mUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETF1mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETF1mUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TF1*> : new vector<TF1*>;
   }
   static void *newArray_vectorlETF1mUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TF1*>[nElements] : new vector<TF1*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETF1mUgR(void *p) {
      delete ((vector<TF1*>*)p);
   }
   static void deleteArray_vectorlETF1mUgR(void *p) {
      delete [] ((vector<TF1*>*)p);
   }
   static void destruct_vectorlETF1mUgR(void *p) {
      typedef vector<TF1*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TF1*>

namespace ROOT {
   static TClass *vectorlEGamRcLcLAngDistcLcLAngCorrmUgR_Dictionary();
   static void vectorlEGamRcLcLAngDistcLcLAngCorrmUgR_TClassManip(TClass*);
   static void *new_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p = nullptr);
   static void *newArray_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(Long_t size, void *p);
   static void delete_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p);
   static void deleteArray_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p);
   static void destruct_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GamR::AngDist::AngCorr*>*)
   {
      vector<GamR::AngDist::AngCorr*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GamR::AngDist::AngCorr*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GamR::AngDist::AngCorr*>", -2, "c++/v1/vector", 471,
                  typeid(vector<GamR::AngDist::AngCorr*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGamRcLcLAngDistcLcLAngCorrmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GamR::AngDist::AngCorr*>) );
      instance.SetNew(&new_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR);
      instance.SetNewArray(&newArray_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR);
      instance.SetDelete(&delete_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR);
      instance.SetDestructor(&destruct_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GamR::AngDist::AngCorr*> >()));

      ::ROOT::AddClassAlternate("vector<GamR::AngDist::AngCorr*>","std::__1::vector<GamR::AngDist::AngCorr*, std::__1::allocator<GamR::AngDist::AngCorr*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GamR::AngDist::AngCorr*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGamRcLcLAngDistcLcLAngCorrmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GamR::AngDist::AngCorr*>*)nullptr)->GetClass();
      vectorlEGamRcLcLAngDistcLcLAngCorrmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGamRcLcLAngDistcLcLAngCorrmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::AngDist::AngCorr*> : new vector<GamR::AngDist::AngCorr*>;
   }
   static void *newArray_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::AngDist::AngCorr*>[nElements] : new vector<GamR::AngDist::AngCorr*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p) {
      delete ((vector<GamR::AngDist::AngCorr*>*)p);
   }
   static void deleteArray_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p) {
      delete [] ((vector<GamR::AngDist::AngCorr*>*)p);
   }
   static void destruct_vectorlEGamRcLcLAngDistcLcLAngCorrmUgR(void *p) {
      typedef vector<GamR::AngDist::AngCorr*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GamR::AngDist::AngCorr*>

namespace {
  void TriggerDictionaryInitialization_libgamr_angdist_Impl() {
    static const char* headers[] = {
"PopulationParameter.hh",
"WignerD.hh",
"AngDist.hh",
"AngCorr.hh",
"TDPAD.hh",
"GaussianDistr.hh",
"StatTensor.hh",
"SolidAttenuation.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/angdist",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/angdist",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/angdist/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_angdist dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/PopulationParameter.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$PopulationParameter.hh")))  PopulationParameter;}}
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/SolidAttenuation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$SolidAttenuation.hh")))  __attribute__((annotate("$clingAutoload$AngDist.hh")))  SolidAttenuation;}}
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/StatTensor.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$StatTensor.hh")))  __attribute__((annotate("$clingAutoload$AngDist.hh")))  StatTensor;}}
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/AngCorr.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AngCorr.hh")))  AngCorr;}}
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/AngCorr.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AngCorr.hh")))  AngCorrFit;}}
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/TDPAD.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$TDPAD.hh")))  SpinPrec;}}
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/GaussianDistr.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$GaussianDistr.hh")))  GaussianDistr;}}
namespace GamR{namespace AngDist{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/angdist/GaussianDistr.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$GaussianDistr.hh")))  DoubleGaussianDistr;}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_angdist dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "PopulationParameter.hh"
#include "WignerD.hh"
#include "AngDist.hh"
#include "AngCorr.hh"
#include "TDPAD.hh"
#include "GaussianDistr.hh"
#include "StatTensor.hh"
#include "SolidAttenuation.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::AngDist::Agen", payloadCode, "@",
"GamR::AngDist::Ak", payloadCode, "@",
"GamR::AngDist::AngCorr", payloadCode, "@",
"GamR::AngDist::AngCorrFit", payloadCode, "@",
"GamR::AngDist::AngCorrFit::fgIsA", payloadCode, "@",
"GamR::AngDist::AutoCorrelation", payloadCode, "@",
"GamR::AngDist::BigD", payloadCode, "@",
"GamR::AngDist::DoubleGaussianDistr", payloadCode, "@",
"GamR::AngDist::Fgen", payloadCode, "@",
"GamR::AngDist::Fk", payloadCode, "@",
"GamR::AngDist::GaussianDistr", payloadCode, "@",
"GamR::AngDist::GetTauG", payloadCode, "@",
"GamR::AngDist::PopulationParameter", payloadCode, "@",
"GamR::AngDist::RatioFunction", payloadCode, "@",
"GamR::AngDist::SolidAttenuation", payloadCode, "@",
"GamR::AngDist::SpinPrec", payloadCode, "@",
"GamR::AngDist::StatTensor", payloadCode, "@",
"GamR::AngDist::TransFrame", payloadCode, "@",
"GamR::AngDist::W", payloadCode, "@",
"GamR::AngDist::djmm", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_angdist",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_angdist_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_angdist_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_angdist() {
  TriggerDictionaryInitialization_libgamr_angdist_Impl();
}
