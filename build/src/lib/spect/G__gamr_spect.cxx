// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_spect
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
#include "IO.hh"
#include "Cut.hh"
#include "Integral.hh"
#include "Transform.hh"
#include "Fit.hh"
#include "FitGuesses.hh"
#include "Display.hh"
#include "FFT.hh"
#include "BackSub.hh"
#include "Calibrate.hh"

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
            instance("GamR", 0 /*version*/, "IO.hh", 15,
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
   namespace Spect {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLSpect_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Spect", 0 /*version*/, "IO.hh", 16,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLSpect_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLSpect_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   static TClass *GamRcLcLSpectcLcLParameter_Dictionary();
   static void GamRcLcLSpectcLcLParameter_TClassManip(TClass*);
   static void *new_GamRcLcLSpectcLcLParameter(void *p = nullptr);
   static void *newArray_GamRcLcLSpectcLcLParameter(Long_t size, void *p);
   static void delete_GamRcLcLSpectcLcLParameter(void *p);
   static void deleteArray_GamRcLcLSpectcLcLParameter(void *p);
   static void destruct_GamRcLcLSpectcLcLParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Spect::Parameter*)
   {
      ::GamR::Spect::Parameter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Spect::Parameter));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Spect::Parameter", "FitGuesses.hh", 17,
                  typeid(::GamR::Spect::Parameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLSpectcLcLParameter_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Spect::Parameter) );
      instance.SetNew(&new_GamRcLcLSpectcLcLParameter);
      instance.SetNewArray(&newArray_GamRcLcLSpectcLcLParameter);
      instance.SetDelete(&delete_GamRcLcLSpectcLcLParameter);
      instance.SetDeleteArray(&deleteArray_GamRcLcLSpectcLcLParameter);
      instance.SetDestructor(&destruct_GamRcLcLSpectcLcLParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Spect::Parameter*)
   {
      return GenerateInitInstanceLocal((::GamR::Spect::Parameter*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Spect::Parameter*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLSpectcLcLParameter_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Spect::Parameter*)nullptr)->GetClass();
      GamRcLcLSpectcLcLParameter_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLSpectcLcLParameter_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/spect/FitGuesses.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLSpectcLcLPeakFitGuesses_Dictionary();
   static void GamRcLcLSpectcLcLPeakFitGuesses_TClassManip(TClass*);
   static void *new_GamRcLcLSpectcLcLPeakFitGuesses(void *p = nullptr);
   static void *newArray_GamRcLcLSpectcLcLPeakFitGuesses(Long_t size, void *p);
   static void delete_GamRcLcLSpectcLcLPeakFitGuesses(void *p);
   static void deleteArray_GamRcLcLSpectcLcLPeakFitGuesses(void *p);
   static void destruct_GamRcLcLSpectcLcLPeakFitGuesses(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Spect::PeakFitGuesses*)
   {
      ::GamR::Spect::PeakFitGuesses *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Spect::PeakFitGuesses));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Spect::PeakFitGuesses", "FitGuesses.hh", 23,
                  typeid(::GamR::Spect::PeakFitGuesses), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLSpectcLcLPeakFitGuesses_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Spect::PeakFitGuesses) );
      instance.SetNew(&new_GamRcLcLSpectcLcLPeakFitGuesses);
      instance.SetNewArray(&newArray_GamRcLcLSpectcLcLPeakFitGuesses);
      instance.SetDelete(&delete_GamRcLcLSpectcLcLPeakFitGuesses);
      instance.SetDeleteArray(&deleteArray_GamRcLcLSpectcLcLPeakFitGuesses);
      instance.SetDestructor(&destruct_GamRcLcLSpectcLcLPeakFitGuesses);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Spect::PeakFitGuesses*)
   {
      return GenerateInitInstanceLocal((::GamR::Spect::PeakFitGuesses*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Spect::PeakFitGuesses*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLSpectcLcLPeakFitGuesses_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Spect::PeakFitGuesses*)nullptr)->GetClass();
      GamRcLcLSpectcLcLPeakFitGuesses_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLSpectcLcLPeakFitGuesses_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/spect/FitGuesses.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLSpectcLcLPeakFit_Dictionary();
   static void GamRcLcLSpectcLcLPeakFit_TClassManip(TClass*);
   static void *new_GamRcLcLSpectcLcLPeakFit(void *p = nullptr);
   static void *newArray_GamRcLcLSpectcLcLPeakFit(Long_t size, void *p);
   static void delete_GamRcLcLSpectcLcLPeakFit(void *p);
   static void deleteArray_GamRcLcLSpectcLcLPeakFit(void *p);
   static void destruct_GamRcLcLSpectcLcLPeakFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Spect::PeakFit*)
   {
      ::GamR::Spect::PeakFit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Spect::PeakFit));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Spect::PeakFit", "Fit.hh", 18,
                  typeid(::GamR::Spect::PeakFit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLSpectcLcLPeakFit_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Spect::PeakFit) );
      instance.SetNew(&new_GamRcLcLSpectcLcLPeakFit);
      instance.SetNewArray(&newArray_GamRcLcLSpectcLcLPeakFit);
      instance.SetDelete(&delete_GamRcLcLSpectcLcLPeakFit);
      instance.SetDeleteArray(&deleteArray_GamRcLcLSpectcLcLPeakFit);
      instance.SetDestructor(&destruct_GamRcLcLSpectcLcLPeakFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Spect::PeakFit*)
   {
      return GenerateInitInstanceLocal((::GamR::Spect::PeakFit*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Spect::PeakFit*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLSpectcLcLPeakFit_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Spect::PeakFit*)nullptr)->GetClass();
      GamRcLcLSpectcLcLPeakFit_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLSpectcLcLPeakFit_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/spect/Fit.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLSpectcLcLPeakFitcLcLPeakParams_Dictionary();
   static void GamRcLcLSpectcLcLPeakFitcLcLPeakParams_TClassManip(TClass*);
   static void *new_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p = nullptr);
   static void *newArray_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(Long_t size, void *p);
   static void delete_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p);
   static void deleteArray_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p);
   static void destruct_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Spect::PeakFit::PeakParams*)
   {
      ::GamR::Spect::PeakFit::PeakParams *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Spect::PeakFit::PeakParams));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Spect::PeakFit::PeakParams", "Fit.hh", 20,
                  typeid(::GamR::Spect::PeakFit::PeakParams), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLSpectcLcLPeakFitcLcLPeakParams_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Spect::PeakFit::PeakParams) );
      instance.SetNew(&new_GamRcLcLSpectcLcLPeakFitcLcLPeakParams);
      instance.SetNewArray(&newArray_GamRcLcLSpectcLcLPeakFitcLcLPeakParams);
      instance.SetDelete(&delete_GamRcLcLSpectcLcLPeakFitcLcLPeakParams);
      instance.SetDeleteArray(&deleteArray_GamRcLcLSpectcLcLPeakFitcLcLPeakParams);
      instance.SetDestructor(&destruct_GamRcLcLSpectcLcLPeakFitcLcLPeakParams);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Spect::PeakFit::PeakParams*)
   {
      return GenerateInitInstanceLocal((::GamR::Spect::PeakFit::PeakParams*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Spect::PeakFit::PeakParams*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLSpectcLcLPeakFitcLcLPeakParams_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Spect::PeakFit::PeakParams*)nullptr)->GetClass();
      GamRcLcLSpectcLcLPeakFitcLcLPeakParams_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLSpectcLcLPeakFitcLcLPeakParams_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/spect/Fit.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLSpectcLcLPeakFitcLcLParameters_Dictionary();
   static void GamRcLcLSpectcLcLPeakFitcLcLParameters_TClassManip(TClass*);
   static void *new_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p = nullptr);
   static void *newArray_GamRcLcLSpectcLcLPeakFitcLcLParameters(Long_t size, void *p);
   static void delete_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p);
   static void deleteArray_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p);
   static void destruct_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Spect::PeakFit::Parameters*)
   {
      ::GamR::Spect::PeakFit::Parameters *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Spect::PeakFit::Parameters));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Spect::PeakFit::Parameters", "Fit.hh", 31,
                  typeid(::GamR::Spect::PeakFit::Parameters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLSpectcLcLPeakFitcLcLParameters_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Spect::PeakFit::Parameters) );
      instance.SetNew(&new_GamRcLcLSpectcLcLPeakFitcLcLParameters);
      instance.SetNewArray(&newArray_GamRcLcLSpectcLcLPeakFitcLcLParameters);
      instance.SetDelete(&delete_GamRcLcLSpectcLcLPeakFitcLcLParameters);
      instance.SetDeleteArray(&deleteArray_GamRcLcLSpectcLcLPeakFitcLcLParameters);
      instance.SetDestructor(&destruct_GamRcLcLSpectcLcLPeakFitcLcLParameters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Spect::PeakFit::Parameters*)
   {
      return GenerateInitInstanceLocal((::GamR::Spect::PeakFit::Parameters*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Spect::PeakFit::Parameters*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLSpectcLcLPeakFitcLcLParameters_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Spect::PeakFit::Parameters*)nullptr)->GetClass();
      GamRcLcLSpectcLcLPeakFitcLcLParameters_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLSpectcLcLPeakFitcLcLParameters_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/spect/Fit.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLSpectcLcLBackSub2D_Dictionary();
   static void GamRcLcLSpectcLcLBackSub2D_TClassManip(TClass*);
   static void delete_GamRcLcLSpectcLcLBackSub2D(void *p);
   static void deleteArray_GamRcLcLSpectcLcLBackSub2D(void *p);
   static void destruct_GamRcLcLSpectcLcLBackSub2D(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Spect::BackSub2D*)
   {
      ::GamR::Spect::BackSub2D *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Spect::BackSub2D));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Spect::BackSub2D", "BackSub.hh", 13,
                  typeid(::GamR::Spect::BackSub2D), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLSpectcLcLBackSub2D_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Spect::BackSub2D) );
      instance.SetDelete(&delete_GamRcLcLSpectcLcLBackSub2D);
      instance.SetDeleteArray(&deleteArray_GamRcLcLSpectcLcLBackSub2D);
      instance.SetDestructor(&destruct_GamRcLcLSpectcLcLBackSub2D);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Spect::BackSub2D*)
   {
      return GenerateInitInstanceLocal((::GamR::Spect::BackSub2D*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Spect::BackSub2D*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLSpectcLcLBackSub2D_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Spect::BackSub2D*)nullptr)->GetClass();
      GamRcLcLSpectcLcLBackSub2D_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLSpectcLcLBackSub2D_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/spect/BackSub.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLSpectcLcLParameter(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::Parameter : new ::GamR::Spect::Parameter;
   }
   static void *newArray_GamRcLcLSpectcLcLParameter(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::Parameter[nElements] : new ::GamR::Spect::Parameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLSpectcLcLParameter(void *p) {
      delete ((::GamR::Spect::Parameter*)p);
   }
   static void deleteArray_GamRcLcLSpectcLcLParameter(void *p) {
      delete [] ((::GamR::Spect::Parameter*)p);
   }
   static void destruct_GamRcLcLSpectcLcLParameter(void *p) {
      typedef ::GamR::Spect::Parameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Spect::Parameter

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLSpectcLcLPeakFitGuesses(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFitGuesses : new ::GamR::Spect::PeakFitGuesses;
   }
   static void *newArray_GamRcLcLSpectcLcLPeakFitGuesses(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFitGuesses[nElements] : new ::GamR::Spect::PeakFitGuesses[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLSpectcLcLPeakFitGuesses(void *p) {
      delete ((::GamR::Spect::PeakFitGuesses*)p);
   }
   static void deleteArray_GamRcLcLSpectcLcLPeakFitGuesses(void *p) {
      delete [] ((::GamR::Spect::PeakFitGuesses*)p);
   }
   static void destruct_GamRcLcLSpectcLcLPeakFitGuesses(void *p) {
      typedef ::GamR::Spect::PeakFitGuesses current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Spect::PeakFitGuesses

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLSpectcLcLPeakFit(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFit : new ::GamR::Spect::PeakFit;
   }
   static void *newArray_GamRcLcLSpectcLcLPeakFit(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFit[nElements] : new ::GamR::Spect::PeakFit[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLSpectcLcLPeakFit(void *p) {
      delete ((::GamR::Spect::PeakFit*)p);
   }
   static void deleteArray_GamRcLcLSpectcLcLPeakFit(void *p) {
      delete [] ((::GamR::Spect::PeakFit*)p);
   }
   static void destruct_GamRcLcLSpectcLcLPeakFit(void *p) {
      typedef ::GamR::Spect::PeakFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Spect::PeakFit

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFit::PeakParams : new ::GamR::Spect::PeakFit::PeakParams;
   }
   static void *newArray_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFit::PeakParams[nElements] : new ::GamR::Spect::PeakFit::PeakParams[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p) {
      delete ((::GamR::Spect::PeakFit::PeakParams*)p);
   }
   static void deleteArray_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p) {
      delete [] ((::GamR::Spect::PeakFit::PeakParams*)p);
   }
   static void destruct_GamRcLcLSpectcLcLPeakFitcLcLPeakParams(void *p) {
      typedef ::GamR::Spect::PeakFit::PeakParams current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Spect::PeakFit::PeakParams

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFit::Parameters : new ::GamR::Spect::PeakFit::Parameters;
   }
   static void *newArray_GamRcLcLSpectcLcLPeakFitcLcLParameters(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Spect::PeakFit::Parameters[nElements] : new ::GamR::Spect::PeakFit::Parameters[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p) {
      delete ((::GamR::Spect::PeakFit::Parameters*)p);
   }
   static void deleteArray_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p) {
      delete [] ((::GamR::Spect::PeakFit::Parameters*)p);
   }
   static void destruct_GamRcLcLSpectcLcLPeakFitcLcLParameters(void *p) {
      typedef ::GamR::Spect::PeakFit::Parameters current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Spect::PeakFit::Parameters

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLSpectcLcLBackSub2D(void *p) {
      delete ((::GamR::Spect::BackSub2D*)p);
   }
   static void deleteArray_GamRcLcLSpectcLcLBackSub2D(void *p) {
      delete [] ((::GamR::Spect::BackSub2D*)p);
   }
   static void destruct_GamRcLcLSpectcLcLBackSub2D(void *p) {
      typedef ::GamR::Spect::BackSub2D current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Spect::BackSub2D

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
   static TClass *maplEstringcOintgR_Dictionary();
   static void maplEstringcOintgR_TClassManip(TClass*);
   static void *new_maplEstringcOintgR(void *p = nullptr);
   static void *newArray_maplEstringcOintgR(Long_t size, void *p);
   static void delete_maplEstringcOintgR(void *p);
   static void deleteArray_maplEstringcOintgR(void *p);
   static void destruct_maplEstringcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,int>*)
   {
      map<string,int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,int>", -2, "c++/v1/map", 900,
                  typeid(map<string,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,int>) );
      instance.SetNew(&new_maplEstringcOintgR);
      instance.SetNewArray(&newArray_maplEstringcOintgR);
      instance.SetDelete(&delete_maplEstringcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOintgR);
      instance.SetDestructor(&destruct_maplEstringcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,int> >()));

      ::ROOT::AddClassAlternate("map<string,int>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, int, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, int> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,int>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,int>*)nullptr)->GetClass();
      maplEstringcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int> : new map<string,int>;
   }
   static void *newArray_maplEstringcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int>[nElements] : new map<string,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOintgR(void *p) {
      delete ((map<string,int>*)p);
   }
   static void deleteArray_maplEstringcOintgR(void *p) {
      delete [] ((map<string,int>*)p);
   }
   static void destruct_maplEstringcOintgR(void *p) {
      typedef map<string,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,int>

namespace ROOT {
   static TClass *maplEstringcOGamRcLcLTKcLcLFPeakmUgR_Dictionary();
   static void maplEstringcOGamRcLcLTKcLcLFPeakmUgR_TClassManip(TClass*);
   static void *new_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p = nullptr);
   static void *newArray_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(Long_t size, void *p);
   static void delete_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p);
   static void deleteArray_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p);
   static void destruct_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,GamR::TK::FPeak*>*)
   {
      map<string,GamR::TK::FPeak*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,GamR::TK::FPeak*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,GamR::TK::FPeak*>", -2, "c++/v1/map", 900,
                  typeid(map<string,GamR::TK::FPeak*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOGamRcLcLTKcLcLFPeakmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,GamR::TK::FPeak*>) );
      instance.SetNew(&new_maplEstringcOGamRcLcLTKcLcLFPeakmUgR);
      instance.SetNewArray(&newArray_maplEstringcOGamRcLcLTKcLcLFPeakmUgR);
      instance.SetDelete(&delete_maplEstringcOGamRcLcLTKcLcLFPeakmUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOGamRcLcLTKcLcLFPeakmUgR);
      instance.SetDestructor(&destruct_maplEstringcOGamRcLcLTKcLcLFPeakmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,GamR::TK::FPeak*> >()));

      ::ROOT::AddClassAlternate("map<string,GamR::TK::FPeak*>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, GamR::TK::FPeak*, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, GamR::TK::FPeak*> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,GamR::TK::FPeak*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOGamRcLcLTKcLcLFPeakmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,GamR::TK::FPeak*>*)nullptr)->GetClass();
      maplEstringcOGamRcLcLTKcLcLFPeakmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOGamRcLcLTKcLcLFPeakmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::TK::FPeak*> : new map<string,GamR::TK::FPeak*>;
   }
   static void *newArray_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::TK::FPeak*>[nElements] : new map<string,GamR::TK::FPeak*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p) {
      delete ((map<string,GamR::TK::FPeak*>*)p);
   }
   static void deleteArray_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p) {
      delete [] ((map<string,GamR::TK::FPeak*>*)p);
   }
   static void destruct_maplEstringcOGamRcLcLTKcLcLFPeakmUgR(void *p) {
      typedef map<string,GamR::TK::FPeak*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,GamR::TK::FPeak*>

namespace ROOT {
   static TClass *maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR_Dictionary();
   static void maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR_TClassManip(TClass*);
   static void *new_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p = nullptr);
   static void *newArray_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(Long_t size, void *p);
   static void delete_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p);
   static void deleteArray_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p);
   static void destruct_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,GamR::Spect::PeakFit::PeakParams>*)
   {
      map<string,GamR::Spect::PeakFit::PeakParams> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,GamR::Spect::PeakFit::PeakParams>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,GamR::Spect::PeakFit::PeakParams>", -2, "c++/v1/map", 900,
                  typeid(map<string,GamR::Spect::PeakFit::PeakParams>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,GamR::Spect::PeakFit::PeakParams>) );
      instance.SetNew(&new_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR);
      instance.SetNewArray(&newArray_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR);
      instance.SetDelete(&delete_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR);
      instance.SetDestructor(&destruct_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,GamR::Spect::PeakFit::PeakParams> >()));

      ::ROOT::AddClassAlternate("map<string,GamR::Spect::PeakFit::PeakParams>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, GamR::Spect::PeakFit::PeakParams, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, GamR::Spect::PeakFit::PeakParams> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,GamR::Spect::PeakFit::PeakParams>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,GamR::Spect::PeakFit::PeakParams>*)nullptr)->GetClass();
      maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Spect::PeakFit::PeakParams> : new map<string,GamR::Spect::PeakFit::PeakParams>;
   }
   static void *newArray_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Spect::PeakFit::PeakParams>[nElements] : new map<string,GamR::Spect::PeakFit::PeakParams>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p) {
      delete ((map<string,GamR::Spect::PeakFit::PeakParams>*)p);
   }
   static void deleteArray_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p) {
      delete [] ((map<string,GamR::Spect::PeakFit::PeakParams>*)p);
   }
   static void destruct_maplEstringcOGamRcLcLSpectcLcLPeakFitcLcLPeakParamsgR(void *p) {
      typedef map<string,GamR::Spect::PeakFit::PeakParams> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,GamR::Spect::PeakFit::PeakParams>

namespace ROOT {
   static TClass *maplEintcOstringgR_Dictionary();
   static void maplEintcOstringgR_TClassManip(TClass*);
   static void *new_maplEintcOstringgR(void *p = nullptr);
   static void *newArray_maplEintcOstringgR(Long_t size, void *p);
   static void delete_maplEintcOstringgR(void *p);
   static void deleteArray_maplEintcOstringgR(void *p);
   static void destruct_maplEintcOstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,string>*)
   {
      map<int,string> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,string>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,string>", -2, "c++/v1/map", 900,
                  typeid(map<int,string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOstringgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,string>) );
      instance.SetNew(&new_maplEintcOstringgR);
      instance.SetNewArray(&newArray_maplEintcOstringgR);
      instance.SetDelete(&delete_maplEintcOstringgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOstringgR);
      instance.SetDestructor(&destruct_maplEintcOstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,string> >()));

      ::ROOT::AddClassAlternate("map<int,string>","std::__1::map<int, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,string>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,string>*)nullptr)->GetClass();
      maplEintcOstringgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,string> : new map<int,string>;
   }
   static void *newArray_maplEintcOstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,string>[nElements] : new map<int,string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOstringgR(void *p) {
      delete ((map<int,string>*)p);
   }
   static void deleteArray_maplEintcOstringgR(void *p) {
      delete [] ((map<int,string>*)p);
   }
   static void destruct_maplEintcOstringgR(void *p) {
      typedef map<int,string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,string>

namespace {
  void TriggerDictionaryInitialization_libgamr_spect_Impl() {
    static const char* headers[] = {
"IO.hh",
"Cut.hh",
"Integral.hh",
"Transform.hh",
"Fit.hh",
"FitGuesses.hh",
"Display.hh",
"FFT.hh",
"BackSub.hh",
"Calibrate.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/spect",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/spect",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/spect/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_spect dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace Spect{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/spect/FitGuesses.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FitGuesses.hh")))  __attribute__((annotate("$clingAutoload$Fit.hh")))  Parameter;}}
namespace GamR{namespace Spect{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/spect/FitGuesses.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FitGuesses.hh")))  __attribute__((annotate("$clingAutoload$Fit.hh")))  PeakFitGuesses;}}
namespace GamR{namespace Spect{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/spect/Fit.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Fit.hh")))  PeakFit;}}
namespace GamR{namespace Spect{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/spect/BackSub.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$BackSub.hh")))  BackSub2D;}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_spect dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "IO.hh"
#include "Cut.hh"
#include "Integral.hh"
#include "Transform.hh"
#include "Fit.hh"
#include "FitGuesses.hh"
#include "Display.hh"
#include "FFT.hh"
#include "BackSub.hh"
#include "Calibrate.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::Spect::Add", payloadCode, "@",
"GamR::Spect::Add2", payloadCode, "@",
"GamR::Spect::BackSub2D", payloadCode, "@",
"GamR::Spect::BackgroundEstimate", payloadCode, "@",
"GamR::Spect::BackgroundSubtract2D", payloadCode, "@",
"GamR::Spect::BackgroundSubtractX", payloadCode, "@",
"GamR::Spect::BackgroundSubtractY", payloadCode, "@",
"GamR::Spect::Counts", payloadCode, "@",
"GamR::Spect::CountsBS", payloadCode, "@",
"GamR::Spect::CutFromText", payloadCode, "@",
"GamR::Spect::Draw", payloadCode, "@",
"GamR::Spect::Draw2D", payloadCode, "@",
"GamR::Spect::FFT", payloadCode, "@",
"GamR::Spect::FindPeaks", payloadCode, "@",
"GamR::Spect::FitGaussians", payloadCode, "@",
"GamR::Spect::FitPeaks", payloadCode, "@",
"GamR::Spect::FromText", payloadCode, "@",
"GamR::Spect::GateX", payloadCode, "@",
"GamR::Spect::GateY", payloadCode, "@",
"GamR::Spect::Init", payloadCode, "@",
"GamR::Spect::Integral", payloadCode, "@",
"GamR::Spect::IntegralBS", payloadCode, "@",
"GamR::Spect::LinAll", payloadCode, "@",
"GamR::Spect::List1DSpectra", payloadCode, "@",
"GamR::Spect::List2DSpectra", payloadCode, "@",
"GamR::Spect::LoadGuesses", payloadCode, "@",
"GamR::Spect::LogAll", payloadCode, "@",
"GamR::Spect::Multiply", payloadCode, "@",
"GamR::Spect::Norm", payloadCode, "@",
"GamR::Spect::NormBackSub", payloadCode, "@",
"GamR::Spect::NormSpectra", payloadCode, "@",
"GamR::Spect::NormSpectraBackSub", payloadCode, "@",
"GamR::Spect::OverlaySpectra", payloadCode, "@",
"GamR::Spect::Parameter", payloadCode, "@",
"GamR::Spect::PeakFit", payloadCode, "@",
"GamR::Spect::PeakFitGuesses", payloadCode, "@",
"GamR::Spect::ProjX", payloadCode, "@",
"GamR::Spect::ProjY", payloadCode, "@",
"GamR::Spect::Rebin", payloadCode, "@",
"GamR::Spect::Reverse", payloadCode, "@",
"GamR::Spect::RotateTH2", payloadCode, "@",
"GamR::Spect::Scale", payloadCode, "@",
"GamR::Spect::ScaleLabelsLinear", payloadCode, "@",
"GamR::Spect::ScalePoly", payloadCode, "@",
"GamR::Spect::Shift", payloadCode, "@",
"GamR::Spect::StackSpectra", payloadCode, "@",
"GamR::Spect::ToBin", payloadCode, "@",
"GamR::Spect::ToSPE", payloadCode, "@",
"GamR::Spect::ToText", payloadCode, "@",
"GamR::Spect::TwoPointCalibrate", payloadCode, "@",
"GamR::Spect::UnZoomAllX", payloadCode, "@",
"GamR::Spect::UnZoomAllY", payloadCode, "@",
"GamR::Spect::ZoomAllX", payloadCode, "@",
"GamR::Spect::ZoomAllY", payloadCode, "@",
"GamR::Spect::gFitGuesses", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_spect",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_spect_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_spect_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_spect() {
  TriggerDictionaryInitialization_libgamr_spect_Impl();
}
