These instructions provide an outline of the steps required to boot Ubuntu Linux on the Xilinx Kria KV260 evaluation board.

- Download and install Xilinx Petalinux 2021.1. See "PetaLinux Tools Documentation Reference Guide", (UG1144).

    NOTE: there was an error in the installation instructions for Ubuntu. You need to install the gawk package not awk.

- Set up your environment variables. Something like this depending on where you installed Petalinux.

    source ~/xilinx/PetaLinux/2021.1/tool/settings.sh


- Download the the kria Petalinux BSP from here

    https://www.xilinx.com/member/forms/download/xef.html?filename=xilinx-k26-som-v2021.1-updated-final.bsp

    Put it somewhere it can be accessed in the next command.

- Now create the petalinux project. (Note: the BSP file name changes with version.)

    petalinux-create --force --type project --template zynqMP --source ~/Downloads/xilinx/zcu104/xilinx-zcu104-v2019.2-final.bsp --name proj1

- Now configure the petalinux project with the settings we need to run Ubuntu from the SD card.

    cd proj1

    petalinux-config --get-hw-description=~/github/zcu104_ubuntu/fpga/implement/results/

- This will bring up a configuration menu.  Make the following changes.

    * Under "Image Packaging Configuration" -> 
        "Root filesystem type" -> 
        Select "SD Card"
    * Under "DTG Settings" -> 
        "Kernel Bootargs" -> 
        Un-select "generate boot args automatically" -> 
        Enter "user set kernel bootargs" -> Paste in the following line
            earlycon clk_ignore_unused earlyprintk root=/dev/mmcblk0p2 rw rootwait cma=1024M
    * Save and exit the configuration menu. Wait for configuration to complete.

- Now edit a file to patch a bug in the Petalinux BSP for the zcu104. (I don't know if this is still necessary.)

    vim project-spec/meta-user/conf/petalinuxbsp.conf

    * Add the followint line
        IMAGE_INSTALL_remove = "gstreamer-vcu-examples"

- Now build the bootloader

    petalinux-build -c bootloader -x distclean

- Now run another configu menu.

    petalinux-config --silentconfig -c kernel
    
- Now build the linux kernel

    petalinux-build

    It takes a while to run.

- Now create the boot files that u-boot expects. 

    petalinux-package --force --boot --fsbl images/linux/zynqmp_fsbl.elf --u-boot images/linux/u-boot.elf

    BOOT.BIN contains the ATF, PMUFW, FSBL, U-Boot.
    image.ub contains the device tree and Linux kernel.

- Now copy the boot files to the SD card.

    cp images/linux/BOOT.BIN /media/pedro/BOOT/
    cp images/linux/image.ub /media/pedro/BOOT/

    It is assumed that you already partitioned the SD card. 
    - sudo gparted  (make sure you have the correct drive selected!)
    - First partition called BOOT, FAT32, 512MB
    - Second partition called rootfs, ext4, use the rest of the card.

- Now down load the root filesystem. It is 360MB.

    wget https://releases.linaro.org/debian/images/developer-arm64/latest/linaro-stretch-developer-20180416-89.tar.gz

- Uncompress the root filesystem preserving file attributes and ownership.

    sudo tar --preserve -zxvf linaro-stretch-developer-20180416-89.tar.gz

- Copy the root filesystem onto the SD card preserving file attributes and ownership.

    sudo cp --recursive --preserve binary/* /media/pedro/rootfs/


- Eject the SD card from your workstation and install it in the ZCU104.

- Connect to the USB Uart port on the zcu104 and start a terminal emulator. I use screen sometimes.

    sudo screen /dev/ttyUSB1 115200

- Power on the board and watch the boot sequence. U-boot will time out and start linux. You should end up at the command prompt as root.

    If you connect an ethernet cable to your network you should be able to update the OS with

    apt update
    apt upgrade

- You can start installing things.

    apt install man
    apt install subversion

- It is a good idea to create a user for yourself and give it sudoer privileges.

    adduser myuser
    usermod -aG sudo myuser

- The serial  terminal is limiting so I like to ssh into the board. First, find the ip address of the zcu104.

    ifconfig (or "ip address")

    Then go back to your workstation.

    ssh myuser@<ip address> 

- Configure the PL side of the Zynq with an FPGA design. This has changed with this newer Linux on Zynq+.

    Modify your FPGA build script to produce a .bin file in addition to the normal .bit file. The FPGA example in this project has that command in compile.tcl.
    
    Go to your terminal on the Zynq+ Linux command line.

    Do a "git pull" to get the latest .bin file from the FPGA side of the repo.

    Copy .../fpga/implement/results/top.bit.bin to /lib/firmware. I think you need to do this as sudo.

    Change to root with "sudo su".

    echo top.bit.bin > /sys/class/fpga_manager/fpga0/firmware

    This last command should make the "Done" LED go green indicating success.

- Good luck.

    
