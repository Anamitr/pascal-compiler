        jump.i  #lab0                   ;jump.i  lab0
lab0:
        sub.i   #3,#1,96                ;sub.i   3,1,$t0
        mul.i   96,#8,96                ;mul.i   $t0,8,$t0
        add.i   #12,96,100              ;add.i   &p,$t0,$t1
        mov.r   #10,*100                ;mov.r   10,$t1
        sub.i   #7,#1,104               ;sub.i   7,1,$t2
        mul.i   104,#8,104              ;mul.i   $t2,8,$t2
        add.i   #12,104,108             ;add.i   &p,$t2,$t3
        mov.r   #7,*108                 ;mov.r   7,$t3
        sub.i   #5,#1,112               ;sub.i   5,1,$t4
        mul.i   112,#8,112              ;mul.i   $t4,8,$t4
        add.i   #12,112,116             ;add.i   &p,$t4,$t5
        write.r *116                    ;write.r $t5
        exit                            ;exit    
