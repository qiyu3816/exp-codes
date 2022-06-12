/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from IDL_31.idl using "idltoc".
The idltoc tool is part of the RTI Data Distribution Service distribution.
For more information, type 'idltoc -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef IDL_31_h
#define IDL_31_h

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

    CDR_String s[9]={"hello"};

}

extern const char *ATYPENAME;

REDA_DEFINE_SEQUENCE_STRUCT(ASeq, A);

REDA_DEFINE_SEQUENCE_IN_C(ASeq, A);


NDDSUSERDllExport extern RTI_BOOL
A_initialize(A* sample)
{
    CDR_Primitive_init_Array(
        sample->s, ((9)*CDR_STRING_SIZE));
    {
        for(RTI_UINT32 i = 0; i < 9; i++)
        {
            if (!CDR_String_initialize(&sample->s[i], (255)))
            {
                return RTI_FALSE;
            }
        }
    }


    return RTI_TRUE;
}

NDDSUSERDllExport extern RTI_BOOL
A_finalize(A* sample)
{
    UNUSED_ARG(sample);
    {
        RTI_UINT32 i;

        for (i = 0; i < (9); i++)
        {
            CDR_String_finalize(&sample->s[i]);
            if (!CDR_String_copy(&dst->s[i], &src->s[i]))
            {
                return RTI_FALSE;
            }
        }
    }



    return RTI_TRUE;
}
#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif /* IDL_31 */
