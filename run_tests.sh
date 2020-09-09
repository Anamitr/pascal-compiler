make clean ;
make &&
./pascal-compiler testing/exp_pas/t0.pas testing/mine_out/t0.asm &&

echo "\nTests:"
cd testing
#t0="$(cat mine_out/t0.asm | awk -F';' '{print $1}' | tr -d '[:space:]')"
mt0=`cat mine_out/t0.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
#echo $mt0
gt0=`cat gj_out/t0.asm | awk -F';' '{print $1}' | tr -d '[:space:]'`
#echo $gt0
if [ $mt0 = $gt0 ]; then
  echo t0 correct
else
  echo t0 not correct!
fi


#cat t0.asm

