        jump.i  #lab0                   ;jump.i  lab0
czytajtab:
        enter.i #20                     ;enter.i 20
        mov.i   #1,BP-4                 ;mov.i   1,i
lab2:
        jl.i    BP-4,#11,#lab3          ;jl.i    i,11,lab3
        mov.i   #0,BP-8                 ;mov.i   0,$t0
        jump.i  #lab4                   ;jump.i  lab4
lab3:
        mov.i   #1,BP-8                 ;mov.i   1,$t0
lab4:
        je.i    BP-8,#0,#lab1           ;je.i    $t0,0,lab1
        sub.i   BP-4,#1,BP-12           ;sub.i   i,1,$t1
        mul.i   BP-12,#8,BP-12          ;mul.i   $t1,8,$t1
        add.i   BP+8,BP-12,BP-16        ;add.i   &a,$t1,$t2
        read.r  *BP-16                  ;read.r  $t2
        add.i   BP-4,#1,BP-20           ;add.i   i,1,$t3
        mov.i   BP-20,BP-4              ;mov.i   $t3,i
        jump.i  #lab2                   ;jump.i  lab2
lab1:
        leave                           ;leave   
        return                          ;return  
bubblesort:
        enter.i #88                     ;enter.i 88
        mov.i   #1,BP-4                 ;mov.i   1,i
lab6:
        jl.i    BP-4,#11,#lab7          ;jl.i    i,11,lab7
        mov.i   #0,BP-20                ;mov.i   0,$t4
        jump.i  #lab8                   ;jump.i  lab8
lab7:
        mov.i   #1,BP-20                ;mov.i   1,$t4
lab8:
        je.i    BP-20,#0,#lab5          ;je.i    $t4,0,lab5
        add.i   BP-4,#1,BP-24           ;add.i   i,1,$t5
        mov.i   BP-24,BP-8              ;mov.i   $t5,j
lab10:
        jl.i    BP-8,#11,#lab11         ;jl.i    j,11,lab11
        mov.i   #0,BP-28                ;mov.i   0,$t6
        jump.i  #lab12                  ;jump.i  lab12
lab11:
        mov.i   #1,BP-28                ;mov.i   1,$t6
lab12:
        je.i    BP-28,#0,#lab9          ;je.i    $t6,0,lab9
        sub.i   BP-4,#1,BP-32           ;sub.i   i,1,$t7
        mul.i   BP-32,#8,BP-32          ;mul.i   $t7,8,$t7
        add.i   BP+8,BP-32,BP-36        ;add.i   &a,$t7,$t8
        sub.i   BP-8,#1,BP-40           ;sub.i   j,1,$t9
        mul.i   BP-40,#8,BP-40          ;mul.i   $t9,8,$t9
        add.i   BP+8,BP-40,BP-44        ;add.i   &a,$t9,$t10
        jg.r    *BP-36,*BP-44,#lab13    ;jg.r    $t8,$t10,lab13
        mov.i   #0,BP-48                ;mov.i   0,$t11
        jump.i  #lab14                  ;jump.i  lab14
lab13:
        mov.i   #1,BP-48                ;mov.i   1,$t11
lab14:
        je.i    BP-48,#0,#lab15         ;je.i    $t11,0,lab15
        sub.i   BP-4,#1,BP-52           ;sub.i   i,1,$t12
        mul.i   BP-52,#8,BP-52          ;mul.i   $t12,8,$t12
        add.i   BP+8,BP-52,BP-56        ;add.i   &a,$t12,$t13
        mov.r   *BP-56,BP-16            ;mov.r   $t13,tmp
        sub.i   BP-4,#1,BP-60           ;sub.i   i,1,$t14
        mul.i   BP-60,#8,BP-60          ;mul.i   $t14,8,$t14
        add.i   BP+8,BP-60,BP-64        ;add.i   &a,$t14,$t15
        sub.i   BP-8,#1,BP-68           ;sub.i   j,1,$t16
        mul.i   BP-68,#8,BP-68          ;mul.i   $t16,8,$t16
        add.i   BP+8,BP-68,BP-72        ;add.i   &a,$t16,$t17
        mov.r   *BP-72,*BP-64           ;mov.r   $t17,$t15
        sub.i   BP-8,#1,BP-76           ;sub.i   j,1,$t18
        mul.i   BP-76,#8,BP-76          ;mul.i   $t18,8,$t18
        add.i   BP+8,BP-76,BP-80        ;add.i   &a,$t18,$t19
        mov.r   BP-16,*BP-80            ;mov.r   tmp,$t19
        jump.i  #lab16                  ;jump.i  lab16
lab15:
lab16:
        add.i   BP-8,#1,BP-84           ;add.i   j,1,$t20
        mov.i   BP-84,BP-8              ;mov.i   $t20,j
        jump.i  #lab10                  ;jump.i  lab10
lab9:
        add.i   BP-4,#1,BP-88           ;add.i   i,1,$t21
        mov.i   BP-88,BP-4              ;mov.i   $t21,i
        jump.i  #lab6                   ;jump.i  lab6
lab5:
        leave                           ;leave   
        return                          ;return  
wypisztab:
        enter.i #20                     ;enter.i 20
        mov.i   #1,BP-4                 ;mov.i   1,i
lab18:
        jl.i    BP-4,#11,#lab19         ;jl.i    i,11,lab19
        mov.i   #0,BP-8                 ;mov.i   0,$t22
        jump.i  #lab20                  ;jump.i  lab20
lab19:
        mov.i   #1,BP-8                 ;mov.i   1,$t22
lab20:
        je.i    BP-8,#0,#lab17          ;je.i    $t22,0,lab17
        sub.i   BP-4,#1,BP-12           ;sub.i   i,1,$t23
        mul.i   BP-12,#8,BP-12          ;mul.i   $t23,8,$t23
        add.i   BP+8,BP-12,BP-16        ;add.i   &a,$t23,$t24
        write.r *BP-16                  ;write.r $t24
        add.i   BP-4,#1,BP-20           ;add.i   i,1,$t25
        mov.i   BP-20,BP-4              ;mov.i   $t25,i
        jump.i  #lab18                  ;jump.i  lab18
lab17:
        leave                           ;leave   
        return                          ;return  
lab0:
        push.i  #12                     ;push.i  &p
        call.i  #czytajtab              ;call.i  &czytajtab
        incsp.i #4                      ;incsp.i 4
        push.i  #12                     ;push.i  &p
        call.i  #bubblesort             ;call.i  &bubblesort
        incsp.i #4                      ;incsp.i 4
        push.i  #12                     ;push.i  &p
        call.i  #wypisztab              ;call.i  &wypisztab
        incsp.i #4                      ;incsp.i 4
        exit                            ;exit    
