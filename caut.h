#ifndef _CAUT_H_
#define _CAUT_H_

//refer to http://en.wikipedia.org/wiki/C_data_types
#define __CAUT_ADDR unsigned long int
#define __CAUT_INT_VALUE long long int
#define __CAUT_REAL_VALUE long double
#define __CAUT_FUNCTION_ID unsigned int

#define CAUT_INPUT(x) _cf__getInput((__CAUT_ADDR)&x)

/* symbolic input interface */
#define CAUT_SYMBOLIC_INPUT(var,var_size,var_name) __caut_symbolic_input((__CAUT_ADDR)&var,var_byte_size,var_name)
void __caut_symbolic_input(__CAUT_ADDR var_addr, int var_byte_size, char* var_name);
void __caut_symbolic_read(__CAUT_ADDR var_addr, int var_byte_size, char* var_name);

/* input var assigmment */
void _cf__getInput(__CAUT_ADDR addr);

void set_main_function_id(int id);

/* init caut */
void init_caut(int argc,char *argv[]);
/* init the coverage driven testing framework */
void init_coverage_driven_testing_framework();
/* init caut before each iteration */
void init_caut_exec();
/* solve each iteration */
void solve_caut_exec();


/*
   monitor the program execution and build the execution tree during the whole testing process
  	LINE: the original cfg branch node line number
  	BRANCH_ID: runtime branching node id
	BRANCH_CHOICE: runtime branching node choice
	FUNCTION_ID: function id
*/
void branch(int line,int branch_id, int branch_choice , int function_id);

/* cover function --> branch coverage */
void bc_cover_fun(int cfg_branch_id, int cfg_branch_choice , int function_id);

/* cover function for fitness guided path exploration */
void cover_condition_fun(int con_id,int predicate_value,int op_type);

/* a monitoring interface for data flow testing 
   function_id : the id of a function
   sid: a global sid for a statement in a function
*/
void df_stmt_monitor(int function_id, int stmt_id, int stmt_line);

/*	
   create "use-item" for arguments in the function call(fetch from the "def-item" list),
   called before the function call.
   	ADDR: argument address
	TYPE: argument type
*/
void argu_push(__CAUT_ADDR addr, int type);
/* 
   record the argument number of the called function
   called before the actual function call.
	PARA_NUM: argument number
*/
void para_num_stack_push(int para_num);
/* clear the stack when encountering un-instrumented functions */
void para_num_stack_pop();
/*
   put the function argument into "def-item" list
   called after entering the called function
*/
void para_pop(__CAUT_ADDR addr);
void symbolic_execution_push(int);
void symbolic_execution_pop();

/*
   maintain the mapping between symbolic value and concrete value 
   [GCC Waring] cast from pointer to integer of different size
*/
void load_to_heap_int(__CAUT_ADDR addr, __CAUT_INT_VALUE value, int type);
void load_to_heap_float(__CAUT_ADDR addr , __CAUT_REAL_VALUE value , int type);

/*	
    apply operation
    OP_TYPE  1:OP_BOOLEAN 2:OP_ARITHMETIC
      defined in symbolic.h
*/
void apply_op(unsigned long op_type, unsigned long op);
void store_to_var_table(__CAUT_ADDR addr);
void store_concrete_value_int(__CAUT_INT_VALUE value);
void store_concrete_value_float(__CAUT_REAL_VALUE value);

/* handle the concrete return value from an uninterpreted(uninstrumented) function 
   store this return value as a new use-item
*/
void handle_uninterpreted_function_return_int(__CAUT_INT_VALUE value, int type);
void handle_uninterpreted_function_return_float(__CAUT_REAL_VALUE value, int type);
/*
   store the concrete return value from an uninterpreted(uninstrumented) function 
   create a new def-item corresponding to the new use-item
*/
void store_uninterpreted_function_return(__CAUT_ADDR addr);


/* get the id of input var */
int get_input_id();
void reset_input_id();
void test_case_record_add(unsigned long, int, int);

