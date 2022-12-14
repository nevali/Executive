	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 0
	.globl	_EXECUTIVE$__start@0.0          ; -- Begin function _EXECUTIVE$__start@0.0
	.weak_definition	_EXECUTIVE$__start@0.0
	.p2align	2
_EXECUTIVE$__start@0.0:                 ; @"\01_EXECUTIVE$__start@0.0"
Lfunc_begin0:
	.file	1 "/Volumes/Werkstatt/Executive/Stubs" "Executive-stubs.c"
	.loc	1 15 0                          ; Executive-stubs.c:15:0
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
Ltmp1:
	.loc	1 17 1 prologue_end             ; Executive-stubs.c:17:1
	add	sp, sp, #16
	ret
Ltmp2:
Lfunc_end0:
	.cfi_endproc
                                        ; -- End function
	.globl	_EXECUTIVE$__syscall@0.0        ; -- Begin function _EXECUTIVE$__syscall@0.0
	.weak_definition	_EXECUTIVE$__syscall@0.0
	.p2align	2
_EXECUTIVE$__syscall@0.0:               ; @"\01_EXECUTIVE$__syscall@0.0"
Lfunc_begin1:
	.loc	1 21 0                          ; Executive-stubs.c:21:0
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	str	w1, [sp, #8]
	mov	w0, #7
Ltmp4:
	.loc	1 25 2 prologue_end             ; Executive-stubs.c:25:2
	add	sp, sp, #16
	ret
Ltmp5:
Lfunc_end1:
	.cfi_endproc
                                        ; -- End function
	.file	2 "/Volumes/Werkstatt/Executive/Stubs" "../PrivateHeaders/Executive/Internal/Entry.h"
	.file	3 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types" "_uint8_t.h"
	.file	4 "/Volumes/Werkstatt/Executive/Stubs" "../Headers/Executive/UUID.h"
	.file	5 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types" "_uint32_t.h"
	.file	6 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_types" "_uint16_t.h"
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
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	63                              ; DW_AT_external
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	5                               ; Abbreviation Code
	.byte	24                              ; DW_TAG_unspecified_parameters
	.byte	0                               ; DW_CHILDREN_no
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	6                               ; Abbreviation Code
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
	.byte	7                               ; Abbreviation Code
	.byte	15                              ; DW_TAG_pointer_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	8                               ; Abbreviation Code
	.byte	19                              ; DW_TAG_structure_type
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
	.byte	21                              ; DW_TAG_subroutine_type
	.byte	1                               ; DW_CHILDREN_yes
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	39                              ; DW_AT_prototyped
	.byte	25                              ; DW_FORM_flag_present
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	11                              ; Abbreviation Code
	.byte	5                               ; DW_TAG_formal_parameter
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	12                              ; Abbreviation Code
	.byte	38                              ; DW_TAG_const_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	13                              ; Abbreviation Code
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
	.byte	14                              ; Abbreviation Code
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
	.byte	15                              ; Abbreviation Code
	.byte	1                               ; DW_TAG_array_type
	.byte	1                               ; DW_CHILDREN_yes
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	16                              ; Abbreviation Code
	.byte	33                              ; DW_TAG_subrange_type
	.byte	0                               ; DW_CHILDREN_no
	.byte	73                              ; DW_AT_type
	.byte	19                              ; DW_FORM_ref4
	.byte	55                              ; DW_AT_count
	.byte	11                              ; DW_FORM_data1
	.byte	0                               ; EOM(1)
	.byte	0                               ; EOM(2)
	.byte	17                              ; Abbreviation Code
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
	.byte	18                              ; Abbreviation Code
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
	.byte	19                              ; Abbreviation Code
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
	.byte	1                               ; Abbrev [1] 0xb:0x25d DW_TAG_compile_unit
	.long	0                               ; DW_AT_producer
	.short	12                              ; DW_AT_language
	.long	49                              ; DW_AT_name
	.long	67                              ; DW_AT_LLVM_sysroot
.set Lset2, Lline_table_start0-Lsection_line ; DW_AT_stmt_list
	.long	Lset2
	.long	69                              ; DW_AT_comp_dir
	.quad	Lfunc_begin0                    ; DW_AT_low_pc
.set Lset3, Lfunc_end1-Lfunc_begin0     ; DW_AT_high_pc
	.long	Lset3
	.byte	2                               ; Abbrev [2] 0x2e:0x28 DW_TAG_subprogram
	.quad	Lfunc_begin0                    ; DW_AT_low_pc
.set Lset4, Lfunc_end0-Lfunc_begin0     ; DW_AT_high_pc
	.long	Lset4
                                        ; DW_AT_APPLE_omit_frame_ptr
	.byte	1                               ; DW_AT_frame_base
	.byte	111
	.long	183                             ; DW_AT_linkage_name
	.long	104                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	14                              ; DW_AT_decl_line
                                        ; DW_AT_prototyped
                                        ; DW_AT_external
	.byte	3                               ; Abbrev [3] 0x47:0xe DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	8
	.long	235                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	14                              ; DW_AT_decl_line
	.long	152                             ; DW_AT_type
	.byte	0                               ; End Of Children Mark
	.byte	4                               ; Abbrev [4] 0x56:0x3b DW_TAG_subprogram
	.quad	Lfunc_begin1                    ; DW_AT_low_pc
.set Lset5, Lfunc_end1-Lfunc_begin1     ; DW_AT_high_pc
	.long	Lset5
                                        ; DW_AT_APPLE_omit_frame_ptr
	.byte	1                               ; DW_AT_frame_base
	.byte	111
	.long	206                             ; DW_AT_linkage_name
	.long	144                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	20                              ; DW_AT_decl_line
                                        ; DW_AT_prototyped
	.long	145                             ; DW_AT_type
                                        ; DW_AT_external
	.byte	3                               ; Abbrev [3] 0x73:0xe DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	12
	.long	534                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	20                              ; DW_AT_decl_line
	.long	145                             ; DW_AT_type
	.byte	3                               ; Abbrev [3] 0x81:0xe DW_TAG_formal_parameter
	.byte	2                               ; DW_AT_location
	.byte	145
	.byte	8
	.long	537                             ; DW_AT_name
	.byte	1                               ; DW_AT_decl_file
	.byte	20                              ; DW_AT_decl_line
	.long	145                             ; DW_AT_type
	.byte	5                               ; Abbrev [5] 0x8f:0x1 DW_TAG_unspecified_parameters
	.byte	0                               ; End Of Children Mark
	.byte	6                               ; Abbrev [6] 0x91:0x7 DW_TAG_base_type
	.long	231                             ; DW_AT_name
	.byte	5                               ; DW_AT_encoding
	.byte	4                               ; DW_AT_byte_size
	.byte	7                               ; Abbrev [7] 0x98:0x5 DW_TAG_pointer_type
	.long	157                             ; DW_AT_type
	.byte	8                               ; Abbrev [8] 0x9d:0x39 DW_TAG_structure_type
	.long	242                             ; DW_AT_name
	.byte	32                              ; DW_AT_byte_size
	.byte	2                               ; DW_AT_decl_file
	.byte	9                               ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0xa5:0xc DW_TAG_member
	.long	267                             ; DW_AT_name
	.long	145                             ; DW_AT_type
	.byte	2                               ; DW_AT_decl_file
	.byte	11                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0xb1:0xc DW_TAG_member
	.long	272                             ; DW_AT_name
	.long	214                             ; DW_AT_type
	.byte	2                               ; DW_AT_decl_file
	.byte	12                              ; DW_AT_decl_line
	.byte	8                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0xbd:0xc DW_TAG_member
	.long	282                             ; DW_AT_name
	.long	214                             ; DW_AT_type
	.byte	2                               ; DW_AT_decl_file
	.byte	13                              ; DW_AT_decl_line
	.byte	16                              ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0xc9:0xc DW_TAG_member
	.long	290                             ; DW_AT_name
	.long	231                             ; DW_AT_type
	.byte	2                               ; DW_AT_decl_file
	.byte	14                              ; DW_AT_decl_line
	.byte	24                              ; DW_AT_data_member_location
	.byte	0                               ; End Of Children Mark
	.byte	7                               ; Abbrev [7] 0xd6:0x5 DW_TAG_pointer_type
	.long	219                             ; DW_AT_type
	.byte	7                               ; Abbrev [7] 0xdb:0x5 DW_TAG_pointer_type
	.long	224                             ; DW_AT_type
	.byte	6                               ; Abbrev [6] 0xe0:0x7 DW_TAG_base_type
	.long	277                             ; DW_AT_name
	.byte	6                               ; DW_AT_encoding
	.byte	1                               ; DW_AT_byte_size
	.byte	7                               ; Abbrev [7] 0xe7:0x5 DW_TAG_pointer_type
	.long	236                             ; DW_AT_type
	.byte	10                              ; Abbrev [10] 0xec:0x15 DW_TAG_subroutine_type
	.long	145                             ; DW_AT_type
                                        ; DW_AT_prototyped
	.byte	11                              ; Abbrev [11] 0xf1:0x5 DW_TAG_formal_parameter
	.long	257                             ; DW_AT_type
	.byte	11                              ; Abbrev [11] 0xf6:0x5 DW_TAG_formal_parameter
	.long	257                             ; DW_AT_type
	.byte	11                              ; Abbrev [11] 0xfb:0x5 DW_TAG_formal_parameter
	.long	609                             ; DW_AT_type
	.byte	0                               ; End Of Children Mark
	.byte	12                              ; Abbrev [12] 0x101:0x5 DW_TAG_const_type
	.long	262                             ; DW_AT_type
	.byte	7                               ; Abbrev [7] 0x106:0x5 DW_TAG_pointer_type
	.long	267                             ; DW_AT_type
	.byte	12                              ; Abbrev [12] 0x10b:0x5 DW_TAG_const_type
	.long	272                             ; DW_AT_type
	.byte	13                              ; Abbrev [13] 0x110:0xf0 DW_TAG_union_type
	.long	304                             ; DW_AT_name
	.byte	16                              ; DW_AT_byte_size
	.byte	4                               ; DW_AT_decl_file
	.byte	36                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0x118:0xc DW_TAG_member
	.long	309                             ; DW_AT_name
	.long	512                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	38                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x124:0xc DW_TAG_member
	.long	357                             ; DW_AT_name
	.long	304                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	44                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	14                              ; Abbrev [14] 0x130:0x35 DW_TAG_structure_type
	.byte	16                              ; DW_AT_byte_size
	.byte	4                               ; DW_AT_decl_file
	.byte	39                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0x134:0xc DW_TAG_member
	.long	359                             ; DW_AT_name
	.long	549                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	40                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x140:0xc DW_TAG_member
	.long	384                             ; DW_AT_name
	.long	549                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	41                              ; DW_AT_decl_line
	.byte	4                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x14c:0xc DW_TAG_member
	.long	387                             ; DW_AT_name
	.long	549                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	42                              ; DW_AT_decl_line
	.byte	8                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x158:0xc DW_TAG_member
	.long	390                             ; DW_AT_name
	.long	549                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	43                              ; DW_AT_decl_line
	.byte	12                              ; DW_AT_data_member_location
	.byte	0                               ; End Of Children Mark
	.byte	9                               ; Abbrev [9] 0x165:0xc DW_TAG_member
	.long	393                             ; DW_AT_name
	.long	369                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	51                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	14                              ; Abbrev [14] 0x171:0x35 DW_TAG_structure_type
	.byte	16                              ; DW_AT_byte_size
	.byte	4                               ; DW_AT_decl_file
	.byte	45                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0x175:0xc DW_TAG_member
	.long	398                             ; DW_AT_name
	.long	549                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	47                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x181:0xc DW_TAG_member
	.long	404                             ; DW_AT_name
	.long	567                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	48                              ; DW_AT_decl_line
	.byte	4                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x18d:0xc DW_TAG_member
	.long	434                             ; DW_AT_name
	.long	567                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	49                              ; DW_AT_decl_line
	.byte	6                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x199:0xc DW_TAG_member
	.long	440                             ; DW_AT_name
	.long	585                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	50                              ; DW_AT_decl_line
	.byte	8                               ; DW_AT_data_member_location
	.byte	0                               ; End Of Children Mark
	.byte	9                               ; Abbrev [9] 0x1a6:0xc DW_TAG_member
	.long	446                             ; DW_AT_name
	.long	434                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	60                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	14                              ; Abbrev [14] 0x1b2:0x4d DW_TAG_structure_type
	.byte	16                              ; DW_AT_byte_size
	.byte	4                               ; DW_AT_decl_file
	.byte	52                              ; DW_AT_decl_line
	.byte	9                               ; Abbrev [9] 0x1b6:0xc DW_TAG_member
	.long	451                             ; DW_AT_name
	.long	549                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	54                              ; DW_AT_decl_line
	.byte	0                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x1c2:0xc DW_TAG_member
	.long	460                             ; DW_AT_name
	.long	567                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	55                              ; DW_AT_decl_line
	.byte	4                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x1ce:0xc DW_TAG_member
	.long	469                             ; DW_AT_name
	.long	567                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	56                              ; DW_AT_decl_line
	.byte	6                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x1da:0xc DW_TAG_member
	.long	489                             ; DW_AT_name
	.long	524                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	57                              ; DW_AT_decl_line
	.byte	8                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x1e6:0xc DW_TAG_member
	.long	515                             ; DW_AT_name
	.long	524                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	58                              ; DW_AT_decl_line
	.byte	9                               ; DW_AT_data_member_location
	.byte	9                               ; Abbrev [9] 0x1f2:0xc DW_TAG_member
	.long	529                             ; DW_AT_name
	.long	597                             ; DW_AT_type
	.byte	4                               ; DW_AT_decl_file
	.byte	59                              ; DW_AT_decl_line
	.byte	10                              ; DW_AT_data_member_location
	.byte	0                               ; End Of Children Mark
	.byte	0                               ; End Of Children Mark
	.byte	15                              ; Abbrev [15] 0x200:0xc DW_TAG_array_type
	.long	524                             ; DW_AT_type
	.byte	16                              ; Abbrev [16] 0x205:0x6 DW_TAG_subrange_type
	.long	542                             ; DW_AT_type
	.byte	16                              ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	17                              ; Abbrev [17] 0x20c:0xb DW_TAG_typedef
	.long	535                             ; DW_AT_type
	.long	315                             ; DW_AT_name
	.byte	3                               ; DW_AT_decl_file
	.byte	31                              ; DW_AT_decl_line
	.byte	6                               ; Abbrev [6] 0x217:0x7 DW_TAG_base_type
	.long	323                             ; DW_AT_name
	.byte	8                               ; DW_AT_encoding
	.byte	1                               ; DW_AT_byte_size
	.byte	18                              ; Abbrev [18] 0x21e:0x7 DW_TAG_base_type
	.long	337                             ; DW_AT_name
	.byte	8                               ; DW_AT_byte_size
	.byte	7                               ; DW_AT_encoding
	.byte	17                              ; Abbrev [17] 0x225:0xb DW_TAG_typedef
	.long	560                             ; DW_AT_type
	.long	362                             ; DW_AT_name
	.byte	5                               ; DW_AT_decl_file
	.byte	31                              ; DW_AT_decl_line
	.byte	6                               ; Abbrev [6] 0x230:0x7 DW_TAG_base_type
	.long	371                             ; DW_AT_name
	.byte	7                               ; DW_AT_encoding
	.byte	4                               ; DW_AT_byte_size
	.byte	17                              ; Abbrev [17] 0x237:0xb DW_TAG_typedef
	.long	578                             ; DW_AT_type
	.long	410                             ; DW_AT_name
	.byte	6                               ; DW_AT_decl_file
	.byte	31                              ; DW_AT_decl_line
	.byte	6                               ; Abbrev [6] 0x242:0x7 DW_TAG_base_type
	.long	419                             ; DW_AT_name
	.byte	7                               ; DW_AT_encoding
	.byte	2                               ; DW_AT_byte_size
	.byte	15                              ; Abbrev [15] 0x249:0xc DW_TAG_array_type
	.long	524                             ; DW_AT_type
	.byte	16                              ; Abbrev [16] 0x24e:0x6 DW_TAG_subrange_type
	.long	542                             ; DW_AT_type
	.byte	8                               ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	15                              ; Abbrev [15] 0x255:0xc DW_TAG_array_type
	.long	524                             ; DW_AT_type
	.byte	16                              ; Abbrev [16] 0x25a:0x6 DW_TAG_subrange_type
	.long	542                             ; DW_AT_type
	.byte	6                               ; DW_AT_count
	.byte	0                               ; End Of Children Mark
	.byte	7                               ; Abbrev [7] 0x261:0x5 DW_TAG_pointer_type
	.long	614                             ; DW_AT_type
	.byte	19                              ; Abbrev [19] 0x266:0x1 DW_TAG_pointer_type
	.byte	0                               ; End Of Children Mark
Ldebug_info_end0:
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"Apple clang version 14.0.0 (clang-1400.0.29.202)" ; string offset=0
	.asciz	"Executive-stubs.c"             ; string offset=49
	.asciz	"/"                             ; string offset=67
	.asciz	"/Volumes/Werkstatt/Executive/Stubs" ; string offset=69
	.asciz	"Executive_start"               ; string offset=104
	.asciz	"\001_EXECUTIVE$__start@0.0"    ; string offset=120
	.asciz	"ExSystemCall"                  ; string offset=144
	.asciz	"\001_EXECUTIVE$__syscall@0.0"  ; string offset=157
	.asciz	"_EXECUTIVE$__start@0.0"        ; string offset=183
	.asciz	"_EXECUTIVE$__syscall@0.0"      ; string offset=206
	.asciz	"int"                           ; string offset=231
	.asciz	"params"                        ; string offset=235
	.asciz	"ExecutiveEntryParameters"      ; string offset=242
	.asciz	"argc"                          ; string offset=267
	.asciz	"argv"                          ; string offset=272
	.asciz	"char"                          ; string offset=277
	.asciz	"environ"                       ; string offset=282
	.asciz	"PAL_metaClass"                 ; string offset=290
	.asciz	"UUID"                          ; string offset=304
	.asciz	"bytes"                         ; string offset=309
	.asciz	"uint8_t"                       ; string offset=315
	.asciz	"unsigned char"                 ; string offset=323
	.asciz	"__ARRAY_SIZE_TYPE__"           ; string offset=337
	.asciz	"d"                             ; string offset=357
	.asciz	"d1"                            ; string offset=359
	.asciz	"uint32_t"                      ; string offset=362
	.asciz	"unsigned int"                  ; string offset=371
	.asciz	"d2"                            ; string offset=384
	.asciz	"d3"                            ; string offset=387
	.asciz	"d4"                            ; string offset=390
	.asciz	"guid"                          ; string offset=393
	.asciz	"data1"                         ; string offset=398
	.asciz	"data2"                         ; string offset=404
	.asciz	"uint16_t"                      ; string offset=410
	.asciz	"unsigned short"                ; string offset=419
	.asciz	"data3"                         ; string offset=434
	.asciz	"data4"                         ; string offset=440
	.asciz	"uuid"                          ; string offset=446
	.asciz	"time_low"                      ; string offset=451
	.asciz	"time_mid"                      ; string offset=460
	.asciz	"time_hi_and_version"           ; string offset=469
	.asciz	"clock_seq_hi_and_reserved"     ; string offset=489
	.asciz	"clock_seq_low"                 ; string offset=515
	.asciz	"node"                          ; string offset=529
	.asciz	"od"                            ; string offset=534
	.asciz	"method"                        ; string offset=537
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
	.long	2                               ; Bucket 2
	.long	3                               ; Bucket 3
	.long	1516113828                      ; Hash in Bucket 0
	.long	-1513597067                     ; Hash in Bucket 1
	.long	1521316802                      ; Hash in Bucket 2
	.long	1649960099                      ; Hash in Bucket 3
.set Lset6, LNames3-Lnames_begin        ; Offset in Bucket 0
	.long	Lset6
.set Lset7, LNames0-Lnames_begin        ; Offset in Bucket 1
	.long	Lset7
.set Lset8, LNames1-Lnames_begin        ; Offset in Bucket 2
	.long	Lset8
.set Lset9, LNames2-Lnames_begin        ; Offset in Bucket 3
	.long	Lset9
LNames3:
	.long	104                             ; Executive_start
	.long	1                               ; Num DIEs
	.long	46
	.long	0
LNames0:
	.long	120                             ; _EXECUTIVE$__start@0.0
	.long	1                               ; Num DIEs
	.long	46
	.long	0
LNames1:
	.long	157                             ; _EXECUTIVE$__syscall@0.0
	.long	1                               ; Num DIEs
	.long	86
	.long	0
LNames2:
	.long	144                             ; ExSystemCall
	.long	1                               ; Num DIEs
	.long	86
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
	.long	11                              ; Header Bucket Count
	.long	11                              ; Header Hash Count
	.long	20                              ; Header Data Length
	.long	0                               ; HeaderData Die Offset Base
	.long	3                               ; HeaderData Atom Count
	.short	1                               ; DW_ATOM_die_offset
	.short	6                               ; DW_FORM_data4
	.short	3                               ; DW_ATOM_die_tag
	.short	5                               ; DW_FORM_data2
	.short	4                               ; DW_ATOM_type_flags
	.short	11                              ; DW_FORM_data1
	.long	0                               ; Bucket 0
	.long	1                               ; Bucket 1
	.long	2                               ; Bucket 2
	.long	-1                              ; Bucket 3
	.long	3                               ; Bucket 4
	.long	-1                              ; Bucket 5
	.long	6                               ; Bucket 6
	.long	7                               ; Bucket 7
	.long	8                               ; Bucket 8
	.long	9                               ; Bucket 9
	.long	10                              ; Bucket 10
	.long	2090147939                      ; Hash in Bucket 0
	.long	789719536                       ; Hash in Bucket 1
	.long	-594775205                      ; Hash in Bucket 2
	.long	290644127                       ; Hash in Bucket 4
	.long	290711645                       ; Hash in Bucket 4
	.long	-104093792                      ; Hash in Bucket 4
	.long	193495088                       ; Hash in Bucket 6
	.long	956781789                       ; Hash in Bucket 7
	.long	-1304652851                     ; Hash in Bucket 8
	.long	2089623292                      ; Hash in Bucket 9
	.long	878862258                       ; Hash in Bucket 10
.set Lset10, Ltypes10-Ltypes_begin      ; Offset in Bucket 0
	.long	Lset10
.set Lset11, Ltypes8-Ltypes_begin       ; Offset in Bucket 1
	.long	Lset11
.set Lset12, Ltypes2-Ltypes_begin       ; Offset in Bucket 2
	.long	Lset12
.set Lset13, Ltypes6-Ltypes_begin       ; Offset in Bucket 4
	.long	Lset13
.set Lset14, Ltypes5-Ltypes_begin       ; Offset in Bucket 4
	.long	Lset14
.set Lset15, Ltypes0-Ltypes_begin       ; Offset in Bucket 4
	.long	Lset15
.set Lset16, Ltypes7-Ltypes_begin       ; Offset in Bucket 6
	.long	Lset16
.set Lset17, Ltypes4-Ltypes_begin       ; Offset in Bucket 7
	.long	Lset17
.set Lset18, Ltypes1-Ltypes_begin       ; Offset in Bucket 8
	.long	Lset18
.set Lset19, Ltypes3-Ltypes_begin       ; Offset in Bucket 9
	.long	Lset19
.set Lset20, Ltypes9-Ltypes_begin       ; Offset in Bucket 10
	.long	Lset20
Ltypes10:
	.long	277                             ; char
	.long	1                               ; Num DIEs
	.long	224
	.short	36
	.byte	0
	.long	0
Ltypes8:
	.long	315                             ; uint8_t
	.long	1                               ; Num DIEs
	.long	524
	.short	22
	.byte	0
	.long	0
Ltypes2:
	.long	337                             ; __ARRAY_SIZE_TYPE__
	.long	1                               ; Num DIEs
	.long	542
	.short	36
	.byte	0
	.long	0
Ltypes6:
	.long	410                             ; uint16_t
	.long	1                               ; Num DIEs
	.long	567
	.short	22
	.byte	0
	.long	0
Ltypes5:
	.long	362                             ; uint32_t
	.long	1                               ; Num DIEs
	.long	549
	.short	22
	.byte	0
	.long	0
Ltypes0:
	.long	323                             ; unsigned char
	.long	1                               ; Num DIEs
	.long	535
	.short	36
	.byte	0
	.long	0
Ltypes7:
	.long	231                             ; int
	.long	1                               ; Num DIEs
	.long	145
	.short	36
	.byte	0
	.long	0
Ltypes4:
	.long	242                             ; ExecutiveEntryParameters
	.long	1                               ; Num DIEs
	.long	157
	.short	19
	.byte	0
	.long	0
Ltypes1:
	.long	371                             ; unsigned int
	.long	1                               ; Num DIEs
	.long	560
	.short	36
	.byte	0
	.long	0
Ltypes3:
	.long	304                             ; UUID
	.long	1                               ; Num DIEs
	.long	272
	.short	23
	.byte	0
	.long	0
Ltypes9:
	.long	419                             ; unsigned short
	.long	1                               ; Num DIEs
	.long	578
	.short	36
	.byte	0
	.long	0
.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
