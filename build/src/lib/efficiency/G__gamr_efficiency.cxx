// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_efficiency
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
#include "Efficiency.hh"

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
            instance("GamR", 0 /*version*/, "toolkit/Gate.hh", 18,
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
   namespace Efficiency {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLEfficiency_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Efficiency", 0 /*version*/, "Efficiency.hh", 22,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLEfficiency_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLEfficiency_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   static TClass *GamRcLcLEfficiencycLcLDataSet_Dictionary();
   static void GamRcLcLEfficiencycLcLDataSet_TClassManip(TClass*);
   static void *new_GamRcLcLEfficiencycLcLDataSet(void *p = nullptr);
   static void *newArray_GamRcLcLEfficiencycLcLDataSet(Long_t size, void *p);
   static void delete_GamRcLcLEfficiencycLcLDataSet(void *p);
   static void deleteArray_GamRcLcLEfficiencycLcLDataSet(void *p);
   static void destruct_GamRcLcLEfficiencycLcLDataSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Efficiency::DataSet*)
   {
      ::GamR::Efficiency::DataSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Efficiency::DataSet));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Efficiency::DataSet", "Efficiency.hh", 25,
                  typeid(::GamR::Efficiency::DataSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLEfficiencycLcLDataSet_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Efficiency::DataSet) );
      instance.SetNew(&new_GamRcLcLEfficiencycLcLDataSet);
      instance.SetNewArray(&newArray_GamRcLcLEfficiencycLcLDataSet);
      instance.SetDelete(&delete_GamRcLcLEfficiencycLcLDataSet);
      instance.SetDeleteArray(&deleteArray_GamRcLcLEfficiencycLcLDataSet);
      instance.SetDestructor(&destruct_GamRcLcLEfficiencycLcLDataSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Efficiency::DataSet*)
   {
      return GenerateInitInstanceLocal((::GamR::Efficiency::DataSet*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Efficiency::DataSet*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLEfficiencycLcLDataSet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Efficiency::DataSet*)nullptr)->GetClass();
      GamRcLcLEfficiencycLcLDataSet_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLEfficiencycLcLDataSet_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLEfficiencycLcLFitParams_Dictionary();
   static void GamRcLcLEfficiencycLcLFitParams_TClassManip(TClass*);
   static void delete_GamRcLcLEfficiencycLcLFitParams(void *p);
   static void deleteArray_GamRcLcLEfficiencycLcLFitParams(void *p);
   static void destruct_GamRcLcLEfficiencycLcLFitParams(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Efficiency::FitParams*)
   {
      ::GamR::Efficiency::FitParams *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Efficiency::FitParams));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Efficiency::FitParams", "Efficiency.hh", 64,
                  typeid(::GamR::Efficiency::FitParams), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLEfficiencycLcLFitParams_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Efficiency::FitParams) );
      instance.SetDelete(&delete_GamRcLcLEfficiencycLcLFitParams);
      instance.SetDeleteArray(&deleteArray_GamRcLcLEfficiencycLcLFitParams);
      instance.SetDestructor(&destruct_GamRcLcLEfficiencycLcLFitParams);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Efficiency::FitParams*)
   {
      return GenerateInitInstanceLocal((::GamR::Efficiency::FitParams*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Efficiency::FitParams*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLEfficiencycLcLFitParams_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Efficiency::FitParams*)nullptr)->GetClass();
      GamRcLcLEfficiencycLcLFitParams_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLEfficiencycLcLFitParams_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLEfficiencycLcLEffFit_Dictionary();
   static void GamRcLcLEfficiencycLcLEffFit_TClassManip(TClass*);
   static void *new_GamRcLcLEfficiencycLcLEffFit(void *p = nullptr);
   static void *newArray_GamRcLcLEfficiencycLcLEffFit(Long_t size, void *p);
   static void delete_GamRcLcLEfficiencycLcLEffFit(void *p);
   static void deleteArray_GamRcLcLEfficiencycLcLEffFit(void *p);
   static void destruct_GamRcLcLEfficiencycLcLEffFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Efficiency::EffFit*)
   {
      ::GamR::Efficiency::EffFit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Efficiency::EffFit));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Efficiency::EffFit", "Efficiency.hh", 75,
                  typeid(::GamR::Efficiency::EffFit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLEfficiencycLcLEffFit_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Efficiency::EffFit) );
      instance.SetNew(&new_GamRcLcLEfficiencycLcLEffFit);
      instance.SetNewArray(&newArray_GamRcLcLEfficiencycLcLEffFit);
      instance.SetDelete(&delete_GamRcLcLEfficiencycLcLEffFit);
      instance.SetDeleteArray(&deleteArray_GamRcLcLEfficiencycLcLEffFit);
      instance.SetDestructor(&destruct_GamRcLcLEfficiencycLcLEffFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Efficiency::EffFit*)
   {
      return GenerateInitInstanceLocal((::GamR::Efficiency::EffFit*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Efficiency::EffFit*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLEfficiencycLcLEffFit_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Efficiency::EffFit*)nullptr)->GetClass();
      GamRcLcLEfficiencycLcLEffFit_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLEfficiencycLcLEffFit_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLEfficiencycLcLMultiDataSet_Dictionary();
   static void GamRcLcLEfficiencycLcLMultiDataSet_TClassManip(TClass*);
   static void *new_GamRcLcLEfficiencycLcLMultiDataSet(void *p = nullptr);
   static void *newArray_GamRcLcLEfficiencycLcLMultiDataSet(Long_t size, void *p);
   static void delete_GamRcLcLEfficiencycLcLMultiDataSet(void *p);
   static void deleteArray_GamRcLcLEfficiencycLcLMultiDataSet(void *p);
   static void destruct_GamRcLcLEfficiencycLcLMultiDataSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Efficiency::MultiDataSet*)
   {
      ::GamR::Efficiency::MultiDataSet *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Efficiency::MultiDataSet));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Efficiency::MultiDataSet", "Efficiency.hh", 93,
                  typeid(::GamR::Efficiency::MultiDataSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLEfficiencycLcLMultiDataSet_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Efficiency::MultiDataSet) );
      instance.SetNew(&new_GamRcLcLEfficiencycLcLMultiDataSet);
      instance.SetNewArray(&newArray_GamRcLcLEfficiencycLcLMultiDataSet);
      instance.SetDelete(&delete_GamRcLcLEfficiencycLcLMultiDataSet);
      instance.SetDeleteArray(&deleteArray_GamRcLcLEfficiencycLcLMultiDataSet);
      instance.SetDestructor(&destruct_GamRcLcLEfficiencycLcLMultiDataSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Efficiency::MultiDataSet*)
   {
      return GenerateInitInstanceLocal((::GamR::Efficiency::MultiDataSet*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Efficiency::MultiDataSet*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLEfficiencycLcLMultiDataSet_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Efficiency::MultiDataSet*)nullptr)->GetClass();
      GamRcLcLEfficiencycLcLMultiDataSet_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLEfficiencycLcLMultiDataSet_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLEfficiencycLcLMultiEffFit_Dictionary();
   static void GamRcLcLEfficiencycLcLMultiEffFit_TClassManip(TClass*);
   static void *new_GamRcLcLEfficiencycLcLMultiEffFit(void *p = nullptr);
   static void *newArray_GamRcLcLEfficiencycLcLMultiEffFit(Long_t size, void *p);
   static void delete_GamRcLcLEfficiencycLcLMultiEffFit(void *p);
   static void deleteArray_GamRcLcLEfficiencycLcLMultiEffFit(void *p);
   static void destruct_GamRcLcLEfficiencycLcLMultiEffFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Efficiency::MultiEffFit*)
   {
      ::GamR::Efficiency::MultiEffFit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Efficiency::MultiEffFit));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Efficiency::MultiEffFit", "Efficiency.hh", 104,
                  typeid(::GamR::Efficiency::MultiEffFit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLEfficiencycLcLMultiEffFit_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Efficiency::MultiEffFit) );
      instance.SetNew(&new_GamRcLcLEfficiencycLcLMultiEffFit);
      instance.SetNewArray(&newArray_GamRcLcLEfficiencycLcLMultiEffFit);
      instance.SetDelete(&delete_GamRcLcLEfficiencycLcLMultiEffFit);
      instance.SetDeleteArray(&deleteArray_GamRcLcLEfficiencycLcLMultiEffFit);
      instance.SetDestructor(&destruct_GamRcLcLEfficiencycLcLMultiEffFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Efficiency::MultiEffFit*)
   {
      return GenerateInitInstanceLocal((::GamR::Efficiency::MultiEffFit*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Efficiency::MultiEffFit*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLEfficiencycLcLMultiEffFit_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Efficiency::MultiEffFit*)nullptr)->GetClass();
      GamRcLcLEfficiencycLcLMultiEffFit_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLEfficiencycLcLMultiEffFit_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLEfficiencycLcLDataSet(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::DataSet : new ::GamR::Efficiency::DataSet;
   }
   static void *newArray_GamRcLcLEfficiencycLcLDataSet(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::DataSet[nElements] : new ::GamR::Efficiency::DataSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLEfficiencycLcLDataSet(void *p) {
      delete ((::GamR::Efficiency::DataSet*)p);
   }
   static void deleteArray_GamRcLcLEfficiencycLcLDataSet(void *p) {
      delete [] ((::GamR::Efficiency::DataSet*)p);
   }
   static void destruct_GamRcLcLEfficiencycLcLDataSet(void *p) {
      typedef ::GamR::Efficiency::DataSet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Efficiency::DataSet

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLEfficiencycLcLFitParams(void *p) {
      delete ((::GamR::Efficiency::FitParams*)p);
   }
   static void deleteArray_GamRcLcLEfficiencycLcLFitParams(void *p) {
      delete [] ((::GamR::Efficiency::FitParams*)p);
   }
   static void destruct_GamRcLcLEfficiencycLcLFitParams(void *p) {
      typedef ::GamR::Efficiency::FitParams current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Efficiency::FitParams

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLEfficiencycLcLEffFit(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::EffFit : new ::GamR::Efficiency::EffFit;
   }
   static void *newArray_GamRcLcLEfficiencycLcLEffFit(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::EffFit[nElements] : new ::GamR::Efficiency::EffFit[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLEfficiencycLcLEffFit(void *p) {
      delete ((::GamR::Efficiency::EffFit*)p);
   }
   static void deleteArray_GamRcLcLEfficiencycLcLEffFit(void *p) {
      delete [] ((::GamR::Efficiency::EffFit*)p);
   }
   static void destruct_GamRcLcLEfficiencycLcLEffFit(void *p) {
      typedef ::GamR::Efficiency::EffFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Efficiency::EffFit

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLEfficiencycLcLMultiDataSet(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::MultiDataSet : new ::GamR::Efficiency::MultiDataSet;
   }
   static void *newArray_GamRcLcLEfficiencycLcLMultiDataSet(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::MultiDataSet[nElements] : new ::GamR::Efficiency::MultiDataSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLEfficiencycLcLMultiDataSet(void *p) {
      delete ((::GamR::Efficiency::MultiDataSet*)p);
   }
   static void deleteArray_GamRcLcLEfficiencycLcLMultiDataSet(void *p) {
      delete [] ((::GamR::Efficiency::MultiDataSet*)p);
   }
   static void destruct_GamRcLcLEfficiencycLcLMultiDataSet(void *p) {
      typedef ::GamR::Efficiency::MultiDataSet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Efficiency::MultiDataSet

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLEfficiencycLcLMultiEffFit(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::MultiEffFit : new ::GamR::Efficiency::MultiEffFit;
   }
   static void *newArray_GamRcLcLEfficiencycLcLMultiEffFit(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Efficiency::MultiEffFit[nElements] : new ::GamR::Efficiency::MultiEffFit[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLEfficiencycLcLMultiEffFit(void *p) {
      delete ((::GamR::Efficiency::MultiEffFit*)p);
   }
   static void deleteArray_GamRcLcLEfficiencycLcLMultiEffFit(void *p) {
      delete [] ((::GamR::Efficiency::MultiEffFit*)p);
   }
   static void destruct_GamRcLcLEfficiencycLcLMultiEffFit(void *p) {
      typedef ::GamR::Efficiency::MultiEffFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Efficiency::MultiEffFit

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = nullptr);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "c++/v1/vector", 471,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));

      ::ROOT::AddClassAlternate("vector<string>","std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<string>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)nullptr)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

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
   static TClass *vectorlETFormulagR_Dictionary();
   static void vectorlETFormulagR_TClassManip(TClass*);
   static void *new_vectorlETFormulagR(void *p = nullptr);
   static void *newArray_vectorlETFormulagR(Long_t size, void *p);
   static void delete_vectorlETFormulagR(void *p);
   static void deleteArray_vectorlETFormulagR(void *p);
   static void destruct_vectorlETFormulagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TFormula>*)
   {
      vector<TFormula> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TFormula>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TFormula>", -2, "c++/v1/vector", 471,
                  typeid(vector<TFormula>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETFormulagR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TFormula>) );
      instance.SetNew(&new_vectorlETFormulagR);
      instance.SetNewArray(&newArray_vectorlETFormulagR);
      instance.SetDelete(&delete_vectorlETFormulagR);
      instance.SetDeleteArray(&deleteArray_vectorlETFormulagR);
      instance.SetDestructor(&destruct_vectorlETFormulagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TFormula> >()));

      ::ROOT::AddClassAlternate("vector<TFormula>","std::__1::vector<TFormula, std::__1::allocator<TFormula> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TFormula>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETFormulagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TFormula>*)nullptr)->GetClass();
      vectorlETFormulagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETFormulagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETFormulagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TFormula> : new vector<TFormula>;
   }
   static void *newArray_vectorlETFormulagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TFormula>[nElements] : new vector<TFormula>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETFormulagR(void *p) {
      delete ((vector<TFormula>*)p);
   }
   static void deleteArray_vectorlETFormulagR(void *p) {
      delete [] ((vector<TFormula>*)p);
   }
   static void destruct_vectorlETFormulagR(void *p) {
      typedef vector<TFormula> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TFormula>

namespace ROOT {
   static TClass *vectorlEGamRcLcLEfficiencycLcLDataSetgR_Dictionary();
   static void vectorlEGamRcLcLEfficiencycLcLDataSetgR_TClassManip(TClass*);
   static void *new_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p = nullptr);
   static void *newArray_vectorlEGamRcLcLEfficiencycLcLDataSetgR(Long_t size, void *p);
   static void delete_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p);
   static void deleteArray_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p);
   static void destruct_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GamR::Efficiency::DataSet>*)
   {
      vector<GamR::Efficiency::DataSet> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GamR::Efficiency::DataSet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GamR::Efficiency::DataSet>", -2, "c++/v1/vector", 471,
                  typeid(vector<GamR::Efficiency::DataSet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGamRcLcLEfficiencycLcLDataSetgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GamR::Efficiency::DataSet>) );
      instance.SetNew(&new_vectorlEGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetNewArray(&newArray_vectorlEGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetDelete(&delete_vectorlEGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetDestructor(&destruct_vectorlEGamRcLcLEfficiencycLcLDataSetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GamR::Efficiency::DataSet> >()));

      ::ROOT::AddClassAlternate("vector<GamR::Efficiency::DataSet>","std::__1::vector<GamR::Efficiency::DataSet, std::__1::allocator<GamR::Efficiency::DataSet> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GamR::Efficiency::DataSet>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGamRcLcLEfficiencycLcLDataSetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GamR::Efficiency::DataSet>*)nullptr)->GetClass();
      vectorlEGamRcLcLEfficiencycLcLDataSetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGamRcLcLEfficiencycLcLDataSetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::Efficiency::DataSet> : new vector<GamR::Efficiency::DataSet>;
   }
   static void *newArray_vectorlEGamRcLcLEfficiencycLcLDataSetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::Efficiency::DataSet>[nElements] : new vector<GamR::Efficiency::DataSet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      delete ((vector<GamR::Efficiency::DataSet>*)p);
   }
   static void deleteArray_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      delete [] ((vector<GamR::Efficiency::DataSet>*)p);
   }
   static void destruct_vectorlEGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      typedef vector<GamR::Efficiency::DataSet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GamR::Efficiency::DataSet>

namespace ROOT {
   static TClass *maplEintcOdoublegR_Dictionary();
   static void maplEintcOdoublegR_TClassManip(TClass*);
   static void *new_maplEintcOdoublegR(void *p = nullptr);
   static void *newArray_maplEintcOdoublegR(Long_t size, void *p);
   static void delete_maplEintcOdoublegR(void *p);
   static void deleteArray_maplEintcOdoublegR(void *p);
   static void destruct_maplEintcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,double>*)
   {
      map<int,double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,double>", -2, "c++/v1/map", 900,
                  typeid(map<int,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,double>) );
      instance.SetNew(&new_maplEintcOdoublegR);
      instance.SetNewArray(&newArray_maplEintcOdoublegR);
      instance.SetDelete(&delete_maplEintcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEintcOdoublegR);
      instance.SetDestructor(&destruct_maplEintcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,double> >()));

      ::ROOT::AddClassAlternate("map<int,double>","std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,double>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,double>*)nullptr)->GetClass();
      maplEintcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,double> : new map<int,double>;
   }
   static void *newArray_maplEintcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,double>[nElements] : new map<int,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOdoublegR(void *p) {
      delete ((map<int,double>*)p);
   }
   static void deleteArray_maplEintcOdoublegR(void *p) {
      delete [] ((map<int,double>*)p);
   }
   static void destruct_maplEintcOdoublegR(void *p) {
      typedef map<int,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,double>

namespace ROOT {
   static TClass *maplEintcOGamRcLcLEfficiencycLcLEffFitgR_Dictionary();
   static void maplEintcOGamRcLcLEfficiencycLcLEffFitgR_TClassManip(TClass*);
   static void *new_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p = nullptr);
   static void *newArray_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(Long_t size, void *p);
   static void delete_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p);
   static void deleteArray_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p);
   static void destruct_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,GamR::Efficiency::EffFit>*)
   {
      map<int,GamR::Efficiency::EffFit> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,GamR::Efficiency::EffFit>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,GamR::Efficiency::EffFit>", -2, "c++/v1/map", 900,
                  typeid(map<int,GamR::Efficiency::EffFit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOGamRcLcLEfficiencycLcLEffFitgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,GamR::Efficiency::EffFit>) );
      instance.SetNew(&new_maplEintcOGamRcLcLEfficiencycLcLEffFitgR);
      instance.SetNewArray(&newArray_maplEintcOGamRcLcLEfficiencycLcLEffFitgR);
      instance.SetDelete(&delete_maplEintcOGamRcLcLEfficiencycLcLEffFitgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOGamRcLcLEfficiencycLcLEffFitgR);
      instance.SetDestructor(&destruct_maplEintcOGamRcLcLEfficiencycLcLEffFitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,GamR::Efficiency::EffFit> >()));

      ::ROOT::AddClassAlternate("map<int,GamR::Efficiency::EffFit>","std::__1::map<int, GamR::Efficiency::EffFit, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, GamR::Efficiency::EffFit> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,GamR::Efficiency::EffFit>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOGamRcLcLEfficiencycLcLEffFitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,GamR::Efficiency::EffFit>*)nullptr)->GetClass();
      maplEintcOGamRcLcLEfficiencycLcLEffFitgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOGamRcLcLEfficiencycLcLEffFitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,GamR::Efficiency::EffFit> : new map<int,GamR::Efficiency::EffFit>;
   }
   static void *newArray_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,GamR::Efficiency::EffFit>[nElements] : new map<int,GamR::Efficiency::EffFit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p) {
      delete ((map<int,GamR::Efficiency::EffFit>*)p);
   }
   static void deleteArray_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p) {
      delete [] ((map<int,GamR::Efficiency::EffFit>*)p);
   }
   static void destruct_maplEintcOGamRcLcLEfficiencycLcLEffFitgR(void *p) {
      typedef map<int,GamR::Efficiency::EffFit> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,GamR::Efficiency::EffFit>

namespace ROOT {
   static TClass *maplEintcOGamRcLcLEfficiencycLcLDataSetgR_Dictionary();
   static void maplEintcOGamRcLcLEfficiencycLcLDataSetgR_TClassManip(TClass*);
   static void *new_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p = nullptr);
   static void *newArray_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(Long_t size, void *p);
   static void delete_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p);
   static void deleteArray_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p);
   static void destruct_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,GamR::Efficiency::DataSet>*)
   {
      map<int,GamR::Efficiency::DataSet> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,GamR::Efficiency::DataSet>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,GamR::Efficiency::DataSet>", -2, "c++/v1/map", 900,
                  typeid(map<int,GamR::Efficiency::DataSet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOGamRcLcLEfficiencycLcLDataSetgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,GamR::Efficiency::DataSet>) );
      instance.SetNew(&new_maplEintcOGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetNewArray(&newArray_maplEintcOGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetDelete(&delete_maplEintcOGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOGamRcLcLEfficiencycLcLDataSetgR);
      instance.SetDestructor(&destruct_maplEintcOGamRcLcLEfficiencycLcLDataSetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,GamR::Efficiency::DataSet> >()));

      ::ROOT::AddClassAlternate("map<int,GamR::Efficiency::DataSet>","std::__1::map<int, GamR::Efficiency::DataSet, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, GamR::Efficiency::DataSet> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,GamR::Efficiency::DataSet>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOGamRcLcLEfficiencycLcLDataSetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,GamR::Efficiency::DataSet>*)nullptr)->GetClass();
      maplEintcOGamRcLcLEfficiencycLcLDataSetgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOGamRcLcLEfficiencycLcLDataSetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,GamR::Efficiency::DataSet> : new map<int,GamR::Efficiency::DataSet>;
   }
   static void *newArray_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,GamR::Efficiency::DataSet>[nElements] : new map<int,GamR::Efficiency::DataSet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      delete ((map<int,GamR::Efficiency::DataSet>*)p);
   }
   static void deleteArray_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      delete [] ((map<int,GamR::Efficiency::DataSet>*)p);
   }
   static void destruct_maplEintcOGamRcLcLEfficiencycLcLDataSetgR(void *p) {
      typedef map<int,GamR::Efficiency::DataSet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,GamR::Efficiency::DataSet>

namespace {
  void TriggerDictionaryInitialization_libgamr_efficiency_Impl() {
    static const char* headers[] = {
"Efficiency.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/efficiency",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/efficiency",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/efficiency/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_efficiency dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace Efficiency{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Efficiency.hh")))  DataSet;}}
namespace GamR{namespace Efficiency{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Efficiency.hh")))  FitParams;}}
namespace GamR{namespace Efficiency{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Efficiency.hh")))  EffFit;}}
namespace GamR{namespace Efficiency{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Efficiency.hh")))  MultiDataSet;}}
namespace GamR{namespace Efficiency{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/efficiency/Efficiency.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Efficiency.hh")))  MultiEffFit;}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_efficiency dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Efficiency.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::Efficiency::DataSet", payloadCode, "@",
"GamR::Efficiency::EffCFunc", payloadCode, "@",
"GamR::Efficiency::EffFit", payloadCode, "@",
"GamR::Efficiency::FitParams", payloadCode, "@",
"GamR::Efficiency::MultiDataSet", payloadCode, "@",
"GamR::Efficiency::MultiEffFit", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_efficiency",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_efficiency_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_efficiency_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_efficiency() {
  TriggerDictionaryInitialization_libgamr_efficiency_Impl();
}
