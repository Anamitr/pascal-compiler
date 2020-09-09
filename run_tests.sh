make clean ; make &&
./pascal-compiler testing/exp_pas/t0.pas testing/mine_out/t0.asm &&

cd testing/mine_out
cat t0.asm

# TODO: straighten headers

# If there are missing references perhaps you forgot to add File.o to main
# pascal compiler target