        jump.i  #lab0                   ;jump.i  lab0
f:
        enter.i #32                     ;enter.i 32
        add.i   *BP+16,#10,BP-4         ;add.i   a,10,$t0
        mul.r   #3.5,*BP+12,BP-12       ;mul.r   3.5,b,$t1
        inttoreal.i BP-4,BP-20          ;inttoreal.i $t0,$t2
        add.r   BP-20,BP-12,BP-28       ;add.r   $t2,$t1,$t3
        realtoint.r BP-28,BP-32         ;realtoint.r $t3,$t4
        mov.i   BP-32,*BP+8             ;mov.i   $t4,f
        leave                           ;leave   
        return                          ;return  
lab0:
        mov.i   #3,24                   ;mov.i   3,$t5
        push.i  #24                     ;push.i  &$t5
        mov.r   #12,28                  ;mov.r   12,$t6
        push.i  #28                     ;push.i  &$t6
        push.i  #36                     ;push.i  &$t7
        call.i  #f                      ;call.i  &f
        incsp.i #12                     ;incsp.i 12
        mov.i   36,0                    ;mov.i   $t7,x
        write.i 0                       ;write.i x
        exit                            ;exit    
