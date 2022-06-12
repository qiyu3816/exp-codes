/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from IDL_28.idl using "idltoc".
The idltoc tool is part of the RTI Data Distribution Service distribution.
For more information, type 'idltoc -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef IDL_28_h
#define IDL_28_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif
#else
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

struct a_bSeq;
class a_bTypeSupport;
class a_bDataWriter;
class a_bDataReader;

class a_b
{
  public: 
    typedef struct a_bSeq Seq;
    typedef a_bTypeSupport TypeSupport;
    typedef a_bDataWriter DataWriter;
    typedef a_bDataReader DataReader;

    CDR_UnsignedShort c=17;
    CDR_UnsignedLong d=18;

}

extern const char *a_bTYPENAME;

REDA_DEFINE_SEQUENCE_STRUCT(a_bSeq, a_b);

REDA_DEFINE_SEQUENCE_IN_C(a_bSeq, a_b);


NDDSUSERDllExport extern RTI_BOOL
a_b_initialize(a_b* sample)
{
    CDR_Primitive_init_UnsignedShort(&sample->c);
    CDR_Primitive_init_UnsignedLong(&sample->d);


    return RTI_TRUE;
}

NDDSUSERDllExport extern RTI_BOOL
a_b_finalize(a_b* sample)
{
    UNUSED_ARG(sample);


    return RTI_TRUE;
}
#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif /* IDL_28 */
