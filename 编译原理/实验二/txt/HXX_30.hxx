/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from IDL_30.idl using "idltoc".
The idltoc tool is part of the RTI Data Distribution Service distribution.
For more information, type 'idltoc -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef IDL_30_h
#define IDL_30_h

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

struct ASeq;
class ATypeSupport;
class ADataWriter;
class ADataReader;

class A
{
  public: 
    typedef struct ASeq Seq;
    typedef ATypeSupport TypeSupport;
    typedef ADataWriter DataWriter;
    typedef ADataReader DataReader;

    CDR_UnsignedLong i1=1;

}

extern const char *ATYPENAME;

REDA_DEFINE_SEQUENCE_STRUCT(ASeq, A);

REDA_DEFINE_SEQUENCE_IN_C(ASeq, A);


NDDSUSERDllExport extern RTI_BOOL
A_initialize(A* sample)
{
    CDR_Primitive_init_UnsignedLong(&sample->i1);


    return RTI_TRUE;
}

NDDSUSERDllExport extern RTI_BOOL
A_finalize(A* sample)
{
    UNUSED_ARG(sample);


    return RTI_TRUE;
}

struct BSeq;
class BTypeSupport;
class BDataWriter;
class BDataReader;

class B
{
  public: 
    typedef struct BSeq Seq;
    typedef BTypeSupport TypeSupport;
    typedef BDataWriter DataWriter;
    typedef BDataReader DataReader;

    CDR_Float i1=3.14;

}

extern const char *BTYPENAME;

REDA_DEFINE_SEQUENCE_STRUCT(BSeq, B);

REDA_DEFINE_SEQUENCE_IN_C(BSeq, B);


NDDSUSERDllExport extern RTI_BOOL
B_initialize(B* sample)
{
    CDR_Primitive_init_Float(&sample->i1);


    return RTI_TRUE;
}

NDDSUSERDllExport extern RTI_BOOL
B_finalize(B* sample)
{
    UNUSED_ARG(sample);


    return RTI_TRUE;
}

struct CSeq;
class CTypeSupport;
class CDataWriter;
class CDataReader;

class C
{
  public: 
    typedef struct CSeq Seq;
    typedef CTypeSupport TypeSupport;
    typedef CDataWriter DataWriter;
    typedef CDataReader DataReader;

    CDR_String i1="hello";

}

extern const char *CTYPENAME;

REDA_DEFINE_SEQUENCE_STRUCT(CSeq, C);

REDA_DEFINE_SEQUENCE_IN_C(CSeq, C);


NDDSUSERDllExport extern RTI_BOOL
C_initialize(C* sample)
{
    if (!CDR_String_initialize(&sample->i1, (255)))
    {
        return RTI_FALSE;
    }


    return RTI_TRUE;
}

NDDSUSERDllExport extern RTI_BOOL
C_finalize(C* sample)
{
    UNUSED_ARG(sample);
    CDR_String_finalize(&sample->i1);



    return RTI_TRUE;
}
#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif /* IDL_30 */
