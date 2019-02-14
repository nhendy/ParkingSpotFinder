/*

Copyright (C) 2015-2016  BridgeTek Pte Ltd 
THIS SOFTWARE IS PROVIDED BY BridgeTek Pte Ltd "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
BridgeTek Pte Ltd BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Author: Jan Boon <jan.boon@kaetemi.be>

*/

#ifndef FT_ESD_H
#define FT_ESD_H

/*
Type definition

ESD_TYPE(ft_uint32_t, Native = UInt32, Edit = Int)

ESD_TYPE(char *, Native = Latin1, Edit = String)

ESD_TYPE(Esd_BitmapCell *, Native = Pointer, Edit = Library)

typedef ft_int32_t ft_int32_f4_t;
ESD_TYPE(ft_int32_f4_t, Native = Int32, Edit = Fixed4)

*/

#define ESD_TYPE(name, ...)

/*
Enum definition.
Parses the enum identifiers, does not care about the integer or any other type of values

Usage examples:

ESD_ENUM(BitmapFormat, Type = ft_uint32_t)
#define RGB 1
#define ARGB 2
ESD_END()

ESD_ENUM(BitmapFormat)
enum BitmapFormat
{
RGB = 1,
ARGB
};
ESD_END()

*/

#define ESD_ENUM(name, ...)
#define ESD_IDENTIFIER(name, ...)
#define ESD_END()

/* Node definition

Usage examples:

ESD_FUNCTION(testPrint, DisplayName = "Test Print", Icon = ":/icons/card-address.png")
ESD_PARAMETER(message, Type = char *)
void testPrint(char *message);

ESD_FUNCTION(Ft_Gpu_Copro_SendCmd, Include = "FT_Gpu_Hal.h")
ESD_PARAMETER(host, Type = Ft_Gpu_Hal_Context_t *, Default = "Ft_App_Get_Host()", Hidden, Internal)
ESD_PARAMETER(cmd, Type = ft_uint32_t)

*/

#define ESD_FUNCTION(name, ...)
#define ESD_METHOD(name, ...)
#define ESD_UPDATE(name, ...)
#define ESD_RENDER(name, ...)

#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)

#define ESD_PARAMETER(name, ...)

#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)

#define ESD_CATEGORY(name, ...)

#include "FT_DataTypes.h"
#include "FT_Platform.h"

ESD_TYPE(void, Native = Void)
ESD_TYPE(char, Native = Char, Edit = String)
ESD_TYPE(signed char, Native = Int8, Edit = Integer)
ESD_TYPE(short, Native = Int16, Edit = Integer)
ESD_TYPE(int, Native = Int32, Edit = Integer)
ESD_TYPE(long, Native = Int32, Edit = Integer)
ESD_TYPE(long long, Native = Int64, Edit = Integer)
ESD_TYPE(unsigned char, Native = UInt8, Edit = Integer)
ESD_TYPE(unsigned short, Native = UInt16, Edit = Integer)
ESD_TYPE(unsigned int, Native = UInt32, Edit = Integer)
ESD_TYPE(unsigned long, Native = UInt32, Edit = Integer)
ESD_TYPE(unsigned long long, Native = UInt64, Edit = Integer)
ESD_TYPE(float, Native = Float, Edit = Real)
ESD_TYPE(double, Native = Double, Edit = Real)
ESD_TYPE(_Bool, Native = Bool, Edit = Boolean)
ESD_TYPE(char *, Native = Latin1, Edit = String)
ESD_TYPE(const char *, Native = Latin1, Edit = String)
ESD_TYPE(void *, Native = Pointer, Edit = None)

ESD_TYPE(int8_t, Native = Int8, Edit = Integer)
ESD_TYPE(uint8_t, Native = UInt8, Edit = Integer)
ESD_TYPE(int16_t, Native = Int16, Edit = Integer)
ESD_TYPE(uint16_t, Native = UInt16, Edit = Integer)
ESD_TYPE(int32_t, Native = Int32, Edit = Integer)
ESD_TYPE(uint32_t, Native = UInt32, Edit = Integer)
ESD_TYPE(int64_t, Native = Int64, Edit = Integer)
ESD_TYPE(uint64_t, Native = UInt64, Edit = Integer)
// ESD_TYPE(ssize_t, Native = IntPtr, Edit = Integer)
ESD_TYPE(size_t, Native = UIntPtr, Edit = Integer)

