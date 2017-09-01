add $s0, $zero, $zero
add $t5, $s0, $a0
CHEESE: addi $t5, $s2, -11
addi $t0, $t4, -9874
addi $t2, $s2, 90
addiu $t2, $s2, 90
addu $t4, $t5, $t0
and $s0, $s1, $a0
jal CHEESE
jr $ra
lw $a0, 4($t5)
andi $t0, $t7, 8
beq $zero, $zero, TERRY
beq $zero, $zero, EXIT
bne $t0, $t1, LOOP
j TERRY
LOOP: slti $t0, $s0, 200
addi $t1, $s0, 2
nor $t5, $t6, $t7
or $s0, $s1, $a0
ori $k0, $ra, 6
slt $t5, $t6, $t0
slti $t1, $t2, -8
sltiu $t5, $s0, 9
sltu $s0, $zero, $ra
sll $t2, $s0, 2
srl $s0, $s1, 1
add $t2, $s1, $t2
sw $t1, 0($t2)
addi $s0, $s0, 1
lw $a0, 4($t5)
lw $a0, 4($t5)
j LOOP
sub $t5, $t6, $s0
subu $s0, $s1, $t4
jal TERRY
EXIT:
TERRY:
