make clean ; make &&
./pascal-compiler testing/exp_pas/t0.pas &&
cat out.asm

# TODO: straighten headers

# If there are missing references perhaps you forgot to add File.o to main
# pascal compiler target