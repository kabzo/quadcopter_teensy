/*
 * Mav_Param.cpp
 *
 *  Created on: 17.12.2014
 *      Author: Juraj
 */

#include <Mav_Param.hpp>


const Mav_Param::Info * Mav_Param::_var_info;
uint8_t Mav_Param::_num_vars = 0;
uint8_t Mav_Param::_num_vars_all = 0;

void Mav_Param::setup_object_defaults(const void *object_pointer,
																			const struct GroupInfo *group_info) {
	uintptr_t base = (uintptr_t) object_pointer;
	uint8_t type;
	for (uint8_t i = 0; (type = PGM_UINT8(&group_info[i].vtype)) != PARAM_NONE;
			i++) {
		if (type <= PARAM_FLOAT) {
			void *ptr = (void *) (base + PGM_UINT16(&group_info[i].offset));
			set_value_ptr((enum var_type) type, ptr,
					PGM_FLOAT(&group_info[i].def_value));
		}
	}
}

void Mav_Param::setup_sketch_defaults() {
	for (uint8_t i = 0; i < _num_vars; i++) {
		uint8_t type = PGM_UINT8(&_var_info[i].vtype);
		if (type <= PARAM_FLOAT) {
			void *ptr = (void*) PGM_POINTER(&_var_info[i].ptr);
			set_value_ptr((enum var_type) type, ptr,
					PGM_FLOAT(&_var_info[i].def_value));
		}
	}
}

