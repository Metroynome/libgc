#ifdef RAC2_PAL
#define Level (0x001a7a78)
#define gameMode (0x001a8fc0)
#define MAINMENU_DETECT_ADDR (0x0026e780)
#define MAINMENU_DETECT_WORD0 (0x3c03001b)
#define MAINMENU_DETECT_WORD1 (0x8c6322a8)
#define MAINMENU_DETECT_WORD2 (0x3c021000)
#define MAINMENU_DETECT_WORD3 (0x34420003)
#elif RAC2_NTSCJ
#define Level (0x001a79f8)
#define gameMode (0x001a8f40)
#define MAINMENU_DETECT_ADDR (0x00272800)
#define MAINMENU_DETECT_WORD0 (0x27bdffe0)
#define MAINMENU_DETECT_WORD1 (0x3c02001c)
#define MAINMENU_DETECT_WORD2 (0xffb00000)
#define MAINMENU_DETECT_WORD3 (0x2442adc0)
#elif RAC2_NTSCU_V200
#define Level (0x001a79f8)
#define gameMode (0x001a8f40)
#define MAINMENU_DETECT_ADDR (0x0026ea00)
#define MAINMENU_DETECT_WORD0 (0x27bdffe0)
#define MAINMENU_DETECT_WORD1 (0x3c02001c)
#define MAINMENU_DETECT_WORD2 (0xffb00000)
#define MAINMENU_DETECT_WORD3 (0x2442ae40)
#else
#define Level (0x001a79f0)
#define gameMode (0x001a8f40)
#define MAINMENU_DETECT_ADDR (0x0026ea00)
#define MAINMENU_DETECT_WORD0 (0x27bdffe0)
#define MAINMENU_DETECT_WORD1 (0x3c02001c)
#define MAINMENU_DETECT_WORD2 (0xffb00000)
#define MAINMENU_DETECT_WORD3 (0x2442aec0)
#endif

#define CHECK_MAINMENU_ADDRESS(exit_label, miss_label) \
	lw $v0, MAINMENU_DETECT_ADDR; \
	li $v1, MAINMENU_DETECT_WORD0; \
	bne $v0, $v1, miss_label; \
	nop; \
	lw $v0, MAINMENU_DETECT_ADDR + 4; \
	li $v1, MAINMENU_DETECT_WORD1; \
	bne $v0, $v1, miss_label; \
	nop; \
	lw $v0, MAINMENU_DETECT_ADDR + 8; \
	li $v1, MAINMENU_DETECT_WORD2; \
	bne $v0, $v1, miss_label; \
	nop; \
	lw $v0, MAINMENU_DETECT_ADDR + 12; \
	li $v1, MAINMENU_DETECT_WORD3; \
	bne $v0, $v1, miss_label; \
	nop; \
	lw $v0, 0x0($a0); \
	b exit_label; \
	nop; \
miss_label:

// fixed address function
#define FUNCTION(name, address) \
	.set	push;		        \
	.set	noreorder;	        \
	.section	.text.##name,"ax",@progbits; \
	.align 2;		            \
	.globl	name;		        \
	.type	name,@function;	    \
	.ent	name,0;		        \
name:	j address;              \
	nop;			            \
	.end	name;		        \
	.size	name,.-name;	    \
	.set	pop;

// variable address function
#define VARIABLE_FUNCTION(name, variable_address_struct) \
	.set	push;		        				\
	.set	noreorder;	        		\
	.section	.text.##name,"ax",@progbits; \
	.align 2;		            			\
	.globl	name;		        			\
	.type	name,@function;	    		\
	.ent	name,0;		        			\
	.extern variable_address_struct; \
name:														\
		addiu $sp, $sp, -0x40;			\
		sq $ra, 0x00($sp);					\
		sq $a0, 0x10($sp);					\
		sq $a1, 0x20($sp);					\
		sq $s0, 0x30($sp);					\
		la $a0, variable_address_struct; \
		la $a1, ##name##_return;				\
		j __LocalGetAddress;        \
		nop;			            			\
##name##_return:										\
		beq $zero, $v0, ##name##_exit;	\
		nop;												\
		lq $a1, 0x20($sp);					\
		jalr $v0;										\
		lq $a0, 0x10($sp);					\
