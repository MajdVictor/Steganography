#include <iostream>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

using namespace std;

typedef ap_axis<32,0,0,0> pkt_t; 



void pixel(

		hls::stream< pkt_t > &din,
		hls::stream< pkt_t > &dout

) {
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis port=din
	#pragma HLS INTERFACE axis port=dout

	pkt_t pkt;
	din.read(pkt);
    if(pkt.data == 1){
		pkt.data = 215;
	}
	if(pkt.data == 215){
		pkt.data = 1;
	}       

	dout.write(pkt);
}

