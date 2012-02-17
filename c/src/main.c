/**
 * Rapid-prototyping protection schemes with IEC 61850
 *
 * Copyright (c) 2012 Steven Blair
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifdef _WIN32
#define WPCAP
#define HAVE_REMOTE
#define WIN32_LEAN_AND_MEAN
#endif

#define TEST_LOCAL_SV_GSE	0
#define TEST_PERFORMANCE	0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#ifdef _WIN32
#include <sys/time.h>
#else
#include <time.h>
#include <unistd.h>
#endif
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#endif


#include "iec61850.h"

#define PI				3.1415926535897932384626433832795
#define TWO_PI			6.283185307179586476925286766559
#define BUFFFER_LENGTH	2048

pcap_t *fp;
char errbuf[PCAP_ERRBUF_SIZE];
unsigned char buf[BUFFFER_LENGTH] = {0};
int len = 0;

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    gse_sv_packet_filter((unsigned char *) pkt_data, header->len);
}

pcap_t *init_pcap() {
	pcap_t *fpl;
    pcap_if_t *alldevs;
    pcap_if_t *used_if;

    /* Retrieve the device list from the local machine */
#ifdef _WIN32
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1) {
        fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
        exit(1);
    }
#else
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
    	fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
    	exit(1);
    }
#endif

    used_if = alldevs;

    // find VirtualBox's "Sun" interface
    /*while (strstr(used_if->description, "Sun") == NULL && used_if->next != NULL) {
    	used_if = used_if->next;
    }*/

    fprintf(stdout, "%s\n", used_if->name);
    fflush(stdout);

	if ((fpl = pcap_open_live(used_if->name,		// name of the device
							 65536,			// portion of the packet to capture. It doesn't matter in this case
							 1,				// promiscuous mode (nonzero means promiscuous)
							 1000,			// read timeout
							 errbuf			// error buffer
							 )) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", alldevs->name);
		exit(2);
	}

    pcap_freealldevs(alldevs);

	return fpl;
}

int main() {
    int len = 0;

	initialise_iec61850();
	fp = init_pcap();

#if TEST_LOCAL_SV_GSE == 1
	srand(time(NULL));
	float valueGSE = (float) rand() / (float) RAND_MAX;
	float valueSV = (float) rand() / (float) RAND_MAX;

	E1Q1SB1.S1.C1.TVTRa_1.Vol.instMag.f = valueGSE;
	len = E1Q1SB1.S1.C1.LN0.ItlPositions.send(buf, 0, 512);
	pcap_sendpacket(fp, buf, len);

	gse_sv_packet_filter(buf, len);
	printf("GSE test: %s\n", D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.E1Q1SB1_C1_Positions.C1_TVTR_1_Vol_instMag.f == valueGSE ? "passed" : "failed");
	fflush(stdout);

	E1Q1SB1.S1.C1.exampleRMXU_1.AmpLocPhsA.instMag.f = valueSV;
	int i = 0;
	for (i = 0; i < E1Q1SB1.S1.C1.LN0.rmxuCB.noASDU; i++) {
		len = E1Q1SB1.S1.C1.LN0.rmxuCB.update(buf);
		pcap_sendpacket(fp, buf, len);

		if (len > 0) {
			gse_sv_packet_filter(buf, len);

			printf("SV test: %s\n", D1Q1SB4.S1.C1.exampleMMXU_1.sv_inputs_rmxuCB.E1Q1SB1_C1_rmxu[15].C1_RMXU_1_AmpLocPhsA.instMag.f == valueSV ? "passed" : "failed");
			fflush(stdout);
		}
	}
	return 0;
#endif

#if TEST_PERFORMANCE == 1
	len = E1Q1SB1.S1.C1.LN0.Performance.send(buf, 0, 512);
	pcap_sendpacket(fp, buf, len);

	gse_sv_packet_filter(buf, len);
	printf("GSE length: %d bytes\n", len);
	fflush(stdout);

	int i = 0;
	for (i = 0; i < E1Q1SB1.S1.C1.LN0.PerformanceSV.noASDU; i++) {
		len = E1Q1SB1.S1.C1.LN0.PerformanceSV.update(buf);
		pcap_sendpacket(fp, buf, len);

		if (len > 0) {
			gse_sv_packet_filter(buf, len);

			printf("SV length: %d bytes\n", len);
			fflush(stdout);
		}
	}
	return 0;
#endif

	while (1) {
		//Receiver
/*
		pcap_loop(fp, 1, packet_handler, NULL);    // capture SV packet
		float gooseIn = D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.E1Q1SB1_C1_Positions.C1_TVTR_1_Vol_instMag.f;
		float svIn = D1Q1SB4.S1.C1.exampleMMXU_1.sv_inputs_rmxuCB.E1Q1SB1_C1_rmxu[15].C1_RMXU_1_AmpLocPhsA.instMag.f;
		printf("GOOSE: %f SV: %f\n", gooseIn, svIn);
		fflush(stdout);
*/
		//Publisher
		float gooseOut = (float) rand() / (float) RAND_MAX;
		float svOut = (float) rand() / (float) RAND_MAX;
		printf("GOOSE: %f SV: %f\n", gooseOut, svOut);
		fflush(stdout);
		E1Q1SB1.S1.C1.TVTRa_1.Vol.instMag.f = gooseOut;
		len = E1Q1SB1.S1.C1.LN0.ItlPositions.send(buf, 1, 512);
		if (pcap_sendpacket(fp, buf, len) != 0) {
			fprintf(stderr,"\nError sending the packet: %s\n", pcap_geterr(fp));
		}
		E1Q1SB1.S1.C1.exampleRMXU_1.AmpLocPhsA.instMag.f = svOut;
		int i;
		for (i = 0; i < E1Q1SB1.S1.C1.LN0.rmxuCB.noASDU; i++) {
			len = E1Q1SB1.S1.C1.LN0.rmxuCB.update(buf);
			if(len > 0) {
				pcap_sendpacket(fp, buf, len);
			}
		}
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}

	pcap_close(fp);

	return 0;
}
