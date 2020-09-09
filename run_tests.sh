#!/bin/bash
function compile_and_test () {
  arr=("$@")

  for prog in "${arr[@]}";
  do
    ./pascal-compiler testing/exp_pas/$prog.pas testing/mine_out/$prog.asm
  done

  for prog in "${arr[@]}";
  do
    mt0=`cat testing/mine_out/$prog.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
    gt0=`cat testing/gj_out/$prog.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
    if [ $mt0 = $gt0 ]; then
      echo $prog correct
    else
      echo $prog not correct!
    fi
  done
}

programArray=(t0 t1)

make clean ; make
printf "\nTests:\n"

#printf "%s\n" "${programArray[@]}"
#cd testing
compile_and_test "${programArray[@]}"




#cat t0.asm

