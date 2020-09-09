        jump.i  #lab0                   ;jump.i  lab0
f:
        enter.i #4                      ;enter.i 4
        add.i   *BP+16,#10,BP-4         ;add.i   a,10,$t0
        mov.i   BP-4,*BP+8              ;mov.i   $t0,f
        leave                           ;leave   
        return                          ;return  
p:
        enter.i #12                     ;enter.i 12
        add.i   *BP+12,#10,BP-4         ;add.i   a,10,$t1
        inttoreal.i BP-4,BP-12          ;inttoreal.i $t1,$t2
        mov.r   BP-12,*BP+8             ;mov.r   $t2,b
        leave                           ;leave   
        return                          ;return  
lab0:
        realtoint.r 8,24                ;realtoint.r g,$t3
        push.i  #24                     ;push.i  &$t3
        inttoreal.i 0,28                ;inttoreal.i x,$t4
        push.i  #28                     ;push.i  &$t4
        call.i  #p                      ;call.i  &p
        incsp.i #8                      ;incsp.i 8
        push.i  #0                      ;push.i  &x
        push.i  #8                      ;push.i  &g
        push.i  #36                     ;push.i  &$t5
        call.i  #f                      ;call.i  &f
        incsp.i #12                     ;incsp.i 12
        mov.i   36,0                    ;mov.i   $t5,x
        exit                            ;exit    