##name##_exit:											\
		lq $ra, 0x00($sp);					\
		lq $s0, 0x30($sp);					\
		jr $ra;											\
		addiu $sp, $sp, 0x40;				\
	.end	name;		        				\
	.size	name,.-name;	   			 	\
	.set	pop;

// 
	.set	push;
	.set	noreorder;
	.section	.text.##__LocalGetAddress,"ax",@progbits;
	.align 2;
	.globl	__LocalGetAddress;
	.type	__LocalGetAddress,@function;
	.ent	__LocalGetAddress,0;
__LocalGetAddress:
	// MainMenu is level -1 and can leave Level with a stale normal level value.
	CHECK_MAINMENU_ADDRESS(__LocalGetAddress_exit, __LocalGetAddress_not_mainmenu)

	// if scene is loading, then we have no address
	li $v1, 1;
	lw $v0, SCENE_LOADED;
	bne $v0, $v1, __LocalGetAddress_exit;
	li $v0, 0;

	// if not in game then no address
	lw $v0, GAME_ACTIVE;
	beq $v0, $zero, __LocalGetAddress_exit;
	move $v0, $zero;

	// Return address by RAC2 level id.
	// VariableAddress_t order is: MainMenu, 0..20, 22..26, then Museum (30).
	lw $v0, GAME_MAP_ID;
	li $v1, 30;
	beq $v0, $v1, __LocalGetAddress_museum;
	nop;

	// valid level ids 0..20 map to table index 1..21
	sltiu $v1, $v0, 21;
	bne $v1, $zero, __LocalGetAddress_load;
	move $v1, $v0;

	// valid level ids 22..26 map to table index 22..26
	addiu $v1, $v0, -22;
	sltiu $v0, $v1, 5;
	beqzl $v0, __LocalGetAddress_exit;
	move $v0, $zero;
	addiu $v1, $v1, 22;
	b __LocalGetAddress_load_indexed;
	nop;

__LocalGetAddress_museum:
	li $v1, 27;
	b __LocalGetAddress_load_indexed;
	nop;

__LocalGetAddress_load:
	addiu $v1, $v1, 1;
__LocalGetAddress_load_indexed:
	sll $v1, $v1, 2;
	addu $a0, $v1;
	lw $v0, 0($a0);

	// return to calling function
__LocalGetAddress_exit:
	jr $a1;
	nop;
	.end	__LocalGetAddress;
	.size	__LocalGetAddress,.-__LocalGetAddress;
	.set	pop;

// 
	.set	push;
	.set	noreorder;
	.section	.text.##GetAddress,"ax",@progbits;
	.align 2;
	.globl	GetAddress;
	.type	GetAddress,@function;
	.ent	GetAddress,0;
GetAddress:
	// MainMenu is level -1 and can leave Level with a stale normal level value.
	CHECK_MAINMENU_ADDRESS(GetAddress_exit, GetAddress_not_mainmenu)

	// if scene is loading, then we have no address
	li $v1, 1;
	lw $v0, SCENE_LOADED;
	bne $v0, $v1, GetAddress_exit;
	li $v0, 0;

	// if not in game then no address
	lw $v0, GAME_ACTIVE;
	beq $v0, $zero, GetAddress_exit;
	move $v0, $zero;

	// Return address by RAC2 level id.
	// VariableAddress_t order is: MainMenu, 0..20, 22..26, then Museum (30).
	lw $v0, GAME_MAP_ID;
	li $v1, 30;
	beq $v0, $v1, GetAddress_museum;
	nop;

	// valid level ids 0..20 map to table index 1..21
	sltiu $v1, $v0, 21;
	bne $v1, $zero, GetAddress_load;
	move $v1, $v0;

	// valid level ids 22..26 map to table index 22..26
	addiu $v1, $v0, -22;
	sltiu $v0, $v1, 5;
	beqzl $v0, GetAddress_exit;
	move $v0, $zero;
	addiu $v1, $v1, 22;
	b GetAddress_load_indexed;
	nop;

GetAddress_museum:
	li $v1, 27;
	b GetAddress_load_indexed;
	nop;

GetAddress_load:
	addiu $v1, $v1, 1;
GetAddress_load_indexed:
	sll $v1, $v1, 2;
	addu $a0, $v1;
	lw $v0, 0($a0);

	// return to calling function
