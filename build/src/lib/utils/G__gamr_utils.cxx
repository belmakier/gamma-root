// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_utils
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
#include "REPL.hh"
#include "Utilities.hh"
#include "Tuples.hh"
#include "RTTI.hh"

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
            instance("GamR", 0 /*version*/, "REPL.hh", 10,
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
   namespace Utils {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *GamRcLcLUtils_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("GamR::Utils", 0 /*version*/, "REPL.hh", 11,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &GamRcLcLUtils_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *GamRcLcLUtils_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   static TClass *GamRcLcLUtilscLcLREPL_Dictionary();
   static void GamRcLcLUtilscLcLREPL_TClassManip(TClass*);
   static void delete_GamRcLcLUtilscLcLREPL(void *p);
   static void deleteArray_GamRcLcLUtilscLcLREPL(void *p);
   static void destruct_GamRcLcLUtilscLcLREPL(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GamR::Utils::REPL*)
   {
      ::GamR::Utils::REPL *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::GamR::Utils::REPL));
      static ::ROOT::TGenericClassInfo 
         instance("GamR::Utils::REPL", "REPL.hh", 13,
                  typeid(::GamR::Utils::REPL), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GamRcLcLUtilscLcLREPL_Dictionary, isa_proxy, 4,
                  sizeof(::GamR::Utils::REPL) );
      instance.SetDelete(&delete_GamRcLcLUtilscLcLREPL);
      instance.SetDeleteArray(&deleteArray_GamRcLcLUtilscLcLREPL);
      instance.SetDestructor(&destruct_GamRcLcLUtilscLcLREPL);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GamR::Utils::REPL*)
   {
      return GenerateInitInstanceLocal((::GamR::Utils::REPL*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GamR::Utils::REPL*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GamRcLcLUtilscLcLREPL_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::GamR::Utils::REPL*)nullptr)->GetClass();
      GamRcLcLUtilscLcLREPL_TClassManip(theClass);
   return theClass;
   }

   static void GamRcLcLUtilscLcLREPL_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","/Users/99j/git/gamma-root/src/lib/utils/REPL.hh");
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GamRcLcLUtilscLcLREPL(void *p) {
      delete ((::GamR::Utils::REPL*)p);
   }
   static void deleteArray_GamRcLcLUtilscLcLREPL(void *p) {
      delete [] ((::GamR::Utils::REPL*)p);
   }
   static void destruct_GamRcLcLUtilscLcLREPL(void *p) {
      typedef ::GamR::Utils::REPL current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GamR::Utils::REPL

namespace {
  void TriggerDictionaryInitialization_libgamr_utils_Impl() {
    static const char* headers[] = {
"REPL.hh",
"Utilities.hh",
"Tuples.hh",
"RTTI.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/utils",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib/utils",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/utils/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_utils dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace GamR{namespace Utils{class __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(file_name@@@/Users/99j/git/gamma-root/src/lib/utils/REPL.hh)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$REPL.hh")))  REPL;}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_utils dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "REPL.hh"
#include "Utilities.hh"
#include "Tuples.hh"
#include "RTTI.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"GamR::Utils::Fac10", payloadCode, "@",
"GamR::Utils::GetClick", payloadCode, "@",
"GamR::Utils::GetHist1D", payloadCode, "@",
"GamR::Utils::GetHist2D", payloadCode, "@",
"GamR::Utils::GetHists1D", payloadCode, "@",
"GamR::Utils::GetInput", payloadCode, "@",
"GamR::Utils::GetNPads", payloadCode, "@",
"GamR::Utils::REPL", payloadCode, "@",
"GamR::Utils::Simps", payloadCode, "@",
"GamR::Utils::c_to_f_str", payloadCode, "@",
"GamR::Utils::catcherr", payloadCode, "@",
"GamR::Utils::getline", payloadCode, "@",
"GamR::Utils::wrresult", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_utils",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_utils_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_utils_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_utils() {
  TriggerDictionaryInitialization_libgamr_utils_Impl();
}
