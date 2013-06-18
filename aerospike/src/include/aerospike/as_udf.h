/******************************************************************************
 *	Copyright 2008-2013 by Aerospike.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy 
 *	of this software and associated documentation files (the "Software"), to 
 *	deal in the Software without restriction, including without limitation the 
 *	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 *	sell copies of the Software, and to permit persons to whom the Software is 
 *	furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in 
 *	all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 *	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *	IN THE SOFTWARE.
 *****************************************************************************/

#pragma once 

#include <aerospike/as_bytes.h>
#include <aerospike/as_list.h>

/******************************************************************************
 *	MACROS
 *****************************************************************************/

/**
 *	The size of a UDF file name
 */
#define AS_UDF_FILE_NAME_SIZE 128

/**
 * The maxium string length of the UDF file name
 */
#define AS_UDF_FILE_NAME_LEN AS_UDF_FILE_NAME_SIZE - 1

/**
 *	The size of a UDF hash value
 */
#define AS_UDF_FILE_HASH_SIZE 20

/******************************************************************************
 *	TYPES
 *****************************************************************************/

/**
 *	Defines a call to a UDF
 */
typedef struct as_udf_call_s {

	/**
	 *	@private
	 *	If true, then as_udf_call_destroy() will free this instance.
	 */
	bool _free;

	/**
	 *	UDF Module containing the function to be called.
	 */
	char * module;

	/**
	 *	UDF Function to be called
	 */
	char * function;

	/**
	 *	Argument List
	 */
	as_list * arglist;
	
} as_udf_call;

/**
 *	Enumeration of UDF types
 */
typedef enum as_udf_type_e {

	/**
	 *	Lua
	 */
	AS_UDF_TYPE_LUA

} as_udf_type;

/**
 *	UDF File
 */
typedef struct as_udf_file_s {

	/**
	 *	@private
	 *	If true, then as_udf_file_destroy() will free this instance.
	 */
	bool _free;

	/**
	 *	Name of the UDF file
	 */
	char name[AS_UDF_FILE_NAME_SIZE];

	/** 
	 *	Hash value of the file contents
	 */
	uint8_t hash[AS_UDF_FILE_HASH_SIZE];

	/**
	 *	The type of UDF
	 */
	as_udf_type type;

	/**
	 *	UDF File contents
	 */
	struct {

		/**
	 	 *	@private
		 *	If true, then as_udf_file_destroy() will free bytes()
		 */
		bool _free;

		/**
		 *	Number of bytes allocated to bytes.
		 */
		uint32_t capacity;

		/**
		 *	Number of bytes used in bytes.
		 */
		uint32_t size;

		/**
		 *	Sequence of bytes
		 */
		uint8_t * bytes;

	} content;

} as_udf_file;

/**
 *	Sequence of UDF Files
 */
typedef struct as_udf_files_s {

	/**
	 *	@private
	 *	If true, then as_udf_list_destroy() will free this instance.
	 */
	bool _free;

	/**
	 *	Number of file entries allocated to files.
	 */
	uint32_t capacity;

	/**
	 *	Number of used file entries in files.
	 */
	uint32_t size;

	/**
	 *	Sequence of files.
	 */
	as_udf_file * entries;

} as_udf_files;

/******************************************************************************
 *	UDF CALL FUNCTIONS
 *****************************************************************************/

/**
 *	Initialize a stack allocated as_udf_call.
 *
 *	@param call 		The call to initialize.
 *	@param module 	The UDF module.
 *	@param function 	The UDF function.
 *	@param arglist 	The UDF argument list.
 *
 *	@return The initialized call on success. Otherwise NULL.
 */
as_udf_call * as_udf_call_init(as_udf_call * call, const char * module, const char * function, as_list * arglist);

/**
 *	Creates a new heap allocated as_udf_call.
 *	@param module 	The UDF module.
 *	@param function 	The UDF function.
 *	@param arglist 	The UDF argument list.
 *
 *	@return The newly allocated call on success. Otherwise NULL.
 */
as_udf_call * as_udf_call_new(const char * module, const char * function, as_list * arglist);

/**
 *	Destroy an as_udf_call.
 */
void as_udf_call_destroy(as_udf_call * call);

/******************************************************************************
 *	UDF FILE FUNCTIONS
 *****************************************************************************/

/**
 *	Initialize a stack allocated as_udf_file.
 *
 *	@returns The initialized udf file on success. Otherwise NULL.
 */
as_udf_file * as_udf_file_init(as_udf_file * file);

/**
 *	Creates a new heap allocated as_udf_file.
 *
 *	@returns The newly allocated udf file on success. Otherwise NULL.
 */
as_udf_file * as_udf_file_new();

/**
 *	Destroy an as_udf_file.
 */
void as_udf_file_destroy(as_udf_file * file);

/******************************************************************************
 *	UDF LIST FUNCTIONS
 *****************************************************************************/

/**
 *	Initialize a stack allocated as_udf_files.
 *
 *	@returns The initialized udf list on success. Otherwise NULL.
 */
as_udf_files * as_udf_files_init(as_udf_files * files, uint32_t capacity);

/**
 *	Creates a new heap allocated as_udf_files.
 *
 *	@returns The newly allocated udf list on success. Otherwise NULL.
 */
as_udf_files * as_udf_files_new(uint32_t capacity);

/**
 *	Destroy an as_udf_files.
 */
void as_udf_files_destroy(as_udf_files * files);