GetAddress_exit:
	jr $ra;
	nop;
	.end	GetAddress;
	.size	GetAddress,.-GetAddress;
	.set	pop;

// 
	.set	push;
	.set	noreorder;
	.section	.text.##GetAddress,"ax",@progbits;
	.align 2;
	.globl	GetAddressImmediate;
	.type	GetAddressImmediate,@function;
	.ent	GetAddressImmediate,0;
GetAddressImmediate:
	// MainMenu is level -1 and can leave Level with a stale normal level value.
	CHECK_MAINMENU_ADDRESS(GetAddressImmediate_exit, GetAddressImmediate_not_mainmenu)

	// if scene is loading, then we have no address
	//li $v1, 1;
	//lw $v0, SCENE_LOADED;
	//bne $v0, $v1, GetAddressImmediate_exit;
	//li $v0, 0;

	// if not in game then no address
	//lw $v0, GAME_ACTIVE;
	//beq $v0, $zero, GetAddressImmediate_exit;
	//nop;

	// Return address by RAC2 level id.
	// VariableAddress_t order is: MainMenu, 0..20, 22..26, then Museum (30).
	lw $v0, GAME_MAP_ID;
	li $v1, 30;
	beq $v0, $v1, GetAddressImmediate_museum;
	nop;

	// valid level ids 0..20 map to table index 1..21
	sltiu $v1, $v0, 21;
	bne $v1, $zero, GetAddressImmediate_load;
	move $v1, $v0;

	// valid level ids 22..26 map to table index 22..26
	addiu $v1, $v0, -22;
	sltiu $v0, $v1, 5;
	beqzl $v0, GetAddressImmediate_exit;
	move $v0, $zero;
	addiu $v1, $v1, 22;
	b GetAddressImmediate_load_indexed;
	nop;

GetAddressImmediate_museum:
	li $v1, 27;
	b GetAddressImmediate_load_indexed;
	nop;

GetAddressImmediate_load:
	addiu $v1, $v1, 1;
GetAddressImmediate_load_indexed:
	sll $v1, $v1, 2;
	addu $a0, $v1;
	lw $v0, 0($a0);

	// return to calling function
GetAddressImmediate_exit:
	jr $ra;
	nop;
	.end	GetAddressImmediate;
	.size	GetAddressImmediate,.-GetAddressImmediate;
	.set	pop;


// 
	.set	push;
	.set	noreorder;
	.section	.text.##IsMainMenu,"ax",@progbits;
	.align 2;
	.globl	IsMainMenu;
	.type	IsMainMenu,@function;
	.ent	IsMainMenu,0;
IsMainMenu:
	lw $v0, MAINMENU_DETECT_ADDR;
	li $v1, MAINMENU_DETECT_WORD0;
	bne $v0, $v1, IsMainMenu_no;
	nop;
	lw $v0, MAINMENU_DETECT_ADDR + 4;
	li $v1, MAINMENU_DETECT_WORD1;
	bne $v0, $v1, IsMainMenu_no;
	nop;
	lw $v0, MAINMENU_DETECT_ADDR + 8;
	li $v1, MAINMENU_DETECT_WORD2;
	bne $v0, $v1, IsMainMenu_no;
	nop;
	lw $v0, MAINMENU_DETECT_ADDR + 12;
	li $v1, MAINMENU_DETECT_WORD3;
	bne $v0, $v1, IsMainMenu_no;
	nop;
	li $v0, 1;
	jr $ra;
	nop;
IsMainMenu_no:
	jr $ra;
	move $v0, $zero;
	.end	IsMainMenu;
	.size	IsMainMenu,.-IsMainMenu;
	.set	pop;

#--------------------------------------------------------
#------------------- STANDARD LIBRARY -------------------
#--------------------------------------------------------
FUNCTION(printf, 0x0011c1f8)
FUNCTION(sprintf, 0x00118cc8)
FUNCTION(memset, 0x00115484)
FUNCTION(memcpy, 0x001153d4)
FUNCTION(strncpy, 0x00115ac0)
FUNCTION(strcmp, 0x00008f998)
FUNCTION(strncmp, 0x001158f8)
#FUNCTION(strlen, 0x0008fadc)

#--------------------------------------------------------
#------------------------ RANDOM ------------------------
#--------------------------------------------------------
FUNCTION(randSeed, 0x001163b0)
