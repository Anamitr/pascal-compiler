#!/bin/bash


function compile_and_test () {
  arr=("$@")

  for prog in "${arr[@]}";
  do
    ./pascal-compiler testing/exp_pas/$prog.pas testing/mine_out/$prog.asm
  done

  for prog in "${arr[@]}";
  do
    if [ "$should_print_output" = true ] ; then
      cat testing/mine_out/$prog.asm
    fi
    mt0=`cat testing/mine_out/$prog.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
    gt0=`cat testing/gj_out/$prog.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
    if [ $mt0 = $gt0 ]; then
      echo $prog correct
    else
      echo $prog not correct!
    fi
  done
}

# Arrays are not implemented, so t9 is skipped
# t13, t14 may be infinite loop

programArray=(t0 t1 t2 t3 t4 t5 t6 t7 t8 t10 t11 t12 t13 t14 arithtest gcd)
#programArray=(arithtest)
should_print_output=false
#should_print_output=true

make clean
set -e
make
printf "\nTests:\n"
compile_and_test "${programArray[@]}"
