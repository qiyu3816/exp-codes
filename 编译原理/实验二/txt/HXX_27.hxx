/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from IDL_27.idl using "idltoc".
The idltoc tool is part of the RTI Data Distribution Service distribution.
For more information, type 'idltoc -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef IDL_27_h
#define IDL_27_h

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

struct space_ASeq;
class space_ATypeSupport;
class space_ADataWriter;
class space_ADataReader;

class space_A
{
  public: 
    typedef struct space_ASeq Seq;
    typedef space_ATypeSupport TypeSupport;
    typedef space_ADataWriter DataWriter;
    typedef space_ADataReader DataReader;

    CDR_Short arr[10]={0,1,2,3,4,5,6,7,8,9};
    CDR_Short i1=10;
    CDR_UnsignedLongLong i11=1000;
    CDR_Short i2=10;
    CDR_UnsignedLong i10=100;
    CDR_Long i3=100;
    CDR_Long i4=100;
    CDR_UnsignedLongLong i12=1000;
    CDR_LongLong i5=1000;
    CDR_LongLong i6=1000;
    CDR_Char c0='a';
    CDR_UnsignedShort i7=10;
    CDR_String c1="abc";
    CDR_UnsignedShort i8=10;
    CDR_Boolean c2=true;
    CDR_UnsignedLong i9=100;
    CDR_Float c3=10.901f;
    CDR_Double c4=23.234d;
    CDR_LongDouble c5=12.23456432235d;

}

extern const char *space_ATYPENAME;

REDA_DEFINE_SEQUENCE_STRUCT(space_ASeq, space_A);

REDA_DEFINE_SEQUENCE_IN_C(space_ASeq, space_A);


NDDSUSERDllExport extern RTI_BOOL
space_A_initialize(space_A* sample)
{
    CDR_Primitive_init_Array(
        sample->arr, ((10)*CDR_SHORT_SIZE));
    CDR_Primitive_init_Short(&sample->i1);
    CDR_Primitive_init_UnsignedLongLong(&sample->i11);
    CDR_Primitive_init_Short(&sample->i2);
    CDR_Primitive_init_UnsignedLong(&sample->i10);
    CDR_Primitive_init_Long(&sample->i3);
    CDR_Primitive_init_Long(&sample->i4);
    CDR_Primitive_init_UnsignedLongLong(&sample->i12);
    CDR_Primitive_init_LongLong(&sample->i5);
    CDR_Primitive_init_LongLong(&sample->i6);
    CDR_Primitive_init_Char(&sample->c0);
    CDR_Primitive_init_UnsignedShort(&sample->i7);
    if (!CDR_String_initialize(&sample->c1, (255)))
    {
        return RTI_FALSE;
    }
    CDR_Primitive_init_UnsignedShort(&sample->i8);
    CDR_Primitive_init_Boolean(&sample->c2);
    CDR_Primitive_init_UnsignedLong(&sample->i9);
    CDR_Primitive_init_Float(&sample->c3);
    CDR_Primitive_init_Double(&sample->c4);
    CDR_Primitive_init_LongDouble(&sample->c5);


    return RTI_TRUE;
}

NDDSUSERDllExport extern RTI_BOOL
space_A_finalize(space_A* sample)
{
    UNUSED_ARG(sample);
    {
        RTI_UINT32 i;

        for (i = 0; i < (10); i++)
        {
            if (!CDR_Short_copy(&dst->arr[i], &src->arr[i]))
            {
                return RTI_FALSE;
            }
        }
    }
    CDR_String_finalize(&sample->c1);



    return RTI_TRUE;
}
#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif /* IDL_27 */
