// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_nucleus
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
#include "Photon.hh"
#include "State.hh"
#include "Transition.hh"
#include "LevelScheme.hh"

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
   namespace Nucleus {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLNucleus_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Nucleus", 0 /*version*/, "Transition.hh", 16,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLNucleus_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLNucleus_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace GamR {
   namespace Nucleus {
      namespace LevelScheme {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLNucleuscLcLLevelScheme_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Nucleus::LevelScheme", 0 /*version*/, "LevelScheme.hh", 12,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLNucleuscLcLLevelScheme_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLNucleuscLcLLevelScheme_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}
}

namespace ROOT {
   static void *new_GamRcLcLNucleuscLcLTransition(void *p = nullptr);
   static void *newArray_GamRcLcLNucleuscLcLTransition(Long_t size, void *p);
   static void delete_GamRcLcLNucleuscLcLTransition(void *p);
   static void deleteArray_GamRcLcLNucleuscLcLTransition(void *p);
   static void destruct_GamRcLcLNucleuscLcLTransition(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Nucleus::Transition*)
   {
      ::GamR::Nucleus::Transition *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::Nucleus::Transition >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Nucleus::Transition", ::GamR::Nucleus::Transition::Class_Version(), "Transition.hh", 18,
                  typeid(::GamR::Nucleus::Transition), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::Nucleus::Transition::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Nucleus::Transition) );
      instance.SetNew(&new_GamRcLcLNucleuscLcLTransition);
      instance.SetNewArray(&newArray_GamRcLcLNucleuscLcLTransition);
      instance.SetDelete(&delete_GamRcLcLNucleuscLcLTransition);
      instance.SetDeleteArray(&deleteArray_GamRcLcLNucleuscLcLTransition);
      instance.SetDestructor(&destruct_GamRcLcLNucleuscLcLTransition);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Nucleus::Transition*)
   {
      return GenerateInitInstanceLocal((::GamR::Nucleus::Transition*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Nucleus::Transition*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLNucleuscLcLTransitionMap(void *p = nullptr);
   static void *newArray_GamRcLcLNucleuscLcLTransitionMap(Long_t size, void *p);
   static void delete_GamRcLcLNucleuscLcLTransitionMap(void *p);
   static void deleteArray_GamRcLcLNucleuscLcLTransitionMap(void *p);
   static void destruct_GamRcLcLNucleuscLcLTransitionMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Nucleus::TransitionMap*)
   {
      ::GamR::Nucleus::TransitionMap *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::Nucleus::TransitionMap >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Nucleus::TransitionMap", ::GamR::Nucleus::TransitionMap::Class_Version(), "Transition.hh", 46,
                  typeid(::GamR::Nucleus::TransitionMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::Nucleus::TransitionMap::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Nucleus::TransitionMap) );
      instance.SetNew(&new_GamRcLcLNucleuscLcLTransitionMap);
      instance.SetNewArray(&newArray_GamRcLcLNucleuscLcLTransitionMap);
      instance.SetDelete(&delete_GamRcLcLNucleuscLcLTransitionMap);
      instance.SetDeleteArray(&deleteArray_GamRcLcLNucleuscLcLTransitionMap);
      instance.SetDestructor(&destruct_GamRcLcLNucleuscLcLTransitionMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Nucleus::TransitionMap*)
   {
      return GenerateInitInstanceLocal((::GamR::Nucleus::TransitionMap*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Nucleus::TransitionMap*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLNucleuscLcLPhoton(void *p = nullptr);
   static void *newArray_GamRcLcLNucleuscLcLPhoton(Long_t size, void *p);
   static void delete_GamRcLcLNucleuscLcLPhoton(void *p);
   static void deleteArray_GamRcLcLNucleuscLcLPhoton(void *p);
   static void destruct_GamRcLcLNucleuscLcLPhoton(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Nucleus::Photon*)
   {
      ::GamR::Nucleus::Photon *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::Nucleus::Photon >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Nucleus::Photon", ::GamR::Nucleus::Photon::Class_Version(), "Photon.hh", 9,
                  typeid(::GamR::Nucleus::Photon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::Nucleus::Photon::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Nucleus::Photon) );
      instance.SetNew(&new_GamRcLcLNucleuscLcLPhoton);
      instance.SetNewArray(&newArray_GamRcLcLNucleuscLcLPhoton);
      instance.SetDelete(&delete_GamRcLcLNucleuscLcLPhoton);
      instance.SetDeleteArray(&deleteArray_GamRcLcLNucleuscLcLPhoton);
      instance.SetDestructor(&destruct_GamRcLcLNucleuscLcLPhoton);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Nucleus::Photon*)
   {
      return GenerateInitInstanceLocal((::GamR::Nucleus::Photon*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Nucleus::Photon*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLNucleuscLcLState(void *p = nullptr);
   static void *newArray_GamRcLcLNucleuscLcLState(Long_t size, void *p);
   static void delete_GamRcLcLNucleuscLcLState(void *p);
   static void deleteArray_GamRcLcLNucleuscLcLState(void *p);
   static void destruct_GamRcLcLNucleuscLcLState(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Nucleus::State*)
   {
      ::GamR::Nucleus::State *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::Nucleus::State >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Nucleus::State", ::GamR::Nucleus::State::Class_Version(), "State.hh", 11,
                  typeid(::GamR::Nucleus::State), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::Nucleus::State::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Nucleus::State) );
      instance.SetNew(&new_GamRcLcLNucleuscLcLState);
      instance.SetNewArray(&newArray_GamRcLcLNucleuscLcLState);
      instance.SetDelete(&delete_GamRcLcLNucleuscLcLState);
      instance.SetDeleteArray(&deleteArray_GamRcLcLNucleuscLcLState);
      instance.SetDestructor(&destruct_GamRcLcLNucleuscLcLState);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Nucleus::State*)
   {
      return GenerateInitInstanceLocal((::GamR::Nucleus::State*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Nucleus::State*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p = nullptr);
   static void *newArray_GamRcLcLNucleuscLcLLevelSchemecLcLState(Long_t size, void *p);
   static void delete_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p);
   static void deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p);
   static void destruct_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Nucleus::LevelScheme::State*)
   {
      ::GamR::Nucleus::LevelScheme::State *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::Nucleus::LevelScheme::State >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Nucleus::LevelScheme::State", ::GamR::Nucleus::LevelScheme::State::Class_Version(), "LevelScheme.hh", 13,
                  typeid(::GamR::Nucleus::LevelScheme::State), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::Nucleus::LevelScheme::State::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Nucleus::LevelScheme::State) );
      instance.SetNew(&new_GamRcLcLNucleuscLcLLevelSchemecLcLState);
      instance.SetNewArray(&newArray_GamRcLcLNucleuscLcLLevelSchemecLcLState);
      instance.SetDelete(&delete_GamRcLcLNucleuscLcLLevelSchemecLcLState);
      instance.SetDeleteArray(&deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLState);
      instance.SetDestructor(&destruct_GamRcLcLNucleuscLcLLevelSchemecLcLState);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Nucleus::LevelScheme::State*)
   {
      return GenerateInitInstanceLocal((::GamR::Nucleus::LevelScheme::State*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::State*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p = nullptr);
   static void *newArray_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(Long_t size, void *p);
   static void delete_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p);
   static void deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p);
   static void destruct_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Nucleus::LevelScheme::Transition*)
   {
      ::GamR::Nucleus::LevelScheme::Transition *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::Nucleus::LevelScheme::Transition >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Nucleus::LevelScheme::Transition", ::GamR::Nucleus::LevelScheme::Transition::Class_Version(), "LevelScheme.hh", 31,
                  typeid(::GamR::Nucleus::LevelScheme::Transition), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::Nucleus::LevelScheme::Transition::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Nucleus::LevelScheme::Transition) );
      instance.SetNew(&new_GamRcLcLNucleuscLcLLevelSchemecLcLTransition);
      instance.SetNewArray(&newArray_GamRcLcLNucleuscLcLLevelSchemecLcLTransition);
      instance.SetDelete(&delete_GamRcLcLNucleuscLcLLevelSchemecLcLTransition);
      instance.SetDeleteArray(&deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLTransition);
      instance.SetDestructor(&destruct_GamRcLcLNucleuscLcLLevelSchemecLcLTransition);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Nucleus::LevelScheme::Transition*)
   {
      return GenerateInitInstanceLocal((::GamR::Nucleus::LevelScheme::Transition*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Transition*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p = nullptr);
   static void *newArray_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(Long_t size, void *p);
   static void delete_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p);
   static void deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p);
   static void destruct_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Nucleus::LevelScheme::Scheme*)
   {
      ::GamR::Nucleus::LevelScheme::Scheme *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GamR::Nucleus::LevelScheme::Scheme >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Nucleus::LevelScheme::Scheme", ::GamR::Nucleus::LevelScheme::Scheme::Class_Version(), "LevelScheme.hh", 56,
                  typeid(::GamR::Nucleus::LevelScheme::Scheme), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GamR::Nucleus::LevelScheme::Scheme::Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Nucleus::LevelScheme::Scheme) );
      instance.SetNew(&new_GamRcLcLNucleuscLcLLevelSchemecLcLScheme);
      instance.SetNewArray(&newArray_GamRcLcLNucleuscLcLLevelSchemecLcLScheme);
      instance.SetDelete(&delete_GamRcLcLNucleuscLcLLevelSchemecLcLScheme);
      instance.SetDeleteArray(&deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLScheme);
      instance.SetDestructor(&destruct_GamRcLcLNucleuscLcLLevelSchemecLcLScheme);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Nucleus::LevelScheme::Scheme*)
   {
      return GenerateInitInstanceLocal((::GamR::Nucleus::LevelScheme::Scheme*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Scheme*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
atomic_TClass_ptr Transition::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Transition::Class_Name()
{
   return "GamR::Nucleus::Transition";
}

//______________________________________________________________________________
const char *Transition::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Transition*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Transition::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Transition*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Transition::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Transition*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Transition::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Transition*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
atomic_TClass_ptr TransitionMap::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TransitionMap::Class_Name()
{
   return "GamR::Nucleus::TransitionMap";
}

//______________________________________________________________________________
const char *TransitionMap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::TransitionMap*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TransitionMap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::TransitionMap*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TransitionMap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::TransitionMap*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TransitionMap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::TransitionMap*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
atomic_TClass_ptr Photon::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Photon::Class_Name()
{
   return "GamR::Nucleus::Photon";
}

//______________________________________________________________________________
const char *Photon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Photon*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Photon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Photon*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Photon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Photon*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Photon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::Photon*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
atomic_TClass_ptr State::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *State::Class_Name()
{
   return "GamR::Nucleus::State";
}

//______________________________________________________________________________
const char *State::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::State*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int State::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::State*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *State::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::State*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *State::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::State*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace GamR {
   namespace Nucleus {
      namespace LevelScheme {
//______________________________________________________________________________
atomic_TClass_ptr State::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *State::Class_Name()
{
   return "GamR::Nucleus::LevelScheme::State";
}

//______________________________________________________________________________
const char *State::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::State*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int State::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::State*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *State::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::State*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *State::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::State*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
namespace GamR {
   namespace Nucleus {
      namespace LevelScheme {
//______________________________________________________________________________
atomic_TClass_ptr Transition::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Transition::Class_Name()
{
   return "GamR::Nucleus::LevelScheme::Transition";
}

//______________________________________________________________________________
const char *Transition::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Transition*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Transition::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Transition*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Transition::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Transition*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Transition::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Transition*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
namespace GamR {
   namespace Nucleus {
      namespace LevelScheme {
//______________________________________________________________________________
atomic_TClass_ptr Scheme::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Scheme::Class_Name()
{
   return "GamR::Nucleus::LevelScheme::Scheme";
}

//______________________________________________________________________________
const char *Scheme::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Scheme*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Scheme::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Scheme*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Scheme::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Scheme*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Scheme::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GamR::Nucleus::LevelScheme::Scheme*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
void Transition::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::Nucleus::Transition.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::Nucleus::Transition::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::Nucleus::Transition::Class(),this);
   }
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLNucleuscLcLTransition(void *p) {
      return  p ? new(p) ::GamR::Nucleus::Transition : new ::GamR::Nucleus::Transition;
   }
   static void *newArray_GamRcLcLNucleuscLcLTransition(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::Nucleus::Transition[nElements] : new ::GamR::Nucleus::Transition[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLNucleuscLcLTransition(void *p) {
      delete ((::GamR::Nucleus::Transition*)p);
   }
   static void deleteArray_GamRcLcLNucleuscLcLTransition(void *p) {
      delete [] ((::GamR::Nucleus::Transition*)p);
   }
   static void destruct_GamRcLcLNucleuscLcLTransition(void *p) {
      typedef ::GamR::Nucleus::Transition current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Nucleus::Transition

namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
void TransitionMap::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::Nucleus::TransitionMap.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::Nucleus::TransitionMap::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::Nucleus::TransitionMap::Class(),this);
   }
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLNucleuscLcLTransitionMap(void *p) {
      return  p ? new(p) ::GamR::Nucleus::TransitionMap : new ::GamR::Nucleus::TransitionMap;
   }
   static void *newArray_GamRcLcLNucleuscLcLTransitionMap(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::Nucleus::TransitionMap[nElements] : new ::GamR::Nucleus::TransitionMap[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLNucleuscLcLTransitionMap(void *p) {
      delete ((::GamR::Nucleus::TransitionMap*)p);
   }
   static void deleteArray_GamRcLcLNucleuscLcLTransitionMap(void *p) {
      delete [] ((::GamR::Nucleus::TransitionMap*)p);
   }
   static void destruct_GamRcLcLNucleuscLcLTransitionMap(void *p) {
      typedef ::GamR::Nucleus::TransitionMap current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Nucleus::TransitionMap

namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
void Photon::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::Nucleus::Photon.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::Nucleus::Photon::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::Nucleus::Photon::Class(),this);
   }
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLNucleuscLcLPhoton(void *p) {
      return  p ? new(p) ::GamR::Nucleus::Photon : new ::GamR::Nucleus::Photon;
   }
   static void *newArray_GamRcLcLNucleuscLcLPhoton(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::Nucleus::Photon[nElements] : new ::GamR::Nucleus::Photon[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLNucleuscLcLPhoton(void *p) {
      delete ((::GamR::Nucleus::Photon*)p);
   }
   static void deleteArray_GamRcLcLNucleuscLcLPhoton(void *p) {
      delete [] ((::GamR::Nucleus::Photon*)p);
   }
   static void destruct_GamRcLcLNucleuscLcLPhoton(void *p) {
      typedef ::GamR::Nucleus::Photon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Nucleus::Photon

namespace GamR {
   namespace Nucleus {
//______________________________________________________________________________
void State::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::Nucleus::State.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::Nucleus::State::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::Nucleus::State::Class(),this);
   }
}

} // namespace GamR::Nucleus
} // namespace GamR::Nucleus
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLNucleuscLcLState(void *p) {
      return  p ? new(p) ::GamR::Nucleus::State : new ::GamR::Nucleus::State;
   }
   static void *newArray_GamRcLcLNucleuscLcLState(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::Nucleus::State[nElements] : new ::GamR::Nucleus::State[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLNucleuscLcLState(void *p) {
      delete ((::GamR::Nucleus::State*)p);
   }
   static void deleteArray_GamRcLcLNucleuscLcLState(void *p) {
      delete [] ((::GamR::Nucleus::State*)p);
   }
   static void destruct_GamRcLcLNucleuscLcLState(void *p) {
      typedef ::GamR::Nucleus::State current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Nucleus::State

namespace GamR {
   namespace Nucleus {
      namespace LevelScheme {
//______________________________________________________________________________
void State::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::Nucleus::LevelScheme::State.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::Nucleus::LevelScheme::State::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::Nucleus::LevelScheme::State::Class(),this);
   }
}

} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p) {
      return  p ? new(p) ::GamR::Nucleus::LevelScheme::State : new ::GamR::Nucleus::LevelScheme::State;
   }
   static void *newArray_GamRcLcLNucleuscLcLLevelSchemecLcLState(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::Nucleus::LevelScheme::State[nElements] : new ::GamR::Nucleus::LevelScheme::State[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p) {
      delete ((::GamR::Nucleus::LevelScheme::State*)p);
   }
   static void deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p) {
      delete [] ((::GamR::Nucleus::LevelScheme::State*)p);
   }
   static void destruct_GamRcLcLNucleuscLcLLevelSchemecLcLState(void *p) {
      typedef ::GamR::Nucleus::LevelScheme::State current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Nucleus::LevelScheme::State

namespace GamR {
   namespace Nucleus {
      namespace LevelScheme {
//______________________________________________________________________________
void Transition::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::Nucleus::LevelScheme::Transition.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::Nucleus::LevelScheme::Transition::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::Nucleus::LevelScheme::Transition::Class(),this);
   }
}

} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p) {
      return  p ? new(p) ::GamR::Nucleus::LevelScheme::Transition : new ::GamR::Nucleus::LevelScheme::Transition;
   }
   static void *newArray_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::Nucleus::LevelScheme::Transition[nElements] : new ::GamR::Nucleus::LevelScheme::Transition[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p) {
      delete ((::GamR::Nucleus::LevelScheme::Transition*)p);
   }
   static void deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p) {
      delete [] ((::GamR::Nucleus::LevelScheme::Transition*)p);
   }
   static void destruct_GamRcLcLNucleuscLcLLevelSchemecLcLTransition(void *p) {
      typedef ::GamR::Nucleus::LevelScheme::Transition current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Nucleus::LevelScheme::Transition

namespace GamR {
   namespace Nucleus {
      namespace LevelScheme {
//______________________________________________________________________________
void Scheme::Streamer(TBuffer &R__b)
{
   // Stream an object of class GamR::Nucleus::LevelScheme::Scheme.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GamR::Nucleus::LevelScheme::Scheme::Class(),this);
   } else {
      R__b.WriteClassBuffer(GamR::Nucleus::LevelScheme::Scheme::Class(),this);
   }
}

} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
} // namespace GamR::Nucleus::LevelScheme
namespace ROOT {
   // Wrappers around operator new
   static void *new_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p) {
      return  p ? new(p) ::GamR::Nucleus::LevelScheme::Scheme : new ::GamR::Nucleus::LevelScheme::Scheme;
   }
   static void *newArray_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(Long_t nElements, void *p) {
      return p ? new(p) ::GamR::Nucleus::LevelScheme::Scheme[nElements] : new ::GamR::Nucleus::LevelScheme::Scheme[nElements];
   }
   // Wrapper around operator delete
   static void delete_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p) {
      delete ((::GamR::Nucleus::LevelScheme::Scheme*)p);
   }
   static void deleteArray_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p) {
      delete [] ((::GamR::Nucleus::LevelScheme::Scheme*)p);
   }
   static void destruct_GamRcLcLNucleuscLcLLevelSchemecLcLScheme(void *p) {
      typedef ::GamR::Nucleus::LevelScheme::Scheme current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Nucleus::LevelScheme::Scheme

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
   static TClass *vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR_Dictionary();
   static void vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR_TClassManip(TClass*);
   static void *new_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p = nullptr);
   static void *newArray_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(Long_t size, void *p);
   static void delete_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p);
   static void deleteArray_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p);
   static void destruct_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<GamR::Nucleus::LevelScheme::Transition>*)
   {
      vector<GamR::Nucleus::LevelScheme::Transition> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<GamR::Nucleus::LevelScheme::Transition>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<GamR::Nucleus::LevelScheme::Transition>", -2, "c++/v1/vector", 471,
                  typeid(vector<GamR::Nucleus::LevelScheme::Transition>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR_Dictionary, isa_proxy, 0,
                  sizeof(vector<GamR::Nucleus::LevelScheme::Transition>) );
      instance.SetNew(&new_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR);
      instance.SetNewArray(&newArray_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR);
      instance.SetDelete(&delete_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR);
      instance.SetDeleteArray(&deleteArray_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR);
      instance.SetDestructor(&destruct_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<GamR::Nucleus::LevelScheme::Transition> >()));

      ::ROOT::AddClassAlternate("vector<GamR::Nucleus::LevelScheme::Transition>","std::__1::vector<GamR::Nucleus::LevelScheme::Transition, std::__1::allocator<GamR::Nucleus::LevelScheme::Transition> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<GamR::Nucleus::LevelScheme::Transition>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<GamR::Nucleus::LevelScheme::Transition>*)nullptr)->GetClass();
      vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::Nucleus::LevelScheme::Transition> : new vector<GamR::Nucleus::LevelScheme::Transition>;
   }
   static void *newArray_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<GamR::Nucleus::LevelScheme::Transition>[nElements] : new vector<GamR::Nucleus::LevelScheme::Transition>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p) {
      delete ((vector<GamR::Nucleus::LevelScheme::Transition>*)p);
   }
   static void deleteArray_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p) {
      delete [] ((vector<GamR::Nucleus::LevelScheme::Transition>*)p);
   }
   static void destruct_vectorlEGamRcLcLNucleuscLcLLevelSchemecLcLTransitiongR(void *p) {
      typedef vector<GamR::Nucleus::LevelScheme::Transition> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<GamR::Nucleus::LevelScheme::Transition>

namespace ROOT {
   static TClass *maplEstringcOGamRcLcLNucleuscLcLTransitiongR_Dictionary();
   static void maplEstringcOGamRcLcLNucleuscLcLTransitiongR_TClassManip(TClass*);
   static void *new_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p = nullptr);
   static void *newArray_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(Long_t size, void *p);
   static void delete_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p);
   static void deleteArray_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p);
   static void destruct_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,GamR::Nucleus::Transition>*)
   {
      map<string,GamR::Nucleus::Transition> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,GamR::Nucleus::Transition>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,GamR::Nucleus::Transition>", -2, "c++/v1/map", 900,
                  typeid(map<string,GamR::Nucleus::Transition>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOGamRcLcLNucleuscLcLTransitiongR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,GamR::Nucleus::Transition>) );
      instance.SetNew(&new_maplEstringcOGamRcLcLNucleuscLcLTransitiongR);
      instance.SetNewArray(&newArray_maplEstringcOGamRcLcLNucleuscLcLTransitiongR);
      instance.SetDelete(&delete_maplEstringcOGamRcLcLNucleuscLcLTransitiongR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOGamRcLcLNucleuscLcLTransitiongR);
      instance.SetDestructor(&destruct_maplEstringcOGamRcLcLNucleuscLcLTransitiongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,GamR::Nucleus::Transition> >()));

      ::ROOT::AddClassAlternate("map<string,GamR::Nucleus::Transition>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, GamR::Nucleus::Transition, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, GamR::Nucleus::Transition> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,GamR::Nucleus::Transition>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOGamRcLcLNucleuscLcLTransitiongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,GamR::Nucleus::Transition>*)nullptr)->GetClass();
      maplEstringcOGamRcLcLNucleuscLcLTransitiongR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOGamRcLcLNucleuscLcLTransitiongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Nucleus::Transition> : new map<string,GamR::Nucleus::Transition>;
   }
   static void *newArray_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Nucleus::Transition>[nElements] : new map<string,GamR::Nucleus::Transition>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p) {
      delete ((map<string,GamR::Nucleus::Transition>*)p);
   }
   static void deleteArray_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p) {
      delete [] ((map<string,GamR::Nucleus::Transition>*)p);
   }
   static void destruct_maplEstringcOGamRcLcLNucleuscLcLTransitiongR(void *p) {
      typedef map<string,GamR::Nucleus::Transition> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,GamR::Nucleus::Transition>

namespace ROOT {
   static TClass *maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR_Dictionary();
   static void maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR_TClassManip(TClass*);
   static void *new_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p = nullptr);
   static void *newArray_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(Long_t size, void *p);
   static void delete_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p);
   static void deleteArray_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p);
   static void destruct_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,GamR::Nucleus::LevelScheme::State>*)
   {
      map<string,GamR::Nucleus::LevelScheme::State> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,GamR::Nucleus::LevelScheme::State>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,GamR::Nucleus::LevelScheme::State>", -2, "c++/v1/map", 900,
                  typeid(map<string,GamR::Nucleus::LevelScheme::State>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,GamR::Nucleus::LevelScheme::State>) );
      instance.SetNew(&new_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR);
      instance.SetNewArray(&newArray_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR);
      instance.SetDelete(&delete_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR);
      instance.SetDestructor(&destruct_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,GamR::Nucleus::LevelScheme::State> >()));

      ::ROOT::AddClassAlternate("map<string,GamR::Nucleus::LevelScheme::State>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, GamR::Nucleus::LevelScheme::State, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, GamR::Nucleus::LevelScheme::State> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,GamR::Nucleus::LevelScheme::State>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,GamR::Nucleus::LevelScheme::State>*)nullptr)->GetClass();
      maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Nucleus::LevelScheme::State> : new map<string,GamR::Nucleus::LevelScheme::State>;
   }
   static void *newArray_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,GamR::Nucleus::LevelScheme::State>[nElements] : new map<string,GamR::Nucleus::LevelScheme::State>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p) {
      delete ((map<string,GamR::Nucleus::LevelScheme::State>*)p);
   }
   static void deleteArray_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p) {
      delete [] ((map<string,GamR::Nucleus::LevelScheme::State>*)p);
   }
   static void destruct_maplEstringcOGamRcLcLNucleuscLcLLevelSchemecLcLStategR(void *p) {
      typedef map<string,GamR::Nucleus::LevelScheme::State> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,GamR::Nucleus::LevelScheme::State>

namespace {
  void TriggerDictionaryInitialization_libgamr_nucleus_Impl() {
    static const char* headers[] = {
"Photon.hh",
"State.hh",
"Transition.hh",
"LevelScheme.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/nucleus",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/nucleus",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/nucleus/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_nucleus dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace Nucleus{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/nucleus/Transition.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Transition.hh")))  __attribute__((annotate("$clingAutoload$Photon.hh")))  Transition;}}
namespace GamR{namespace Nucleus{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/nucleus/Transition.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Transition.hh")))  __attribute__((annotate("$clingAutoload$Photon.hh")))  TransitionMap;}}
namespace GamR{namespace Nucleus{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/nucleus/Photon.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Photon.hh")))  Photon;}}
namespace GamR{namespace Nucleus{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/nucleus/State.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$State.hh")))  State;}}
namespace GamR{namespace Nucleus{namespace LevelScheme{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/nucleus/LevelScheme.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$LevelScheme.hh")))  State;}}}
namespace GamR{namespace Nucleus{namespace LevelScheme{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/nucleus/LevelScheme.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$LevelScheme.hh")))  Transition;}}}
namespace GamR{namespace Nucleus{namespace LevelScheme{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/nucleus/LevelScheme.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$LevelScheme.hh")))  Scheme;}}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_nucleus dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Photon.hh"
#include "State.hh"
#include "Transition.hh"
#include "LevelScheme.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::Nucleus::LevelScheme::Scheme", payloadCode, "@",
"GamR::Nucleus::LevelScheme::Scheme::fgIsA", payloadCode, "@",
"GamR::Nucleus::LevelScheme::State", payloadCode, "@",
"GamR::Nucleus::LevelScheme::State::fgIsA", payloadCode, "@",
"GamR::Nucleus::LevelScheme::Transition", payloadCode, "@",
"GamR::Nucleus::LevelScheme::Transition::fgIsA", payloadCode, "@",
"GamR::Nucleus::Photon", payloadCode, "@",
"GamR::Nucleus::Photon::fgIsA", payloadCode, "@",
"GamR::Nucleus::State", payloadCode, "@",
"GamR::Nucleus::State::fgIsA", payloadCode, "@",
"GamR::Nucleus::Transition", payloadCode, "@",
"GamR::Nucleus::Transition::fgIsA", payloadCode, "@",
"GamR::Nucleus::TransitionMap", payloadCode, "@",
"GamR::Nucleus::TransitionMap::fgIsA", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_nucleus",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_nucleus_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_nucleus_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_nucleus() {
  TriggerDictionaryInitialization_libgamr_nucleus_Impl();
}
