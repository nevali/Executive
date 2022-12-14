	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 0
	.globl	_PAL$metaClass@0.0              ; -- Begin function _PAL$metaClass@0.0
	.weak_definition	_PAL$metaClass@0.0
	.p2align	2
_PAL$metaClass@0.0:                     ; @"\01_PAL$metaClass@0.0"
Lfunc_begin0:
	.file	1 "/Volumes/Werkstatt/Executive/Stubs" "PAL-stubs.c"
	.loc	1 24 0                          ; PAL-stubs.c:24:0
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #24]
	str	x1, [sp, #16]
	str	x2, [sp, #8]
	mov	w0, #7
Ltmp1:
	.loc	1 29 2 prologue_end             ; PAL-stubs.c:29:2
	add	sp, sp, #32
	ret
Ltmp2:
Lfunc_end0:
	.cfi_endproc
                                        ; -- End function
	.globl	_PAL$__panic@0.0                ; -- Begin function _PAL$__panic@0.0
	.weak_definition	_PAL$__panic@0.0
	.p2align	2
_PAL$__panic@0.0:                       ; @"\01_PAL$__panic@0.0"
Lfunc_begin1:
	.loc	1 37 0                          ; PAL-stubs.c:37:0
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
Ltmp4:
	.loc	1 39 1 prologue_end             ; PAL-stubs.c:39:1
	add	sp, sp, #16
	ret
Ltmp5:
Lfunc_end1:
	.cfi_endproc
                                        ; -- End function
	.file	2 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types" "_uint8_t.h"
	.file	3 "/Volumes/Werkstatt/Executive/Stubs" "../Headers/Executive/UUID.h"
	.file	4 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types" "_uint32_t.h"
	.file	5 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types" "_uint16_t.h"
	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.byte	1                               ; Abbreviation Code
	.byte	17                              ; DW_TAG_compile_unit
	.byte	1                               ; DW_CHILDREN_yes
	.byte	37                              ; DW_AT_producer
	.byte	14                              ; DW_FORM_strp
	.byte	19                              ; DW_AT_language
	.byte	5                               ; DW_FORM_data2
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.ascii	"\202|"                         ; DW_AT_LLVM_sysroot
	.byte	14                              ; DW_FORM_strp
	.byte	16                              ; DW_AT_stmt_list
	.byte	23                              ; DW_FORM_sec_offset
	.byte	27                              ; DW_AT_comp_dir
	.byte	14                              ; DW_FORM_strp
	.byte	17                              ; DW_AT_low_pc
	.byte	1                               ; DW_FORM_addr
	.byte	18                              ; DW_AT_high_pc
	.byte	6                               ; DW_FORM_data4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	2                               ; Abbreviation Code
	.byte	46                              ; DW_TAG_subprogram
	.byte	1                               ; DW_CHILDREN_yes
	.byte	17                              ; DW_AT_low_pc
	.byte	1                               ; DW_FORM_addr
	.byte	18                              ; DW_AT_high_pc
	.byte	6                               ; DW_FORM_data4
	.ascii	"\347\177"                      ; DW_AT_APPLE_omit_frame_ptr
	.byte	25                              ; DW_FORM_flag_present
	.byte	64                              ; DW_AT_frame_base
	.byte	24                              ; DW_FORM_exprloc
	.byte	110                             ; DW_AT_linkage_name
	.byte	14                              ; DW_FORM_strp
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	39                              ; DW_AT_prototyped
	.byte	25                              ; DW_FORM_flag_present
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	63                              ; DW_AT_external
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	3                               ; Abbreviation Code
	.byte	5                               ; DW_TAG_formal_parameter
	.byte	0                               ; DW_CHILDREN_no
	.byte	2                               ; DW_AT_location
	.byte	24                              ; DW_FORM_exprloc
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	4                               ; Abbreviation Code
	.byte	46                              ; DW_TAG_subprogram
	.byte	1                               ; DW_CHILDREN_yes
	.byte	17                              ; DW_AT_low_pc
	.byte	1                               ; DW_FORM_addr
	.byte	18                              ; DW_AT_high_pc
	.byte	6                               ; DW_FORM_data4
	.ascii	"\347\177"                      ; DW_AT_APPLE_omit_frame_ptr
	.byte	25                              ; DW_FORM_flag_present
	.byte	64                              ; DW_AT_frame_base
	.byte	24                              ; DW_FORM_exprloc
	.byte	110                             ; DW_AT_linkage_name
	.byte	14                              ; DW_FORM_strp
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	39                              ; DW_AT_prototyped
	.byte	25                              ; DW_FORM_flag_present
	.byte	63                              ; DW_AT_external
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	5                               ; Abbreviation Code
	.byte	36                              ; DW_TAG_base_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	62                              ; DW_AT_encoding
	.byte	11                              ; DW_FORM_data1
	.byte	11                              ; DW_AT_byte_size
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	6                               ; Abbreviation Code
	.byte	38                              ; DW_TAG_const_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	7                               ; Abbreviation Code
	.byte	15                              ; DW_TAG_pointer_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	8                               ; Abbreviation Code
	.byte	23                              ; DW_TAG_union_type
	.byte	1                               ; DW_CHILDREN_yes
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	11                              ; DW_AT_byte_size
	.byte	11                              ; DW_FORM_data1
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	9                               ; Abbreviation Code
	.byte	13                              ; DW_TAG_member
	.byte	0                               ; DW_CHILDREN_no
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	56                              ; DW_AT_data_member_location
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	10                              ; Abbreviation Code
	.byte	19                              ; DW_TAG_structure_type
	.byte	1                               ; DW_CHILDREN_yes
	.byte	11                              ; DW_AT_byte_size
	.byte	11                              ; DW_FORM_data1
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	11                              ; Abbreviation Code
	.byte	1                               ; DW_TAG_array_type
	.byte	1                               ; DW_CHILDREN_yes
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	12                              ; Abbreviation Code
	.byte	33                              ; DW_TAG_subrange_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	55                              ; DW_AT_count
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	13                              ; Abbreviation Code
	.byte	22                              ; DW_TAG_typedef
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	58                              ; DW_AT_decl_file
	.byte	11                              ; DW_FORM_data1
	.byte	59                              ; DW_AT_decl_line
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	14                              ; Abbreviation Code
	.byte	36                              ; DW_TAG_base_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	3                               ; DW_AT_name
	.byte	14                              ; DW_FORM_strp
	.byte	11                              ; DW_AT_byte_size
	.byte	11                              ; DW_FORM_data1
	.byte	62                              ; DW_AT_encoding
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	15                              ; Abbreviation Code
	.byte	15                              ; DW_TAG_pointer_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	0                               ; EOM(3)
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
Lcu_begin0:
.set Lset0, Ldebug_info_end0-Ldebug_info_start0 ; Length of Unit
	.long	Lset0
Ldebug_info_start0:
	.short	4                               ; DWARF version number
.set Lset1, Lsection_abbrev-Lsection_abbrev ; Offset Into Abbrev. Section
	.long	Lset1
	.byte	8                               ; Address Size (in bytes)
	.byte	1                               ; Abbrev [1] 0xb:0x212 DW_TAG_compile_unit
	.long	0                               ; DW_AT_producer
	.short	12                              ; DW_AT_language
	.long	49                              ; DW_AT_name
	.long	61                              ; DW_AT_LLVM_sysroot
.set Lset2, Lline_table_start0-Lsection_line ; DW_AT_stmt_list
	.long	Lset2
	.long	63                              ; DW_AT_comp_dir
	.quad	Lfunc_begin0                    ; DW_AT_low_pc
.set Lset3, Lfunc_end1-Lfunc_begin0     ; DW_AT_high_pc
	.long	Lset3
	.byte	2                               ; Abbrev [2] 0x2e:0x48 DW_TAG_subprogram
	.quad	Lfunc_begin0                    ; DW_AT_low_pc
.set Lset4, Lfunc_end0-Lfunc_begin0     ; DW_AT_high_pc
	.long	Lset4
                                        ; DW_AT_APPLE_omit_frame_ptr
	.byte	1                               ; DW_AT_frame_base
	.byte	111
	.long	160                             ; DW_AT_linkage_name
	.long	98                              ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	23                              ; DW_AT_decl_line
                                        ; DW_AT_prototyped
	.long	158                             ; DW_AT_type
                                        ; DW_AT_external
	.byte	3                               ; Abbrev [3] 0x4b:0xe DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	24
	.long	200                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	23                              ; DW_AT_decl_line
	.long	165                             ; DW_AT_type
	.byte	3                               ; Abbrev [3] 0x59:0xe DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	16
	.long	436                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	23                              ; DW_AT_decl_line
	.long	165                             ; DW_AT_type
	.byte	3                               ; Abbrev [3] 0x67:0xe DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	8
	.long	440                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	23                              ; DW_AT_decl_line
	.long	517                             ; DW_AT_type
	.byte	0                               ; End Of Children Mark
	.byte	4                               ; Abbrev [4] 0x76:0x28 DW_TAG_subprogram
	.quad	Lfunc_begin1                    ; DW_AT_low_pc
.set Lset5, Lfunc_end1-Lfunc_begin1     ; DW_AT_high_pc
	.long	Lset5
                                        ; DW_AT_APPLE_omit_frame_ptr
	.byte	1                               ; DW_AT_frame_base
	.byte	111
	.long	183                             ; DW_AT_linkage_name
	.long	132                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	36                              ; DW_AT_decl_line
                                        ; DW_AT_prototyped
                                        ; DW_AT_external
	.byte	3                               ; Abbrev [3] 0x8f:0xe DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	8
	.long	444                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	36                              ; DW_AT_decl_line
	.long	523                             ; DW_AT_type
	.byte	0                               ; End Of Children Mark
	.byte	5                               ; Abbrev [5] 0x9e:0x7 DW_TAG_base_type
	.long	179                             ; DW_AT_name
	.byte	5                               ; DW_AT_encoding
	.byte	4                               ; DW_AT_byte_size
	.byte	6                               ; Abbrev [6] 0xa5:0x5 DW_TAG_const_type
	.long	170                             ; DW_AT_type
	.byte	7                               ; Abbrev [7] 0xaa:0x5 DW_TAG_pointer_type
	.long	175                             ; DW_AT_type
	.byte	6                               ; Abbrev [6] 0xaf:0x5 DW_TAG_const_type
	.long	180                             ; DW_AT_type
	.byte	8                               ; Abbrev [8] 0xb4:0xf0 DW_TAG_union_type
	.long	206                             ; DW_AT_name
	.byte	16                              ; DW_AT_byte_size
	.byte	3                               ; DW_AT_decl_file
	.byte	36                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0xbc:0xc DW_TAG_member
	.long	211                             ; DW_AT_name
	.long	420                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	38                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0xc8:0xc DW_TAG_member
	.long	259                             ; DW_AT_name
	.long	212                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	44                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	10                              ; Abbrev [10] 0xd4:0x35 DW_TAG_structure_type
	.byte	16                              ; DW_AT_byte_size
	.byte	3                               ; DW_AT_decl_file
	.byte	39                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0xd8:0xc DW_TAG_member
	.long	261                             ; DW_AT_name
	.long	457                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	40                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0xe4:0xc DW_TAG_member
	.long	286                             ; DW_AT_name
	.long	457                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	41                              ; DW_AT_decl_line
	.byte	4                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0xf0:0xc DW_TAG_member
	.long	289                             ; DW_AT_name
	.long	457                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	42                              ; DW_AT_decl_line
	.byte	8                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0xfc:0xc DW_TAG_member
	.long	292                             ; DW_AT_name
	.long	457                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	43                              ; DW_AT_decl_line
	.byte	12                              ; DW_AT_data_member_location
	.byte	0                               ; End Of Children Mark
	.byte	9                               ; Abbrev [9] 0x109:0xc DW_TAG_member
	.long	295                             ; DW_AT_name
	.long	277                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	51                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	10                              ; Abbrev [10] 0x115:0x35 DW_TAG_structure_type
	.byte	16                              ; DW_AT_byte_size
	.byte	3                               ; DW_AT_decl_file
	.byte	45                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0x119:0xc DW_TAG_member
	.long	300                             ; DW_AT_name
	.long	457                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	47                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x125:0xc DW_TAG_member
	.long	306                             ; DW_AT_name
	.long	475                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	48                              ; DW_AT_decl_line
	.byte	4                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x131:0xc DW_TAG_member
	.long	336                             ; DW_AT_name
	.long	475                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	49                              ; DW_AT_decl_line
	.byte	6                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x13d:0xc DW_TAG_member
	.long	342                             ; DW_AT_name
	.long	493                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	50                              ; DW_AT_decl_line
	.byte	8                               ; DW_AT_data_member_location
	.byte	0                               ; End Of Children Mark
	.byte	9                               ; Abbrev [9] 0x14a:0xc DW_TAG_member
	.long	348                             ; DW_AT_name
	.long	342                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	60                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	10                              ; Abbrev [10] 0x156:0x4d DW_TAG_structure_type
	.byte	16                              ; DW_AT_byte_size
	.byte	3                               ; DW_AT_decl_file
	.byte	52                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0x15a:0xc DW_TAG_member
	.long	353                             ; DW_AT_name
	.long	457                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	54                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x166:0xc DW_TAG_member
	.long	362                             ; DW_AT_name
	.long	475                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	55                              ; DW_AT_decl_line
	.byte	4                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x172:0xc DW_TAG_member
	.long	371                             ; DW_AT_name
	.long	475                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	56                              ; DW_AT_decl_line
	.byte	6                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x17e:0xc DW_TAG_member
	.long	391                             ; DW_AT_name
	.long	432                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	57                              ; DW_AT_decl_line
	.byte	8                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x18a:0xc DW_TAG_member
	.long	417                             ; DW_AT_name
	.long	432                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	58                              ; DW_AT_decl_line
	.byte	9                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x196:0xc DW_TAG_member
	.long	431                             ; DW_AT_name
	.long	505                             ; DW_AT_type
	.byte	3                               ; DW_AT_decl_file
	.byte	59                              ; DW_AT_decl_line
	.byte	10                              ; DW_AT_data_member_location
	.byte	0                               ; End Of Children Mark
	.byte	0                               ; End Of Children Mark
	.byte	11                              ; Abbrev [11] 0x1a4:0xc DW_TAG_array_type
	.long	432                             ; DW_AT_type
	.byte	12                              ; Abbrev [12] 0x1a9:0x6 DW_TAG_subrange_type
	.long	450                             ; DW_AT_type
	.byte	16                              ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	13                              ; Abbrev [13] 0x1b0:0xb DW_TAG_typedef
	.long	443                             ; DW_AT_type
	.long	217                             ; DW_AT_name
	.byte	2                               ; DW_AT_decl_file
	.byte	31                              ; DW_AT_decl_line
	.byte	5                               ; Abbrev [5] 0x1bb:0x7 DW_TAG_base_type
	.long	225                             ; DW_AT_name
	.byte	8                               ; DW_AT_encoding
	.byte	1                               ; DW_AT_byte_size
	.byte	14                              ; Abbrev [14] 0x1c2:0x7 DW_TAG_base_type
	.long	239                             ; DW_AT_name
	.byte	8                               ; DW_AT_byte_size
	.byte	7                               ; DW_AT_encoding
	.byte	13                              ; Abbrev [13] 0x1c9:0xb DW_TAG_typedef
	.long	468                             ; DW_AT_type
	.long	264                             ; DW_AT_name
	.byte	4                               ; DW_AT_decl_file
	.byte	31                              ; DW_AT_decl_line
	.byte	5                               ; Abbrev [5] 0x1d4:0x7 DW_TAG_base_type
	.long	273                             ; DW_AT_name
	.byte	7                               ; DW_AT_encoding
	.byte	4                               ; DW_AT_byte_size
	.byte	13                              ; Abbrev [13] 0x1db:0xb DW_TAG_typedef
	.long	486                             ; DW_AT_type
	.long	312                             ; DW_AT_name
	.byte	5                               ; DW_AT_decl_file
	.byte	31                              ; DW_AT_decl_line
	.byte	5                               ; Abbrev [5] 0x1e6:0x7 DW_TAG_base_type
	.long	321                             ; DW_AT_name
	.byte	7                               ; DW_AT_encoding
	.byte	2                               ; DW_AT_byte_size
	.byte	11                              ; Abbrev [11] 0x1ed:0xc DW_TAG_array_type
	.long	432                             ; DW_AT_type
	.byte	12                              ; Abbrev [12] 0x1f2:0x6 DW_TAG_subrange_type
	.long	450                             ; DW_AT_type
	.byte	8                               ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	11                              ; Abbrev [11] 0x1f9:0xc DW_TAG_array_type
	.long	432                             ; DW_AT_type
	.byte	12                              ; Abbrev [12] 0x1fe:0x6 DW_TAG_subrange_type
	.long	450                             ; DW_AT_type
	.byte	6                               ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	7                               ; Abbrev [7] 0x205:0x5 DW_TAG_pointer_type
	.long	522                             ; DW_AT_type
	.byte	15                              ; Abbrev [15] 0x20a:0x1 DW_TAG_pointer_type
	.byte	7                               ; Abbrev [7] 0x20b:0x5 DW_TAG_pointer_type
	.long	528                             ; DW_AT_type
	.byte	6                               ; Abbrev [6] 0x210:0x5 DW_TAG_const_type
	.long	533                             ; DW_AT_type
	.byte	5                               ; Abbrev [5] 0x215:0x7 DW_TAG_base_type
	.long	448                             ; DW_AT_name
	.byte	6                               ; DW_AT_encoding
	.byte	1                               ; DW_AT_byte_size
	.byte	0                               ; End Of Children Mark
Ldebug_info_end0:
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"Apple clang version 14.0.0 (clang-1400.0.29.202)" ; string offset=0
	.asciz	"PAL-stubs.c"                   ; string offset=49
	.asciz	"/"                             ; string offset=61
	.asciz	"/Volumes/Werkstatt/Executive/Stubs" ; string offset=63
	.asciz	"PAL_metaClass"                 ; string offset=98
	.asciz	"\001_PAL$metaClass@0.0"        ; string offset=112
	.asciz	"PAL_panic"                     ; string offset=132
	.asciz	"\001_PAL$__panic@0.0"          ; string offset=142
	.asciz	"_PAL$metaClass@0.0"            ; string offset=160
	.asciz	"int"                           ; string offset=179
	.asciz	"_PAL$__panic@0.0"              ; string offset=183
	.asciz	"clsid"                         ; string offset=200
	.asciz	"UUID"                          ; string offset=206
	.asciz	"bytes"                         ; string offset=211
	.asciz	"uint8_t"                       ; string offset=217
	.asciz	"unsigned char"                 ; string offset=225
	.asciz	"__ARRAY_SIZE_TYPE__"           ; string offset=239
	.asciz	"d"                             ; string offset=259
	.asciz	"d1"                            ; string offset=261
	.asciz	"uint32_t"                      ; string offset=264
	.asciz	"unsigned int"                  ; string offset=273
	.asciz	"d2"                            ; string offset=286
	.asciz	"d3"                            ; string offset=289
	.asciz	"d4"                            ; string offset=292
	.asciz	"guid"                          ; string offset=295
	.asciz	"data1"                         ; string offset=300
	.asciz	"data2"                         ; string offset=306
	.asciz	"uint16_t"                      ; string offset=312
	.asciz	"unsigned short"                ; string offset=321
	.asciz	"data3"                         ; string offset=336
	.asciz	"data4"                         ; string offset=342
	.asciz	"uuid"                          ; string offset=348
	.asciz	"time_low"                      ; string offset=353
	.asciz	"time_mid"                      ; string offset=362
	.asciz	"time_hi_and_version"           ; string offset=371
	.asciz	"clock_seq_hi_and_reserved"     ; string offset=391
	.asciz	"clock_seq_low"                 ; string offset=417
	.asciz	"node"                          ; string offset=431
	.asciz	"iid"                           ; string offset=436
	.asciz	"out"                           ; string offset=440
	.asciz	"str"                           ; string offset=444
	.asciz	"char"                          ; string offset=448
	.section	__DWARF,__apple_names,regular,debug
Lnames_begin:
	.long	1212240712                      ; Header Magic
	.short	1                               ; Header Version
	.short	0                               ; Header Hash Function
	.long	4                               ; Header Bucket Count
	.long	4                               ; Header Hash Count
	.long	12                              ; Header Data Length
	.long	0                               ; HeaderData Die Offset Base
	.long	1                               ; HeaderData Atom Count
	.short	1                               ; DW_ATOM_die_offset
	.short	6                               ; DW_FORM_data4
	.long	0                               ; Bucket 0
	.long	1                               ; Bucket 1
	.long	3                               ; Bucket 2
	.long	-1                              ; Bucket 3
	.long	364695596                       ; Hash in Bucket 0
	.long	-2086571503                     ; Hash in Bucket 1
	.long	-1641245763                     ; Hash in Bucket 1
	.long	1468072670                      ; Hash in Bucket 2
.set Lset6, LNames0-Lnames_begin        ; Offset in Bucket 0
	.long	Lset6
.set Lset7, LNames3-Lnames_begin        ; Offset in Bucket 1
	.long	Lset7
.set Lset8, LNames1-Lnames_begin        ; Offset in Bucket 1
	.long	Lset8
.set Lset9, LNames2-Lnames_begin        ; Offset in Bucket 2
	.long	Lset9
LNames0:
	.long	132                             ; PAL_panic
	.long	1                               ; Num DIEs
	.long	118
	.long	0
LNames3:
	.long	112                             ; _PAL$metaClass@0.0
	.long	1                               ; Num DIEs
	.long	46
	.long	0
LNames1:
	.long	142                             ; _PAL$__panic@0.0
	.long	1                               ; Num DIEs
	.long	118
	.long	0
LNames2:
	.long	98                              ; PAL_metaClass
	.long	1                               ; Num DIEs
	.long	46
	.long	0
	.section	__DWARF,__apple_objc,regular,debug
Lobjc_begin:
	.long	1212240712                      ; Header Magic
	.short	1                               ; Header Version
	.short	0                               ; Header Hash Function
	.long	1                               ; Header Bucket Count
	.long	0                               ; Header Hash Count
	.long	12                              ; Header Data Length
	.long	0                               ; HeaderData Die Offset Base
	.long	1                               ; HeaderData Atom Count
	.short	1                               ; DW_ATOM_die_offset
	.short	6                               ; DW_FORM_data4
	.long	-1                              ; Bucket 0
	.section	__DWARF,__apple_namespac,regular,debug
Lnamespac_begin:
	.long	1212240712                      ; Header Magic
	.short	1                               ; Header Version
	.short	0                               ; Header Hash Function
	.long	1                               ; Header Bucket Count
	.long	0                               ; Header Hash Count
	.long	12                              ; Header Data Length
	.long	0                               ; HeaderData Die Offset Base
	.long	1                               ; HeaderData Atom Count
	.short	1                               ; DW_ATOM_die_offset
	.short	6                               ; DW_FORM_data4
	.long	-1                              ; Bucket 0
	.section	__DWARF,__apple_types,regular,debug
Ltypes_begin:
	.long	1212240712                      ; Header Magic
	.short	1                               ; Header Version
	.short	0                               ; Header Hash Function
	.long	10                              ; Header Bucket Count
	.long	10                              ; Header Hash Count
	.long	20                              ; Header Data Length
	.long	0                               ; HeaderData Die Offset Base
	.long	3                               ; HeaderData Atom Count
	.short	1                               ; DW_ATOM_die_offset
	.short	6                               ; DW_FORM_data4
	.short	3                               ; DW_ATOM_die_tag
	.short	5                               ; DW_FORM_data2
	.short	4                               ; DW_ATOM_type_flags
	.short	11                              ; DW_FORM_data1
	.long	-1                              ; Bucket 0
	.long	0                               ; Bucket 1
	.long	1                               ; Bucket 2
	.long	-1                              ; Bucket 3
	.long	2                               ; Bucket 4
	.long	3                               ; Bucket 5
	.long	5                               ; Bucket 6
	.long	6                               ; Bucket 7
	.long	7                               ; Bucket 8
	.long	9                               ; Bucket 9
	.long	-594775205                      ; Hash in Bucket 1
	.long	2089623292                      ; Hash in Bucket 2
	.long	-104093792                      ; Hash in Bucket 4
	.long	290711645                       ; Hash in Bucket 5
	.long	-1304652851                     ; Hash in Bucket 5
	.long	789719536                       ; Hash in Bucket 6
	.long	290644127                       ; Hash in Bucket 7
	.long	193495088                       ; Hash in Bucket 8
	.long	878862258                       ; Hash in Bucket 8
	.long	2090147939                      ; Hash in Bucket 9
.set Lset10, Ltypes0-Ltypes_begin       ; Offset in Bucket 1
	.long	Lset10
.set Lset11, Ltypes1-Ltypes_begin       ; Offset in Bucket 2
	.long	Lset11
.set Lset12, Ltypes8-Ltypes_begin       ; Offset in Bucket 4
	.long	Lset12
.set Lset13, Ltypes2-Ltypes_begin       ; Offset in Bucket 5
	.long	Lset13
.set Lset14, Ltypes3-Ltypes_begin       ; Offset in Bucket 5
	.long	Lset14
.set Lset15, Ltypes6-Ltypes_begin       ; Offset in Bucket 6
	.long	Lset15
.set Lset16, Ltypes4-Ltypes_begin       ; Offset in Bucket 7
	.long	Lset16
.set Lset17, Ltypes5-Ltypes_begin       ; Offset in Bucket 8
	.long	Lset17
.set Lset18, Ltypes7-Ltypes_begin       ; Offset in Bucket 8
	.long	Lset18
.set Lset19, Ltypes9-Ltypes_begin       ; Offset in Bucket 9
	.long	Lset19
Ltypes0:
	.long	239                             ; __ARRAY_SIZE_TYPE__
	.long	1                               ; Num DIEs
	.long	450
	.short	36
	.byte	0
	.long	0
Ltypes1:
	.long	206                             ; UUID
	.long	1                               ; Num DIEs
	.long	180
	.short	23
	.byte	0
	.long	0
Ltypes8:
	.long	225                             ; unsigned char
	.long	1                               ; Num DIEs
	.long	443
	.short	36
	.byte	0
	.long	0
Ltypes2:
	.long	264                             ; uint32_t
	.long	1                               ; Num DIEs
	.long	457
	.short	22
	.byte	0
	.long	0
Ltypes3:
	.long	273                             ; unsigned int
	.long	1                               ; Num DIEs
	.long	468
	.short	36
	.byte	0
	.long	0
Ltypes6:
	.long	217                             ; uint8_t
	.long	1                               ; Num DIEs
	.long	432
	.short	22
	.byte	0
	.long	0
Ltypes4:
	.long	312                             ; uint16_t
	.long	1                               ; Num DIEs
	.long	475
	.short	22
	.byte	0
	.long	0
Ltypes5:
	.long	179                             ; int
	.long	1                               ; Num DIEs
	.long	158
	.short	36
	.byte	0
	.long	0
Ltypes7:
	.long	321                             ; unsigned short
	.long	1                               ; Num DIEs
	.long	486
	.short	36
	.byte	0
	.long	0
Ltypes9:
	.long	448                             ; char
	.long	1                               ; Num DIEs
	.long	533
	.short	36
	.byte	0
	.long	0
.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
