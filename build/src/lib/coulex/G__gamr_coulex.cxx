// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_coulex
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
#include "Coulex.hh"
#include "CoulexCalculation.hh"
#include "Eloss.hh"
#include "WDBSubs.hh"

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
            instance("GamR", 0 /*version*/, "toolkit/Misc.hh", 4,
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
   namespace Coulex {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLCoulex_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Coulex", 0 /*version*/, "Eloss.hh", 30,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLCoulex_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLCoulex_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace GamR {
   namespace Coulex {
      namespace WDB {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLCoulexcLcLWDB_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Coulex::WDB", 0 /*version*/, "WDBSubs.hh", 6,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLCoulexcLcLWDB_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLCoulexcLcLWDB_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}
}

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLWDB_nuclvl_Dictionary();
   static void GamRcLcLCoulexcLcLWDB_nuclvl_TClassManip(TClass*);
   static void *new_GamRcLcLCoulexcLcLWDB_nuclvl(void *p = nullptr);
   static void *newArray_GamRcLcLCoulexcLcLWDB_nuclvl(Long_t size, void *p);
   static void delete_GamRcLcLCoulexcLcLWDB_nuclvl(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLWDB_nuclvl(void *p);
   static void destruct_GamRcLcLCoulexcLcLWDB_nuclvl(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::WDB_nuclvl*)
   {
      ::GamR::Coulex::WDB_nuclvl *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::WDB_nuclvl));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::WDB_nuclvl", "Coulex.hh", 23,
                  typeid(::GamR::Coulex::WDB_nuclvl), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLWDB_nuclvl_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::WDB_nuclvl) );
      instance.SetNew(&new_GamRcLcLCoulexcLcLWDB_nuclvl);
      instance.SetNewArray(&newArray_GamRcLcLCoulexcLcLWDB_nuclvl);
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLWDB_nuclvl);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLWDB_nuclvl);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLWDB_nuclvl);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::WDB_nuclvl*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::WDB_nuclvl*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::WDB_nuclvl*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLWDB_nuclvl_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::WDB_nuclvl*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLWDB_nuclvl_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLWDB_nuclvl_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/Coulex.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLWDB_nuctrans_Dictionary();
   static void GamRcLcLCoulexcLcLWDB_nuctrans_TClassManip(TClass*);
   static void *new_GamRcLcLCoulexcLcLWDB_nuctrans(void *p = nullptr);
   static void *newArray_GamRcLcLCoulexcLcLWDB_nuctrans(Long_t size, void *p);
   static void delete_GamRcLcLCoulexcLcLWDB_nuctrans(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLWDB_nuctrans(void *p);
   static void destruct_GamRcLcLCoulexcLcLWDB_nuctrans(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::WDB_nuctrans*)
   {
      ::GamR::Coulex::WDB_nuctrans *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::WDB_nuctrans));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::WDB_nuctrans", "Coulex.hh", 31,
                  typeid(::GamR::Coulex::WDB_nuctrans), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLWDB_nuctrans_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::WDB_nuctrans) );
      instance.SetNew(&new_GamRcLcLCoulexcLcLWDB_nuctrans);
      instance.SetNewArray(&newArray_GamRcLcLCoulexcLcLWDB_nuctrans);
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLWDB_nuctrans);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLWDB_nuctrans);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLWDB_nuctrans);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::WDB_nuctrans*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::WDB_nuctrans*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::WDB_nuctrans*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLWDB_nuctrans_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::WDB_nuctrans*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLWDB_nuctrans_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLWDB_nuctrans_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/Coulex.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLNucleus_Dictionary();
   static void GamRcLcLCoulexcLcLNucleus_TClassManip(TClass*);
   static void *new_GamRcLcLCoulexcLcLNucleus(void *p = nullptr);
   static void *newArray_GamRcLcLCoulexcLcLNucleus(Long_t size, void *p);
   static void delete_GamRcLcLCoulexcLcLNucleus(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLNucleus(void *p);
   static void destruct_GamRcLcLCoulexcLcLNucleus(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::Nucleus*)
   {
      ::GamR::Coulex::Nucleus *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::Nucleus));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::Nucleus", "CoulexCalculation.hh", 33,
                  typeid(::GamR::Coulex::Nucleus), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLNucleus_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::Nucleus) );
      instance.SetNew(&new_GamRcLcLCoulexcLcLNucleus);
      instance.SetNewArray(&newArray_GamRcLcLCoulexcLcLNucleus);
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLNucleus);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLNucleus);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLNucleus);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::Nucleus*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::Nucleus*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::Nucleus*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLNucleus_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::Nucleus*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLNucleus_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLNucleus_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLTarget_Dictionary();
   static void GamRcLcLCoulexcLcLTarget_TClassManip(TClass*);
   static void *new_GamRcLcLCoulexcLcLTarget(void *p = nullptr);
   static void *newArray_GamRcLcLCoulexcLcLTarget(Long_t size, void *p);
   static void delete_GamRcLcLCoulexcLcLTarget(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLTarget(void *p);
   static void destruct_GamRcLcLCoulexcLcLTarget(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::Target*)
   {
      ::GamR::Coulex::Target *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::Target));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::Target", "CoulexCalculation.hh", 41,
                  typeid(::GamR::Coulex::Target), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLTarget_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::Target) );
      instance.SetNew(&new_GamRcLcLCoulexcLcLTarget);
      instance.SetNewArray(&newArray_GamRcLcLCoulexcLcLTarget);
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLTarget);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLTarget);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLTarget);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::Target*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::Target*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::Target*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLTarget_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::Target*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLTarget_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLTarget_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLLevel_Dictionary();
   static void GamRcLcLCoulexcLcLLevel_TClassManip(TClass*);
   static void delete_GamRcLcLCoulexcLcLLevel(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLLevel(void *p);
   static void destruct_GamRcLcLCoulexcLcLLevel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::Level*)
   {
      ::GamR::Coulex::Level *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::Level));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::Level", "CoulexCalculation.hh", 52,
                  typeid(::GamR::Coulex::Level), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLLevel_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::Level) );
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLLevel);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLLevel);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLLevel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::Level*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::Level*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::Level*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLLevel_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::Level*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLLevel_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLLevel_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLTransition_Dictionary();
   static void GamRcLcLCoulexcLcLTransition_TClassManip(TClass*);
   static void delete_GamRcLcLCoulexcLcLTransition(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLTransition(void *p);
   static void destruct_GamRcLcLCoulexcLcLTransition(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::Transition*)
   {
      ::GamR::Coulex::Transition *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::Transition));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::Transition", "CoulexCalculation.hh", 82,
                  typeid(::GamR::Coulex::Transition), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLTransition_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::Transition) );
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLTransition);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLTransition);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLTransition);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::Transition*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::Transition*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::Transition*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLTransition_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::Transition*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLTransition_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLTransition_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLLevelScheme_Dictionary();
   static void GamRcLcLCoulexcLcLLevelScheme_TClassManip(TClass*);
   static void *new_GamRcLcLCoulexcLcLLevelScheme(void *p = nullptr);
   static void *newArray_GamRcLcLCoulexcLcLLevelScheme(Long_t size, void *p);
   static void delete_GamRcLcLCoulexcLcLLevelScheme(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLLevelScheme(void *p);
   static void destruct_GamRcLcLCoulexcLcLLevelScheme(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::LevelScheme*)
   {
      ::GamR::Coulex::LevelScheme *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::LevelScheme));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::LevelScheme", "CoulexCalculation.hh", 120,
                  typeid(::GamR::Coulex::LevelScheme), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLLevelScheme_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::LevelScheme) );
      instance.SetNew(&new_GamRcLcLCoulexcLcLLevelScheme);
      instance.SetNewArray(&newArray_GamRcLcLCoulexcLcLLevelScheme);
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLLevelScheme);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLLevelScheme);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLLevelScheme);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::LevelScheme*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::LevelScheme*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::LevelScheme*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLLevelScheme_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::LevelScheme*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLLevelScheme_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLLevelScheme_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLParticleDetector_Dictionary();
   static void GamRcLcLCoulexcLcLParticleDetector_TClassManip(TClass*);
   static void *new_GamRcLcLCoulexcLcLParticleDetector(void *p = nullptr);
   static void *newArray_GamRcLcLCoulexcLcLParticleDetector(Long_t size, void *p);
   static void delete_GamRcLcLCoulexcLcLParticleDetector(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLParticleDetector(void *p);
   static void destruct_GamRcLcLCoulexcLcLParticleDetector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::ParticleDetector*)
   {
      ::GamR::Coulex::ParticleDetector *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::ParticleDetector));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::ParticleDetector", "CoulexCalculation.hh", 143,
                  typeid(::GamR::Coulex::ParticleDetector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLParticleDetector_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::ParticleDetector) );
      instance.SetNew(&new_GamRcLcLCoulexcLcLParticleDetector);
      instance.SetNewArray(&newArray_GamRcLcLCoulexcLcLParticleDetector);
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLParticleDetector);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLParticleDetector);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLParticleDetector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::ParticleDetector*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::ParticleDetector*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::ParticleDetector*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLParticleDetector_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::ParticleDetector*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLParticleDetector_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLParticleDetector_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GamRcLcLCoulexcLcLCoulexCalculation_Dictionary();
   static void GamRcLcLCoulexcLcLCoulexCalculation_TClassManip(TClass*);
   static void *new_GamRcLcLCoulexcLcLCoulexCalculation(void *p = nullptr);
   static void *newArray_GamRcLcLCoulexcLcLCoulexCalculation(Long_t size, void *p);
   static void delete_GamRcLcLCoulexcLcLCoulexCalculation(void *p);
   static void deleteArray_GamRcLcLCoulexcLcLCoulexCalculation(void *p);
   static void destruct_GamRcLcLCoulexcLcLCoulexCalculation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Coulex::CoulexCalculation*)
   {
      ::GamR::Coulex::CoulexCalculation *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Coulex::CoulexCalculation));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Coulex::CoulexCalculation", "CoulexCalculation.hh", 154,
                  typeid(::GamR::Coulex::CoulexCalculation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLCoulexcLcLCoulexCalculation_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Coulex::CoulexCalculation) );
      instance.SetNew(&new_GamRcLcLCoulexcLcLCoulexCalculation);
      instance.SetNewArray(&newArray_GamRcLcLCoulexcLcLCoulexCalculation);
      instance.SetDelete(&delete_GamRcLcLCoulexcLcLCoulexCalculation);
      instance.SetDeleteArray(&deleteArray_GamRcLcLCoulexcLcLCoulexCalculation);
      instance.SetDestructor(&destruct_GamRcLcLCoulexcLcLCoulexCalculation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Coulex::CoulexCalculation*)
   {
      return GenerateInitInstanceLocal((::GamR::Coulex::CoulexCalculation*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Coulex::CoulexCalculation*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLCoulexcLcLCoulexCalculation_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Coulex::CoulexCalculation*)nullptr)->GetClass();
      GamRcLcLCoulexcLcLCoulexCalculation_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLCoulexcLcLCoulexCalculation_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLCoulexcLcLWDB_nuclvl(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::WDB_nuclvl : new ::GamR::Coulex::WDB_nuclvl;
   }
   static void *newArray_GamRcLcLCoulexcLcLWDB_nuclvl(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::WDB_nuclvl[nElements] : new ::GamR::Coulex::WDB_nuclvl[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLWDB_nuclvl(void *p) {
      delete ((::GamR::Coulex::WDB_nuclvl*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLWDB_nuclvl(void *p) {
      delete [] ((::GamR::Coulex::WDB_nuclvl*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLWDB_nuclvl(void *p) {
      typedef ::GamR::Coulex::WDB_nuclvl current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::WDB_nuclvl

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLCoulexcLcLWDB_nuctrans(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::WDB_nuctrans : new ::GamR::Coulex::WDB_nuctrans;
   }
   static void *newArray_GamRcLcLCoulexcLcLWDB_nuctrans(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::WDB_nuctrans[nElements] : new ::GamR::Coulex::WDB_nuctrans[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLWDB_nuctrans(void *p) {
      delete ((::GamR::Coulex::WDB_nuctrans*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLWDB_nuctrans(void *p) {
      delete [] ((::GamR::Coulex::WDB_nuctrans*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLWDB_nuctrans(void *p) {
      typedef ::GamR::Coulex::WDB_nuctrans current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::WDB_nuctrans

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLCoulexcLcLNucleus(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::Nucleus : new ::GamR::Coulex::Nucleus;
   }
   static void *newArray_GamRcLcLCoulexcLcLNucleus(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::Nucleus[nElements] : new ::GamR::Coulex::Nucleus[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLNucleus(void *p) {
      delete ((::GamR::Coulex::Nucleus*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLNucleus(void *p) {
      delete [] ((::GamR::Coulex::Nucleus*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLNucleus(void *p) {
      typedef ::GamR::Coulex::Nucleus current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::Nucleus

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLCoulexcLcLTarget(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::Target : new ::GamR::Coulex::Target;
   }
   static void *newArray_GamRcLcLCoulexcLcLTarget(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::Target[nElements] : new ::GamR::Coulex::Target[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLTarget(void *p) {
      delete ((::GamR::Coulex::Target*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLTarget(void *p) {
      delete [] ((::GamR::Coulex::Target*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLTarget(void *p) {
      typedef ::GamR::Coulex::Target current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::Target

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLLevel(void *p) {
      delete ((::GamR::Coulex::Level*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLLevel(void *p) {
      delete [] ((::GamR::Coulex::Level*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLLevel(void *p) {
      typedef ::GamR::Coulex::Level current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::Level

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLTransition(void *p) {
      delete ((::GamR::Coulex::Transition*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLTransition(void *p) {
      delete [] ((::GamR::Coulex::Transition*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLTransition(void *p) {
      typedef ::GamR::Coulex::Transition current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::Transition

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLCoulexcLcLLevelScheme(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::LevelScheme : new ::GamR::Coulex::LevelScheme;
   }
   static void *newArray_GamRcLcLCoulexcLcLLevelScheme(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::LevelScheme[nElements] : new ::GamR::Coulex::LevelScheme[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLLevelScheme(void *p) {
      delete ((::GamR::Coulex::LevelScheme*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLLevelScheme(void *p) {
      delete [] ((::GamR::Coulex::LevelScheme*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLLevelScheme(void *p) {
      typedef ::GamR::Coulex::LevelScheme current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::LevelScheme

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLCoulexcLcLParticleDetector(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::ParticleDetector : new ::GamR::Coulex::ParticleDetector;
   }
   static void *newArray_GamRcLcLCoulexcLcLParticleDetector(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::ParticleDetector[nElements] : new ::GamR::Coulex::ParticleDetector[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLParticleDetector(void *p) {
      delete ((::GamR::Coulex::ParticleDetector*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLParticleDetector(void *p) {
      delete [] ((::GamR::Coulex::ParticleDetector*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLParticleDetector(void *p) {
      typedef ::GamR::Coulex::ParticleDetector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::ParticleDetector

namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLCoulexcLcLCoulexCalculation(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::CoulexCalculation : new ::GamR::Coulex::CoulexCalculation;
   }
   static void *newArray_GamRcLcLCoulexcLcLCoulexCalculation(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::GamR::Coulex::CoulexCalculation[nElements] : new ::GamR::Coulex::CoulexCalculation[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLCoulexcLcLCoulexCalculation(void *p) {
      delete ((::GamR::Coulex::CoulexCalculation*)p);
   }
   static void deleteArray_GamRcLcLCoulexcLcLCoulexCalculation(void *p) {
      delete [] ((::GamR::Coulex::CoulexCalculation*)p);
   }
   static void destruct_GamRcLcLCoulexcLcLCoulexCalculation(void *p) {
      typedef ::GamR::Coulex::CoulexCalculation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Coulex::CoulexCalculation

namespace ROOT {
   static TClass *vectorlEGamRcLcLCoulexcLcLTransitionmUgR_Dictionary();
   static void vectorlEGamRcLcLCoulexcLcLTransitionmUgR_TClassManip(TClass*);
   static void *new_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p = nullptr);
   static void *newArray_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(Long_t size, void *p);
   static void delete_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p);
   static void deleteArray_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p);
   static void destruct_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GamR::Coulex::Transition*>*)
   {
      vector<GamR::Coulex::Transition*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GamR::Coulex::Transition*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GamR::Coulex::Transition*>", -2, "c++/v1/vector", 471,
                  typeid(vector<GamR::Coulex::Transition*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGamRcLcLCoulexcLcLTransitionmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GamR::Coulex::Transition*>) );
      instance.SetNew(&new_vectorlEGamRcLcLCoulexcLcLTransitionmUgR);
      instance.SetNewArray(&newArray_vectorlEGamRcLcLCoulexcLcLTransitionmUgR);
      instance.SetDelete(&delete_vectorlEGamRcLcLCoulexcLcLTransitionmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEGamRcLcLCoulexcLcLTransitionmUgR);
      instance.SetDestructor(&destruct_vectorlEGamRcLcLCoulexcLcLTransitionmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GamR::Coulex::Transition*> >()));

      ::ROOT::AddClassAlternate("vector<GamR::Coulex::Transition*>","std::__1::vector<GamR::Coulex::Transition*, std::__1::allocator<GamR::Coulex::Transition*> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GamR::Coulex::Transition*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGamRcLcLCoulexcLcLTransitionmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GamR::Coulex::Transition*>*)nullptr)->GetClass();
      vectorlEGamRcLcLCoulexcLcLTransitionmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGamRcLcLCoulexcLcLTransitionmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::Coulex::Transition*> : new vector<GamR::Coulex::Transition*>;
   }
   static void *newArray_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::Coulex::Transition*>[nElements] : new vector<GamR::Coulex::Transition*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p) {
      delete ((vector<GamR::Coulex::Transition*>*)p);
   }
   static void deleteArray_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p) {
      delete [] ((vector<GamR::Coulex::Transition*>*)p);
   }
   static void destruct_vectorlEGamRcLcLCoulexcLcLTransitionmUgR(void *p) {
      typedef vector<GamR::Coulex::Transition*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GamR::Coulex::Transition*>

namespace ROOT {
   static TClass *maplEstringcOGamRcLcLCoulexcLcLLevelmUgR_Dictionary();
   static void maplEstringcOGamRcLcLCoulexcLcLLevelmUgR_TClassManip(TClass*);
   static void *new_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p = nullptr);
   static void *newArray_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(Long_t size, void *p);
   static void delete_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p);
   static void deleteArray_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p);
   static void destruct_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,GamR::Coulex::Level*>*)
   {
      map<string,GamR::Coulex::Level*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,GamR::Coulex::Level*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,GamR::Coulex::Level*>", -2, "c++/v1/map", 900,
                  typeid(map<string,GamR::Coulex::Level*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOGamRcLcLCoulexcLcLLevelmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,GamR::Coulex::Level*>) );
      instance.SetNew(&new_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR);
      instance.SetNewArray(&newArray_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR);
      instance.SetDelete(&delete_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR);
      instance.SetDestructor(&destruct_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,GamR::Coulex::Level*> >()));

      ::ROOT::AddClassAlternate("map<string,GamR::Coulex::Level*>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, GamR::Coulex::Level*, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, GamR::Coulex::Level*> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,GamR::Coulex::Level*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOGamRcLcLCoulexcLcLLevelmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,GamR::Coulex::Level*>*)nullptr)->GetClass();
      maplEstringcOGamRcLcLCoulexcLcLLevelmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOGamRcLcLCoulexcLcLLevelmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Coulex::Level*> : new map<string,GamR::Coulex::Level*>;
   }
   static void *newArray_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Coulex::Level*>[nElements] : new map<string,GamR::Coulex::Level*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p) {
      delete ((map<string,GamR::Coulex::Level*>*)p);
   }
   static void deleteArray_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p) {
      delete [] ((map<string,GamR::Coulex::Level*>*)p);
   }
   static void destruct_maplEstringcOGamRcLcLCoulexcLcLLevelmUgR(void *p) {
      typedef map<string,GamR::Coulex::Level*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,GamR::Coulex::Level*>

namespace {
  void TriggerDictionaryInitialization_libgamr_coulex_Impl() {
    static const char* headers[] = {
"Coulex.hh",
"CoulexCalculation.hh",
"Eloss.hh",
"WDBSubs.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/coulex",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/coulex",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/coulex/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_coulex dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace Coulex{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/Coulex.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Coulex.hh")))  WDB_nuclvl;}}
namespace GamR{namespace Coulex{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/Coulex.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Coulex.hh")))  WDB_nuctrans;}}
namespace GamR{namespace Coulex{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$CoulexCalculation.hh")))  Nucleus;}}
namespace GamR{namespace Coulex{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$CoulexCalculation.hh")))  Target;}}
namespace GamR{namespace Coulex{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$CoulexCalculation.hh")))  Level;}}
namespace GamR{namespace Coulex{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$CoulexCalculation.hh")))  Transition;}}
namespace GamR{namespace Coulex{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$CoulexCalculation.hh")))  LevelScheme;}}
namespace GamR{namespace Coulex{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$CoulexCalculation.hh")))  ParticleDetector;}}
namespace GamR{namespace Coulex{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/coulex/CoulexCalculation.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$CoulexCalculation.hh")))  CoulexCalculation;}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_coulex dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Coulex.hh"
#include "CoulexCalculation.hh"
#include "Eloss.hh"
#include "WDBSubs.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::Coulex::CoulexCalculation", payloadCode, "@",
"GamR::Coulex::DoCoulex", payloadCode, "@",
"GamR::Coulex::DrawSetup", payloadCode, "@",
"GamR::Coulex::ELoss", payloadCode, "@",
"GamR::Coulex::Eldat", payloadCode, "@",
"GamR::Coulex::ExperimentalSetup", payloadCode, "@",
"GamR::Coulex::GP_AC_Tensors", payloadCode, "@",
"GamR::Coulex::Kinematics", payloadCode, "@",
"GamR::Coulex::Level", payloadCode, "@",
"GamR::Coulex::LevelScheme", payloadCode, "@",
"GamR::Coulex::MakeDatafile", payloadCode, "@",
"GamR::Coulex::Nucleus", payloadCode, "@",
"GamR::Coulex::ParticleDetector", payloadCode, "@",
"GamR::Coulex::ReadDatafile", payloadCode, "@",
"GamR::Coulex::SCOEFloaded", payloadCode, "@",
"GamR::Coulex::S_e", payloadCode, "@",
"GamR::Coulex::S_n", payloadCode, "@",
"GamR::Coulex::Target", payloadCode, "@",
"GamR::Coulex::Transition", payloadCode, "@",
"GamR::Coulex::WDB::coulex_", payloadCode, "@",
"GamR::Coulex::WDB::coulparcm_", payloadCode, "@",
"GamR::Coulex::WDB::freader_", payloadCode, "@",
"GamR::Coulex::WDB::getcoulex_", payloadCode, "@",
"GamR::Coulex::WDB::setup_coulex_", payloadCode, "@",
"GamR::Coulex::WDB_nuclvl", payloadCode, "@",
"GamR::Coulex::WDB_nuctrans", payloadCode, "@",
"GamR::Coulex::dEdx", payloadCode, "@",
"GamR::Coulex::loadSCOEF", payloadCode, "@",
"GamR::Coulex::rad2deg", payloadCode, "@",
"GamR::Coulex::setupcoulex", payloadCode, "@",
"GamR::Coulex::xcmlr", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_coulex",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_coulex_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_coulex_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_coulex() {
  TriggerDictionaryInitialization_libgamr_coulex_Impl();
}
