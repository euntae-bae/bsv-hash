SRC_NAME=Tb.bsv
all: mkTb mkTb.v jhash_sw

mkTb: mkTb.ba
	bsc -sim -o mkTb -e mkTb mkTb.ba

mkTb.ba: $(SRC_NAME) Jhash.bsv
	bsc -sim -u $(SRC_NAME)

mkTb.v: $(SRC_NAME)
	bsc -verilog $(SRC_NAME)

mkJhash.v: Jhash.bsv
	bsc -verilog Jhash.bsv

jhash_sw: jhash_sw.c jhash.c jhash.h
	gcc -o jhash_sw jhash_sw.c jhash.c

clean:
	rm *.bo
	rm mk*
	rm model_*
	rm jhash_sw