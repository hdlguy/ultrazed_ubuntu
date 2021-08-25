#define		BASE_ADDRESS		0x80000000
#define		PROTO_SIZE		0x40000000

#define 	REGFILE_OFFSET		0x00000000

#define 	FPGA_ID     		REGFILE_OFFSET+0x04*0  // Currently returns 0xDEADBEEF
#define 	FPGA_VERSION		REGFILE_OFFSET+0x04*1  // Returns major and minor version numbers.
#define 	LED_CONTROL		REGFILE_OFFSET+0x04*2  // Returns major and minor version numbers.


    
    // assign ap_start = slv_reg[4][0]; 
//#define 	MATINV_CONTROL		AXI_REGFILE_0+0x04*4  // Returns major and minor version numbers.

    // assign slv_read[5][0] = ap_done;
    // assign slv_read[5][4] = ap_idle;
    // assign slv_read[5][8] = ap_ready;
//#define 	MATINV_STATUS           AXI_REGFILE_0+0x04*5  // Returns major and minor version numbers.
    
    // assign slv_read[6] = ap_return;
//#define 	MATINV_RETURN           AXI_REGFILE_0+0x04*6  // Returns major and minor version numbers.

#define         TEST_BRAM_OFFSET    0x20000000
#define         TEST_BRAM_SIZE      0x00001000 // 4KB

//#define         MATINV_IBRAM        0x00020000 // This is the input bram of the matrix inverter.
//#define         MATINV_OBRAM        0x00030000 // This is the output bram of the matrix inverter.


#define         ULTRA_RAM_OFFSET      0x01000000 // Ultraram
#define         ULTRA_RAM_SIZE        0x00200000 // 32K

