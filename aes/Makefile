SRC_NAME=Tb.bsv
all: mkTb mkTb.v sbox aes128sw.c

sbox: sbox.c
	gcc -o sbox sbox.c

aes128sw: aes128sw.c
	gcc -o aes128sw aes128sw.c

mkTb: mkTb.ba
	bsc -sim -o mkTb -e mkTb mkTb.ba

mkTb.ba: $(SRC_NAME)
	bsc -sim -u $(SRC_NAME)

mkTb.v: $(SRC_NAME)
	bsc -verilog $(SRC_NAME)

clean:
	rm *.bo
#	rm mkTb*
	rm mk*
	rm model_*