Mav_Param* Mav_Param::get_param_by_name(const char * name, enum var_type & type) {
	for (uint16_t i = 0; pgm_read_one_byte(&_var_info[i].vtype) != PARAM_NONE; i++) {
		if (_var_info[i].vtype == PARAM_GROUP) {
			const struct GroupInfo *group_info =
					(const struct GroupInfo *) PGM_POINTER(&_var_info[i].group_info);

			for (int a = 0; pgm_read_one_byte(&group_info[a].vtype) != PARAM_NONE; a++) {
				String nameStr = "";
				nameStr += _var_info[i].name;
				nameStr += group_info[a].name;
				if (!strcmp(nameStr.c_str(), name)) {
					type = (enum var_type) PGM_UINT8(&group_info[a].vtype);
					return (Mav_Param*) (PGM_POINTER(&_var_info[i].ptr)
							+ PGM_UINT16(&group_info[a].offset));
				}
			}

		}

		if (!strcmp(_var_info[i].name, name)) {
			type = (enum var_type) PGM_UINT8(&_var_info[i].vtype);
			return (Mav_Param *) (PGM_POINTER(&_var_info[i].ptr));
		}

	}
	return 0;
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

float Mav_Param::get_value_by_name(const char * name) {
	var_type type;
	Mav_Param *param = get_param_by_name(name, type);
	return param->cast_to_float_mav(type);
}

void Mav_Param::set_value_by_name(const char * name, float val) {
	var_type vtype;
	Mav_Param *param = get_param_by_name(name, vtype);
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

void Mav_Param::set_value(float val, enum var_type & vtype) {
	switch (vtype) {
		case PARAM_INT8:{
			((Mav_Int8 *) this)->set(val);
			((Mav_Int8 *) this)->set_changed(true);
			break;
		}
		case PARAM_INT16:{
			((Mav_Int16 *) this)->set(val);
			((Mav_Int16 *) this)->set_changed(true);
			break;
		}
		case PARAM_INT32:{
			((Mav_Int32 *) this)->set(val);
			((Mav_Int32 *) this)->set_changed(true);
			break;
		}
		case PARAM_FLOAT:{
			((Mav_Float *) this)->set(val);
			((Mav_Float *) this)->set_changed(true);
			break;
		}
		default:
			return;
	}
}

Mav_Param * Mav_Param::get_param_by_id(uint8_t id) {
	var_type type;
	return get_param_type_by_id(id, type);
}

Mav_Param* Mav_Param::get_param_type_by_id(uint8_t id, enum var_type &type) {
	for (uint16_t i = 0; pgm_read_one_byte(&_var_info[i].vtype) != PARAM_NONE; i++) {
		if (_var_info[i].vtype == PARAM_GROUP) {
			const struct GroupInfo *group_info =
					(const struct GroupInfo *) PGM_POINTER(&_var_info[i].group_info);
			for (int a = 0; pgm_read_one_byte(&group_info[a].vtype) != PARAM_NONE; a++) {
				if (a + i == id) {
					type = (enum var_type) PGM_UINT8(&group_info[a].vtype);
					return (Mav_Param*) (PGM_POINTER(&_var_info[i].ptr)
							+ PGM_UINT16(&group_info[a].offset));
				}
			}
		}
		if (i == id) {
			type = (enum var_type) PGM_UINT8(&_var_info[i].vtype);
			return (Mav_Param *) (PGM_POINTER(&_var_info[i].ptr));
		}
	}
	return 0;
}

float Mav_Param::get_value_by_id(uint8_t id, enum var_type &type) {
	Mav_Param *param = get_param_type_by_id(id, type);
	return param->cast_to_float_mav(type);
}

float Mav_Param::get_value_id_by_name(	uint8_t &id,
																					enum var_type &type,
																					const char *name) {
	uint8_t count = 0;
	for (uint16_t i = 0; pgm_read_one_byte(&_var_info[i].vtype) != PARAM_NONE; i++) {

		if (_var_info[i].vtype == PARAM_GROUP) {
			const struct GroupInfo *group_info =
					(const struct GroupInfo *) PGM_POINTER(&_var_info[i].group_info);
			for (int a = 0; pgm_read_one_byte(&group_info[a].vtype) != PARAM_NONE; a++) {
				String nameStr = "";
				nameStr += _var_info[i].name;
				nameStr += group_info[a].name;
				if (!strcmp(nameStr.c_str(), name)) {
					id = count;
					type = (enum var_type) PGM_UINT8(&group_info[a].vtype);
					Mav_Param *ptr = (Mav_Param*) (PGM_POINTER(&_var_info[i].ptr)
							+ PGM_UINT16(&group_info[a].offset));
					return ptr->cast_to_float_mav(type);
				}
				count++;
			}

		}

		if (!strcmp(_var_info[i].name, name)) {
			id = i;
			type = (enum var_type) PGM_UINT8(&_var_info[i].vtype);
			Mav_Param *ptr = (Mav_Param *) (PGM_POINTER(&_var_info[i].ptr));
			return ptr->cast_to_float_mav(type);
		}

	}
	return 0;
}

float Mav_Param::get_value_name_by_id(	enum var_type &type,
																					char *name,
																					uint8_t id) {
	uint8_t sum = 0;
	for (uint16_t i = 0; pgm_read_one_byte(&_var_info[i].vtype) != PARAM_NONE; i++) {

		if (_var_info[i].vtype == PARAM_GROUP) {
			const struct GroupInfo *group_info =
					(const struct GroupInfo *) PGM_POINTER(&_var_info[i].group_info);
			for (int a = 0; pgm_read_one_byte(&group_info[a].vtype) != PARAM_NONE; a++) {
				if (sum == id) {
					strcpy(name, _var_info[i].name);
					strcat(name, group_info[a].name);
					type = (enum var_type) PGM_UINT8(&group_info[a].vtype);
					Mav_Param *ptr = (Mav_Param*) (PGM_POINTER(&_var_info[i].ptr)
							+ PGM_UINT16(&group_info[a].offset));
					return ptr->cast_to_float_mav(type);
				}
				sum++;
			}
		} else
			sum++;
		if (i == id) {
			strcpy(name, _var_info[i].name);
			type = (enum var_type) PGM_UINT8(&_var_info[i].vtype);
			Mav_Param *ptr = (Mav_Param *) (PGM_POINTER(&_var_info[i].ptr));
			return ptr->cast_to_float_mav(type);
		}
	}
	return 0;
}

void Mav_Param::get_name_by_id(uint8_t id, char *name) {
	uint8_t sum = 0;
	for (uint16_t i = 0; pgm_read_one_byte(&_var_info[i].vtype) != PARAM_NONE; i++) {
		if (_var_info[i].vtype == PARAM_GROUP) {
			const struct GroupInfo *group_info =
					(const struct GroupInfo *) PGM_POINTER(&_var_info[i].group_info);
			for (int a = 0; pgm_read_one_byte(&group_info[a].vtype) != PARAM_NONE; a++) {
				if (sum == id) {
					strcpy(name, _var_info[i].name);
					strcat(name, group_info[a].name);
					return;
				}
			}
		} else
			sum++;
		if (i == id) {
			strcpy(name, _var_info[i].name);
			return;
		}
	}

	return;
}

uint8_t Mav_Param::get_id_by_name(const char* name) {
	char tempName[MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN];
	for (uint8_t i = 0; i < _num_vars_all; i++) {
		get_name_by_id(i, tempName);
		if (!strcmp(name, tempName)) {
			return i;
		}
	}
	return 0;
}




