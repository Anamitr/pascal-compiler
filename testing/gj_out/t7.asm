        jump.i  #lab0                   ;jump.i  lab0
f:
        enter.i #4                      ;enter.i 4
        add.i   *BP+16,#10,BP-4         ;add.i   a,10,$t0
        mov.i   BP-4,*BP+8              ;mov.i   $t0,f
        leave                           ;leave   
        return                          ;return  
lab0:
        inttoreal.i #1,24               ;inttoreal.i 1,$t1
        mov.r   24,8                    ;mov.r   $t1,g
        mov.i   #2,0                    ;mov.i   2,x
        realtoint.r 8,32                ;realtoint.r g,$t2
        push.i  #32                     ;push.i  &$t2
        inttoreal.i 0,36                ;inttoreal.i x,$t3
        push.i  #36                     ;push.i  &$t3
        push.i  #44                     ;push.i  &$t4
        call.i  #f                      ;call.i  &f
        incsp.i #12                     ;incsp.i 12
        mov.i   44,0                    ;mov.i   $t4,x
        write.i 0                       ;write.i x
        exit                            ;exit    
