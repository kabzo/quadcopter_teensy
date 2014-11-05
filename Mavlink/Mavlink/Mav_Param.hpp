#ifndef COPTER_PARAMETERS_HPP_
#define COPTER_PARAMETERS_HPP_

#include <common/mavlink.h>

enum var_type {
	PARAM_NONE = 0,
	PARAM_INT8 = 2,
	PARAM_INT16 = 4,
	PARAM_UINT32 = 5,
	PARAM_INT32 = 6,
	PARAM_FLOAT = 8

};

class Mav_Param {
	public:
		Mav_Param() {
		}

		struct Info {
				const var_type vtype;
				char _name[MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN];
				unsigned int id;
				void *ptr;
		};

		void set_value_ptr(enum var_type type, void *ptr, float value);
		float cast_to_float_mav(enum var_type type);
		void set_value(float value, enum var_type * type);

		static Mav_Param* find_by_name(const char * name, enum var_type * type);
		static float find_by_name_value(const char * name);
		static void set_value_by_name(const char * name, float val);
		static Mav_Param* get_param_id(uint8_t id);
		static Mav_Param* get_param_id(uint8_t id, enum var_type *type);
		static float get_param_id_value(uint8_t id, enum var_type *type);
	  static const char * get_param_name_id(uint8_t id);
	  static uint8_t get_param_id_name(const char* name);
	  static uint8_t cout_vars();

//private:
		static const struct Info _var_info[];
		static uint8_t _num_vars;

};

template<typename NumericT, var_type Type>
class Mav_ParamT: public Mav_Param {
	public:
		Mav_ParamT()
				: vtype(Type), _value(0) {
		}

		Mav_ParamT(NumericT value)
				: vtype(Type), _value(value) {
		}

		void set(const NumericT &v) {
			_value = v;
		}
		template<typename T>
		Mav_ParamT<NumericT, Type>& operator=(T val) {
			_value = val;
			return *this;
		}
		operator const NumericT &() const {
			return _value;
		}
		Mav_ParamT<NumericT, Type>& operator=(const NumericT &v) {
			_value = v;
			return *this;
		}
		Mav_ParamT<NumericT, Type>& operator |=(const NumericT &v) {
			_value |= v;
			return *this;
		}
		Mav_ParamT<NumericT, Type>& operator &=(const NumericT &v) {
			_value &= v;
			return *this;
		}
		Mav_ParamT<NumericT, Type>& operator +=(const NumericT &v) {
			_value += v;
			return *this;
		}
		Mav_ParamT<NumericT, Type>& operator /=(const NumericT &v) {
			_value /= v;
			return *this;
		}
		Mav_ParamT<NumericT, Type>& operator -=(const NumericT &v) {
			_value -= v;
			return *this;
		}
		template<typename T>
		bool operator !=(T &v) {
			if (_value != v)
				return true;
			return false;
		}
		template<typename T>
		bool operator ==(T &v) {
			if (_value == v)
				return true;
			return false;
		}
		float cast_to_float(void) const {
			return (float) _value;
		}

		const var_type vtype;
		NumericT _value;

};

#define PARAMDEF(_t, _suffix, _pt)   typedef Mav_ParamT<_t, _pt> Mav_ ## _suffix;
PARAMDEF(float, Float, PARAM_FLOAT);    // defines mav_Float
PARAMDEF(int8_t, Int8, PARAM_INT8);     // defines mav_Int8
PARAMDEF(int16_t, Int16, PARAM_INT16);  // defines mav_Int16
PARAMDEF(int32_t, Uint32, PARAM_UINT32);  // defines mav_Int32
PARAMDEF(int32_t, Int32, PARAM_INT32);  // defines mav_Int32

Mav_Param* Mav_Param::find_by_name(const char * name, enum var_type * type) {
	for (uint8_t i = 0; i < _num_vars; i++) {
		if (!strcmp(name, _var_info[i]._name)) {
			*type = _var_info[i].vtype;
			return (Mav_Param *) (_var_info[i].ptr);
		}
	}
	return NULL;
}

void Mav_Param::set_value_ptr(enum var_type type, void *ptr, float value) {
	switch (type) {
		case PARAM_INT8:
			((Mav_Int8 *) (ptr))->set(value);
			break;
		case PARAM_INT16:
			((Mav_Int16 *) ptr)->set(value);
			break;
		case PARAM_INT32:
			((Mav_Int32 *) ptr)->set(value);
			break;
		case PARAM_FLOAT:
			((Mav_Float *) ptr)->set(value);
			break;
		default:
			break;
	}
}

float Mav_Param::cast_to_float_mav(enum var_type vtype) {
	switch (vtype) {
		case PARAM_INT8:
			return ((Mav_Int8 *) this)->cast_to_float();
		case PARAM_INT16:
			return ((Mav_Int16 *) this)->cast_to_float();
		case PARAM_INT32:
			return ((Mav_Int32 *) this)->cast_to_float();
		case PARAM_FLOAT:
			return ((Mav_Float *) this)->cast_to_float();
		default:
			return NAN;
	}
}

float Mav_Param::find_by_name_value(const char * name) {
	var_type type;
	Mav_Param *param = find_by_name(name, &type);
	return param->cast_to_float_mav(type);
}

void Mav_Param::set_value_by_name(const char * name, float val) {
	var_type vtype;
	Mav_Param *param = find_by_name(name, &vtype);
	switch (vtype) {
		case PARAM_INT8:
			((Mav_Int8 *) param)->set(val);
			break;
		case PARAM_INT16:
			((Mav_Int16 *) param)->set(val);
			break;
		case PARAM_INT32:
			((Mav_Int32 *) param)->set(val);
			break;
		case PARAM_FLOAT:
			((Mav_Float *) param)->set(val);
			break;
		default:
			return;
	}

}

void Mav_Param::set_value(float val,enum var_type * vtype){
	switch (*vtype) {
			case PARAM_INT8:
				((Mav_Int8 *) this)->set(val);
				break;
			case PARAM_INT16:
				((Mav_Int16 *) this)->set(val);
				break;
			case PARAM_INT32:
				((Mav_Int32 *) this)->set(val);
				break;
			case PARAM_FLOAT:
				((Mav_Float *) this)->set(val);
				break;
			default:
				return;
		}
}


Mav_Param * Mav_Param::get_param_id(uint8_t id) {
	return (Mav_Param *) (_var_info[id].ptr);
}
Mav_Param* Mav_Param::get_param_id(uint8_t id, enum var_type *type) {
	*type = _var_info[id].vtype;
	return (Mav_Param *) (_var_info[id].ptr);
}
float Mav_Param::get_param_id_value(uint8_t id, enum var_type *type) {
	Mav_Param *param = get_param_id(id, type);
	return param->cast_to_float_mav(*type);
}
const char * Mav_Param::get_param_name_id(uint8_t id){
		return _var_info[id]._name;
}
 uint8_t Mav_Param::cout_vars(){
	 enum var_type vtype;
	 Mav_Param * param;
	 do{
		 param = get_param_id(_num_vars,&vtype);
		 _num_vars++;
	 }while(param != NULL && vtype != PARAM_NONE);
	 _num_vars--;
	 return _num_vars;
 }
 uint8_t Mav_Param::get_param_id_name(const char* name){
	 for (uint8_t i = 0; i < _num_vars; i++) {
	 		if (!strcmp(name, _var_info[i]._name)) {

	 			return i++;
	 		}
	 	}
	 	return 0;
 }

#endif /* COPTER_PARAMETERS_HPP_ */
