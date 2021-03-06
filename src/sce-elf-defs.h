/*
This file is part of DolceSDK
Copyright (C) 2020 Asakura Reiko

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Copyright (C) 2015, 2016 xyzz
Copyright (C) 2016 173210
Copyright (C) 2016 Yifan Lu
Copyright (C) 2018 VelocityRa
See LICENSE/vitasdk
*/

/* This file gets included multiple times to generate the host-visible and target-visible versions of each struct */

#if defined(SCE_ELF_DEFS_HOST)
# define SCE_TYPE(type) type ## _t
# define SCE_PTR(type) type
#elif defined(SCE_ELF_DEFS_TARGET)
# define SCE_TYPE(type) type ## _raw
# define SCE_PTR(type) uint32_t
#else
# error "Do not include sce-elf-defs.h directly!  Include sce-elf.h!"
#endif

#include <stdint.h>

#define SCE_PSP2_SDK_VERSION 0x03570011

struct SCE_TYPE(sce_module_exports);
struct SCE_TYPE(sce_module_imports);

typedef struct SCE_TYPE(sce_module_info) {
	uint16_t attributes;
	uint16_t version;			/* Set to 0x0101 */
	char name[27];				/* Name of the library */
	uint8_t type;				/* 0x0 for executable, 0x6 for PRX */
	SCE_PTR(const void *) gp_value;
	SCE_PTR(struct sce_module_exports_t *)
		export_top;			/* Offset to start of export table */
	SCE_PTR(struct sce_module_exports_t *)
		export_end;			/* Offset to end of export table */
	SCE_PTR(struct sce_module_imports_t *)
		import_top;			/* Offset to start of import table */
	SCE_PTR(struct sce_module_imports_t *)
		import_end;			/* Offset to end of import table */
	uint32_t library_nid;			/* NID of this library */
	uint32_t field_38;
	uint32_t field_3C;
	uint32_t field_40;
	SCE_PTR(const void *) module_start;	/* Offset to function to run when library is started, 0 to disable */
	SCE_PTR(const void *) module_stop;	/* Offset to function to run when library is exiting, 0 to disable */
	SCE_PTR(const void *) exidx_top;	/* Offset to start of ARM EXIDX (optional) */
	SCE_PTR(const void *) exidx_end;	/* Offset to end of ARM EXIDX (optional) */
	SCE_PTR(const void *) extab_top;	/* Offset to start of ARM EXTAB (optional) */
	SCE_PTR(const void *) extab_end;	/* Offset to end of ARM EXTAB (optional */

	// TODO: separate into another struct
	uint32_t              process_param_size;                      /* 0x34 */
	uint32_t              process_param_magic;                     /* "PSP2" */
	uint32_t              process_param_unk_8;                     /* 6 */
	uint32_t              process_param_sdk_version;
	SCE_PTR(const char *) process_param_main_thread_name;
	SCE_PTR(uint32_t *)   process_param_main_thread_priority;
	SCE_PTR(uint32_t *)   process_param_main_thread_stack_size;
	uint32_t              process_param_unk_1c;
	SCE_PTR(const char *) process_param_process_name;
	SCE_PTR(uint32_t *)   process_param_unk_24;
	uint32_t              process_param_unk_28;
	SCE_PTR(const void *) process_param_libc_param;
	uint32_t              process_param_unk_30;

	// TODO: separate into another struct
	uint32_t              libc_param_size;                      /* 0x38 */
	uint32_t              libc_param_unk_4;
	SCE_PTR(uint32_t *)   libc_param_heap_size;
	SCE_PTR(uint32_t *)   libc_param_heap_size_default;
	uint32_t              libc_param_unk_10;
	uint32_t              libc_param_unk_14;
	uint32_t              libc_param_sdk_version;
	uint32_t              libc_param_unk_1c;                    /* 9 */
	SCE_PTR(const void *) libc_param_malloc_replace;
	SCE_PTR(const void *) libc_param_new_replace;
	uint32_t              libc_param_unk_28;
	uint32_t              libc_param_unk_2c;
	uint32_t              libc_param_unk_30;
	SCE_PTR(const void *) libc_param_malloc_replace_for_tls;

	uint32_t              _libc_param_heap_size;
	uint32_t              _libc_param_heap_size_default;        /* 0x40000 */

} SCE_TYPE(sce_module_info);

typedef struct SCE_TYPE(sce_module_exports) {
	uint16_t size;				/* Size of this struct, set to 0x20 */
	uint16_t version;			/* 0x1 for normal export, 0x0 for main module export */
	uint16_t flags;				/* 0x1 for normal export, 0x8000 for main module export */
	uint16_t num_syms_funcs;		/* Number of function exports */
	uint32_t num_syms_vars;			/* Number of variable exports */
	uint32_t num_syms_unk;
	uint32_t module_nid;			/* NID of this module */
	SCE_PTR(const char *) module_name;	/* Pointer to name of this module */
	SCE_PTR(uint32_t *) nid_table;		/* Pointer to array of 32-bit NIDs to export */
	SCE_PTR(const void **) entry_table;	/* Pointer to array of data pointers for each NID */
} SCE_TYPE(sce_module_exports);

typedef struct SCE_TYPE(sce_module_imports) {
	uint16_t size;				/* Size of this struct, set to 0x34 */
	uint16_t version;			/* Set to 0x1 */
	uint16_t flags;				/* Set to 0x0 */
	uint16_t num_syms_funcs;		/* Number of function imports */
	uint16_t num_syms_vars;			/* Number of variable imports */
	uint16_t num_syms_unk;

	uint32_t reserved1;
	uint32_t module_nid;			/* NID of module to import */
	SCE_PTR(const char *) module_name;	/* Pointer to name of imported module, for debugging */
	uint32_t reserved2;
	SCE_PTR(uint32_t *) func_nid_table;	/* Pointer to array of function NIDs to import */
	SCE_PTR(const void **) func_entry_table;/* Pointer to array of stub functions to fill */
	SCE_PTR(uint32_t *) var_nid_table;	/* Pointer to array of variable NIDs to import */
	SCE_PTR(const void **) var_entry_table;	/* Pointer to array of data pointers to write to */
	SCE_PTR(uint32_t *) unk_nid_table;
	SCE_PTR(const void **) unk_entry_table;
} SCE_TYPE(sce_module_imports);

/* alternative module imports struct with a size of 0x24 */
typedef struct SCE_TYPE(sce_module_imports_short) {
	uint16_t size;				/* Size of this struct, set to 0x24 */
	uint16_t version;			/* Set to 0x1 */
	uint16_t flags;				/* Set to 0x0 */
	uint16_t num_syms_funcs;		/* Number of function imports */
	uint16_t num_syms_vars;			/* Number of variable imports */
	uint16_t num_syms_unk;

	uint32_t module_nid;				/* NID of module to import */
	SCE_PTR(const char *) module_name;	/* Pointer to name of imported module, for debugging */
	SCE_PTR(uint32_t *) func_nid_table;	/* Pointer to array of function NIDs to import */
	SCE_PTR(const void **) func_entry_table;	/* Pointer to array of stub functions to fill */
	SCE_PTR(uint32_t *) var_nid_table;			/* Pointer to array of variable NIDs to import */
	SCE_PTR(const void **) var_entry_table;		/* Pointer to array of data pointers to write to */
} SCE_TYPE(sce_module_imports_short);

#undef SCE_TYPE
#undef SCE_PTR
