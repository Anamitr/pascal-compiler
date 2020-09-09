#!/bin/bash
function run_test () {
  arr=("$@")
#  printf "%s\n" "${arr[@]}"

  for prog in "${arr[@]}";
  do
#    echo $prog
    ./pascal-compiler testing/exp_pas/$prog.pas testing/mine_out/$prog.asm &&
      #t0="$(cat mine_out/t0.asm | awk -F';' '{print $1}' | tr -d '[:space:]')"
    mt0=`cat testing/mine_out/$prog.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
    #echo $mt0
    gt0=`cat testing/gj_out/$prog.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
    #echo $gt0
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
run_test "${programArray[@]}"




#cat t0.asm

