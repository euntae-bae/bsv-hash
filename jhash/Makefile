SRC_NAME=Tb.bsv
all: mkTb mkTb.v jhash_sw

mkTb: mkTb.ba
	bsc -sim -o mkTb -e mkTb mkTb.ba

mkTb.ba: $(SRC_NAME)
	bsc -sim -u $(SRC_NAME)

mkTb.v: $(SRC_NAME)
	bsc -verilog $(SRC_NAME)

jhash_sw: jhash_sw.c
	gcc -o jhash_sw jhash_sw.c

clean:
	rm *.bo
	rm mk*
	rm model_*