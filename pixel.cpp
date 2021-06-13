#include <stdio.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include<math.h>

using namespace std;

typedef ap_axis<32,0,0,0> pkt_t;
static int count_streams = 0;
static long long charIn=0;
int addNum=0;

long long toAscii(int number);
long long convert(int n);
int convertBinInt(long long n);


void pixel(
		ap_int<32> position1,
		ap_int<32> position2,
		ap_int<32> stream_count,
		ap_int<32> ascii,
		hls::stream< pkt_t > &din,
		hls::stream< pkt_t > &dout
) {
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE s_axilite port=position1
	#pragma HLS INTERFACE s_axilite port=position2
	#pragma HLS INTERFACE s_axilite port=stream_count
	#pragma HLS INTERFACE s_axilite port=ascii
	#pragma HLS INTERFACE axis port=din
	#pragma HLS INTERFACE axis port=dout

	pkt_t pkt=din.read();
    if (count_streams == 0){
        charIn=toAscii(ascii);
    }

    if((count_streams >= 3 * (position1 - 1)) && (count_streams < 3 * (position2))&& (charIn!=0)){

        addNum=charIn%10;
		charIn=(int)charIn/10;

        pkt.data=charIn;

    }


	count_streams++;

	if (count_streams == stream_count){
		count_streams = 0;
        charIn=0;
        addNum=0;

	}

    dout.write(pkt);
}


long long convert(int n) {
    long long bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0) {
        rem = n % 2;
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}

int convertBinInt(long long n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}

long long toAscii(int c) {
    long long bin = convert(c);
    return bin;
}
