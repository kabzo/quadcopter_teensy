#ifndef COPTER_PARAMETERS_HPP_
#define COPTER_PARAMETERS_HPP_

#include <Arduino.h>
#include <mavlinkCommon/common/mavlink.h>
#include <Typedef.hpp>

enum var_type
{
		PARAM_NONE = 0,
		PARAM_INT8 = 2,
		PARAM_INT16 = 4,
		PARAM_UINT32 = 5,
		PARAM_INT32 = 6,
		PARAM_FLOAT = 9,
		PARAM_GROUP

};

// a variant of offsetof() to work around C++ restrictions.
// this can only be used when the offset of a variable in a object
// is constant and known at compile time
#define VAROFFSET(type, element) (((uintptr_t)(&((const type *)1)->element))-1)

// find the type of a variable given the class and element
#define CLASSTYPE(class, element) (((const class *) 1)->element.vtype)

// declare a group var_info line
#define GROUPINFO(name,  class, element, def) { CLASSTYPE(class, element),  name, VAROFFSET(class, element), {def_value : def} }
#define GROUPEND     { PARAM_NONE,  "", 0, { group_info : NULL } }
#define VAREND       { PARAM_NONE, "", NULL, { group_info : NULL } }

//macro for init
#define GSCALAR(v, name, def) { (uint8_t)con.v.vtype, name,  &con.v, {def_value : def} }
#define GGROUP(v, name, class) { PARAM_GROUP, name,  &con.v, {group_info : class::var_info} }

class Mav_Param
{
public:
	Mav_Param()
	{
	}

	struct GroupInfo
	{
		uint8_t vtype; // AP_PARAM_*
		const char name[MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN + 1];
		uintptr_t offset; // offset within the object
		union
		{
			const struct GroupInfo *group_info;
			const float def_value;
		};
	};

	struct Info
	{
		uint8_t vtype; // AP_PARAM_*
		const char name[MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN + 1];
		void *ptr;    // pointer to the variable in memory
		union
		{
			const struct GroupInfo *group_info;
			const float def_value;
		};
	};

	Mav_Param(const struct Info *info)
	{
		_var_info = info;

		uint16_t i;
		for (i = 0; pgm_read_one_byte(&info[i].vtype) != PARAM_NONE; i++)
		{
			if (pgm_read_one_byte(&info[i].vtype) == PARAM_GROUP)
			{
				const struct GroupInfo *ginfo = (const struct GroupInfo *) PGM_POINTER(&info[i].group_info);
				uint16_t a;
				for (a = 0; pgm_read_one_byte(&ginfo[a].vtype) != PARAM_NONE; a++)
					;

				_num_vars_all += a;

			} else
				_num_vars_all++;
			_num_vars++;
		}
		setup_sketch_defaults();

	}

	static void set_value_ptr(enum var_type type, void *ptr, float value);

	float cast_to_float_mav(enum var_type type);
	void set_value(float value, enum var_type & type);

	static Mav_Param* get_param_by_name(const char * name, enum var_type & type);
	static float get_value_by_name(const char * name);
	static void set_value_by_name(const char * name, float val);
	static Mav_Param* get_param_by_id(uint8_t id);
	static Mav_Param* get_param_type_by_id(uint8_t id, enum var_type &type);
	static float get_value_by_id(uint8_t id, enum var_type &type);
	static void get_name_by_id(uint8_t id, char *name);
	static float get_value_id_by_name(uint8_t &id, enum var_type &type, const char *name);
	static float get_value_name_by_id(enum var_type &type, char *name, uint8_t id);
	static uint8_t get_id_by_name(const char * name);

	static void setup_object_defaults(const void *object_pointer, const struct GroupInfo *group_info);

	static const struct Info * _var_info;
	static uint8_t _num_vars;
	static uint8_t _num_vars_all;

	static void setup_sketch_defaults();

};

template<typename NumericT, var_type Type>
class Mav_ParamT: public Mav_Param
{
public:
	Mav_ParamT() :
			_value(0), _changed(false)
	{
	}

	Mav_ParamT(NumericT value) :
			_value(value), _changed(false)

	{
	}

	void set(const NumericT &v)
	{
		_value = v;
	}

	void set_changed(bool change){
		_changed = change;
	}

	template<typename T>
	Mav_ParamT<NumericT, Type>& operator=(T val)
	{
		_value = val;
		return *this;
	}
	operator const NumericT &() const
	{
		return _value;
	}
	Mav_ParamT<NumericT, Type>& operator=(const NumericT &v)
	{
		_value = v;
		return *this;
	}

	Mav_ParamT<NumericT, Type>& operator |=(const NumericT &v)
	{
		_value |= v;
		return *this;
	}
	Mav_ParamT<NumericT, Type>& operator &=(const NumericT &v)
	{
		_value &= v;
		return *this;
	}
	Mav_ParamT<NumericT, Type>& operator +=(const NumericT &v)
	{
		_value += v;
		return *this;
	}
	Mav_ParamT<NumericT, Type>& operator /=(const NumericT &v)
	{
		_value /= v;
		return *this;
	}
	Mav_ParamT<NumericT, Type>& operator -=(const NumericT &v)
	{
		_value -= v;
		return *this;
	}
	template<typename T>
	bool operator !=(T &v)
	{
		if (_value != v)
			return true;
		return false;
	}
	template<typename T>
	bool operator ==(T &v)
	{
		if (_value == v)
			return true;
		return false;
	}
	float cast_to_float(void) const
	{
		return (float) _value;
	}

	static const var_type vtype = Type;
	NumericT _value;
	bool _changed;

};

#define PARAMDEF(_t, _suffix, _pt)   typedef Mav_ParamT<_t, _pt> Mav_ ## _suffix;
PARAMDEF(float, Float, PARAM_FLOAT);    // defines mav_Float
PARAMDEF(int8_t, Int8, PARAM_INT8);     // defines mav_Int8
PARAMDEF(int16_t, Int16, PARAM_INT16);  // defines mav_Int16
PARAMDEF(int32_t, Uint32, PARAM_UINT32);  // defines mav_Int32
PARAMDEF(int32_t, Int32, PARAM_INT32);  // defines mav_Int32

#endif /* COPTER_PARAMETERS_HPP_ */
