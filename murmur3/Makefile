SRC_NAME=Tb.bsv
all: mkTb mkTb.v mkMurmur3.v murmur_sw

mkTb: mkTb.ba
	bsc -sim -o mkTb -e mkTb mkTb.ba

mkTb.ba: $(SRC_NAME) Murmur3.bsv
	bsc -sim -u $(SRC_NAME)

mkTb.v: $(SRC_NAME)
	bsc -verilog $(SRC_NAME)

mkMurmur3.v: Murmur3.bsv
	bsc -verilog Murmur3.bsv

murmur_sw: murmur_sw.c
	gcc -o murmur_sw murmur_sw.c

clean:
	rm *.bo
	rm mk*
	rm model_*