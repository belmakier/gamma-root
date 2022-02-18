// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__gamr_abbrevs
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
#include "Abbreviations.hh"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace {
  void TriggerDictionaryInitialization_libgamr_abbrevs_Impl() {
    static const char* headers[] = {
"Abbreviations.hh",
nullptr
    };
    static const char* includePaths[] = {
"/Users/99j/git/gamma-root/src/lib/abbrevs",
"/Users/99j/root_build/include",
"/Users/99j/git/gamma-root/src/lib",
"/Users/99j/git/gamma-root/src/lib/abbrevs",
"/Users/99j/root_build/include/",
"/Users/99j/git/gamma-root/build/src/lib/abbrevs/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libgamr_abbrevs dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libgamr_abbrevs dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Abbreviations.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"add", payloadCode, "@",
"add2", payloadCode, "@",
"bp", payloadCode, "@",
"bsx", payloadCode, "@",
"bsy", payloadCode, "@",
"ca", payloadCode, "@",
"cbp", payloadCode, "@",
"ct", payloadCode, "@",
"ctbs", payloadCode, "@",
"fp", payloadCode, "@",
"gx", payloadCode, "@",
"gy", payloadCode, "@",
"ig", payloadCode, "@",
"igbs", payloadCode, "@",
"lin", payloadCode, "@",
"log", payloadCode, "@",
"ls", payloadCode, "@",
"ls2", payloadCode, "@",
"ns", payloadCode, "@",
"nsbs", payloadCode, "@",
"os", payloadCode, "@",
"pf", payloadCode, "@",
"pfconf", payloadCode, "@",
"pfprint", payloadCode, "@",
"pfsave", payloadCode, "@",
"px", payloadCode, "@",
"py", payloadCode, "@",
"rb", payloadCode, "@",
"sp", payloadCode, "@",
"sp2", payloadCode, "@",
"ss", payloadCode, "@",
"uz", payloadCode, "@",
"uzx", payloadCode, "@",
"uzy", payloadCode, "@",
"zx", payloadCode, "@",
"zy", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libgamr_abbrevs",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libgamr_abbrevs_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libgamr_abbrevs_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libgamr_abbrevs() {
  TriggerDictionaryInitialization_libgamr_abbrevs_Impl();
}
