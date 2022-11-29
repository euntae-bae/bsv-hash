SRC_NAME=Tb.bsv
all: mkTb mkTb.v #murmur_sw

mkTb: mkTb.ba
	bsc -sim -o mkTb -e mkTb mkTb.ba

mkTb.ba: $(SRC_NAME)
	bsc -sim -u $(SRC_NAME)

mkTb.v: $(SRC_NAME)
	bsc -verilog $(SRC_NAME)

murmur_sw: murmur_sw.c
	gcc -o murmur_sw murmur_sw.c

clean:
	rm *.bo
	rm mk*
	rm model_*