/* initialize input var according its meomory layout 
   Derived type vars are decoupled into Scalar type vars.
*/
/* handling input var with scalar type */
void get_test_case_int(__CAUT_ADDR addr);
void get_test_case_long(__CAUT_ADDR addr);
void get_test_case_double(__CAUT_ADDR addr);
void get_test_case_char(__CAUT_ADDR addr);
void get_test_case_short(__CAUT_ADDR addr);
void get_test_case_void(__CAUT_ADDR addr);

/* handling input var with derived type : array, pointer and struct */
__CAUT_ADDR abstract_ptr_handle(__CAUT_ADDR addr, int size);
void array_declaration(__CAUT_ADDR addr, int n, int type, unsigned int type_size);

/* primitive type */
enum __CAUT_primitivetype_t
{
	__CAUT__void = 0,
	__CAUT__char = 1,
	__CAUT__signed_char = 2,
	__CAUT__short = 3,
	__CAUT__int = 4,
	__CAUT__long = 5,
	__CAUT__long_long = 6,
	__CAUT__unsigned_char = 7,
	__CAUT__unsigned_short = 8,
	__CAUT__unsigned_int = 9,
	__CAUT__unsigned_long = 10,
	__CAUT__unsigned_long_long = 11,
	__CAUT__float = 12,
	__CAUT__double = 13,
	__CAUT__long_double = 14
};

/* type system registrateion interfaces */
typedef struct __CAUT_datatype_t *__CAUT_ctype_t;

__CAUT_ctype_t __CAUT_create_primitive_type(const char *name, int namelen, int typesize, enum __CAUT_primitivetype_t type);
__CAUT_ctype_t __CAUT_create_pointer_type(const char *name, int namelen, int subtype);
__CAUT_ctype_t __CAUT_create_comp_type_struct(const char *name, int namelen, int typesize, int membercnt);
__CAUT_ctype_t __CAUT_create_comp_type_union(const char *name, int namelen, int typesize, int membercnt);
__CAUT_ctype_t __CAUT_create_comp_member(__CAUT_ctype_t comptype, const char *name, int namelen, int membertype, int bitlen, int seq);
__CAUT_ctype_t __CAUT_create_array_type(const char *name, int namelen, int membertype, int dimension, const int *dimlens);
__CAUT_ctype_t __CAUT_create_enum_type(const char *name, int namelen, int membercnt, const int *members);
__CAUT_ctype_t __CAUT_create_func_type(const char *name, int namelen, int paramcnt, const int *paramtypes, int returntype);
int __CAUT_register_datatype(int id, __CAUT_ctype_t datatype);
void __CAUT_free_datatype(__CAUT_ctype_t datatype);

/* Libo : print test case */
void store_input_var(const char* var_name, __CAUT_ADDR var_addr, const char* type_name);
void print_testcase();


/*******************************************************************/

#define CAUT_DF_CALL 1
#define CAUT_DF_ENTRY 2
#define CAUT_DF_EXIT 3
#define CAUT_DF_RETURN 4

/* utilities functions for data flow testing */
/* mark var defs and uses 
	var_name: the name of a var (defs or uses)
	index: the index
	def_or_use: is var def or var use ?
	use_index: the var use index, it has no meaning for var def
	
	**** INDEX starts from 1 (inclusive) ****
  Limitation:
	You can write only one def_use mark function.
  Usage:
	mark a var def just behind the definition instruction.
	mark a var use just before the use instruction.
*/


//void CAUT_DEF_USE(char* var_name, int dua_index, int def_or_use, int use_index){return;}


/* 
	mark dua's interprocedural data flow direction (mark a realizable path)
	 dua_index: corresponds to the "dua_index" in "def_use"
	 dua_use_index: corresponds to the "use_index" in "def_use"
	 interp_point_type: CALL, ENTRY, EXIT and RETURN
	 interp_point_index: the index for interp. point

	 **** POINT_TYPE starts from 1 (inclusive) ****
*/

//void CAUT_DF_CONTEXT(int dua_index, int interp_point_type, int interp_point_index, int dua_use_index){return;}

/*******************************************************************/


#endif