ESD_TYPE(ft_char8_t, Native = Char, Edit = String)
ESD_TYPE(ft_schar8_t, Native = Char, Edit = Integer)
ESD_TYPE(ft_uchar8_t, Native = Char, Edit = Integer)
ESD_TYPE(ft_uint8_t, Native = UInt8, Edit = Integer)
ESD_TYPE(ft_int16_t, Native = Int16, Edit = Integer)
ESD_TYPE(ft_uint16_t, Native = UInt16, Edit = Integer)
ESD_TYPE(ft_uint32_t, Native = UInt32, Edit = Integer)
ESD_TYPE(ft_int32_t, Native = Int32, Edit = Integer)
ESD_TYPE(ft_void_t, Native = Void)
ESD_TYPE(ft_int64_t, Native = Int64, Edit = Integer)
ESD_TYPE(ft_uint64_t, Native = UInt64, Edit = Integer)
ESD_TYPE(ft_float_t, Native = Float, Edit = Integer)
ESD_TYPE(ft_double_t, Native = Double, Edit = Real)
ESD_TYPE(ft_bool_t, Native = Int8, Edit = Boolean)
ESD_TYPE(ft_char8_t *, Native = Latin1, Edit = String)
ESD_TYPE(const ft_char8_t *, Native = Latin1, Edit = String)

typedef ft_int32_t ft_int32_f16_t;
ESD_TYPE(ft_int32_f16_t, Native = Int32, Edit = Fixed16)

typedef ft_int32_t ft_int32_f8_t;
ESD_TYPE(ft_int32_f8_t, Native = Int16, Edit = Fixed8)

typedef ft_int32_t ft_int32_f4_t;
ESD_TYPE(ft_int32_f4_t, Native = Int16, Edit = Fixed4)

typedef ft_int32_t ft_int32_f3_t;
ESD_TYPE(ft_int32_f3_t, Native = Int16, Edit = Fixed3)

typedef ft_int32_t ft_int32_f2_t;
ESD_TYPE(ft_int32_f2_t, Native = Int16, Edit = Fixed2)

typedef ft_int16_t ft_int16_f8_t;
ESD_TYPE(ft_int16_f8_t, Native = Int16, Edit = Fixed8)

typedef ft_int16_t ft_int16_f4_t;
ESD_TYPE(ft_int16_f4_t, Native = Int16, Edit = Fixed4)

typedef ft_int16_t ft_int16_f2_t;
ESD_TYPE(ft_int16_f2_t, Native = Int16, Edit = Fixed2)

typedef ft_uint32_t ft_argb32_t;
ESD_TYPE(ft_argb32_t, Native = UInt32, Edit = ColorARGB)

typedef ft_uint32_t ft_rgb32_t;
ESD_TYPE(ft_rgb32_t, Native = UInt32, Edit = ColorRGB)

ESD_FUNCTION(Ft_Esd_Noop, Category = _GroupHidden)
ESD_PARAMETER(context, Type = void *)
void Ft_Esd_Noop(void *context);

// TODO: This probably belongs in widgets framework, Ft_Esd.h is for core framework functionality only ->
ESD_ENUM(Ft_AlignX_Opt, Type = ft_uint16_t)
#define OPT_ALIGN_LEFT             0UL
#define OPT_ALIGN_CENTER           1UL
#define OPT_ALIGN_RIGHT            2UL
ESD_END()
ESD_ENUM(Ft_AlignY_Opt, Type = ft_uint16_t)
#define OPT_ALIGN_TOP              0UL
#define OPT_ALIGN_CENTER           1UL
#define OPT_ALIGN_BOTTOM           2UL
ESD_END()
// <-

#ifdef ESD_SIMULATION
void LogMessage__ESD(const char *str);
void LogWarning__ESD(const char *str);
void LogError__ESD(const char *str);
#define Ft_Esd_LogMessage(s) LogMessage__ESD(s)
#define Ft_Esd_LogWarning(s) LogWarning__ESD(s)
#define Ft_Esd_LogError(s) LogError__ESD(s)
#else
#define Ft_Esd_LogMessage(s) do { } while (0)
#define Ft_Esd_LogWarning(s) do { } while (0)
#define Ft_Esd_LogError(s) do { } while (0)
#endif

#ifdef _MSC_VER
#define inline __inline
#endif

#endif /* #ifndef FT_ESD_H */

/* end of file */
