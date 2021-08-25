#set_property IOSTANDARD LVCMOS33 [get_ports {led[*]}]
# put leds on PMOD connector for now. There are no LEDs on the carrier board.
#set_property PACKAGE_PIN C11 [get_ports {led[3]}]
#set_property PACKAGE_PIN D10 [get_ports {led[2]}]
#set_property PACKAGE_PIN E10 [get_ports {led[1]}]
#set_property PACKAGE_PIN H12 [get_ports {led[0]}]

set_property IOSTANDARD LVCMOS18 [get_ports {led[*]}]
#set_property PACKAGE_PIN T5  [get_ports {led[7]}]; #JX1_HP_DP_24_P 81 
#set_property PACKAGE_PIN T4  [get_ports {led[6]}]; #JX1_HP_DP_24_N 83
#set_property PACKAGE_PIN R7  [get_ports {led[5]}]; #JX1_HP_DP_25_P 80 
#set_property PACKAGE_PIN T7  [get_ports {led[4]}]; #JX1_HP_DP_25_N 82 
set_property PACKAGE_PIN U6  [get_ports {led[3]}]; #JX1_HP_DP_26_P 87 
set_property PACKAGE_PIN U5  [get_ports {led[2]}]; #JX1_HP_DP_26_N 89 
set_property PACKAGE_PIN T3  [get_ports {led[1]}]; #JX1_HP_DP_27_P 86 
set_property PACKAGE_PIN U2  [get_ports {led[0]}]; #JX1_HP_DP_27_N 88
