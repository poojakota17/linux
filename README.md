Linux kernel
============
#  **Assignment 1**
============

* https://github.com/poojakota17/linux/tree/master/kernel/cmpe283-assignment1
* Readme : https://github.com/poojakota17/linux/blob/master/kernel/cmpe283-assignment1/README.md


#  **Assignment 2**
============

## **Team members**:
* *Anastasia Zimina*
* *Pooja Prasannan* 

### **Question 1**: 
## Work by Pooja Prasannan

* Scenario 1 setup with host OS as linux(Ubuntu 20.04).
* Checked if vmx is available.
  * ```
    $ cat /proc/cpuinfo
    flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx est
      ```
*  Checked if kvm exists.
    * ```
      $ kvm-ok 
      INFO: /dev/kvm exists
      KVM acceleration can be used
      ```
* Forked torvalds/linux repository and cloned locally.
    * ```
      $ git clone https://github.com/poojakota17/linux.git
      ``` 
* Installed gcc and make.   
* Builded the kernel using following commands:
    * ```
      $ cd cmpe283assignment/linux
      $ sudo bash
      # apt-get install build-essential kernel-package fakeroot libncurses5-dev libssl-dev ccache bison flex libelf-dev 
      # uname -a
        # Linux pooja 5.4.0-52-generic  #57-Ubuntu SMP Thu Oct 15 10:57:00 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
      # cp /boot/config-5.4.0-52-generic     ./.config  
      # make oldconfig
      # make -j 4 && make modules -j 4 && make install -j 4 && make modules_install -j 4
      # reboot
      ```
* There was some kernel panic error after rebooting with the modified kernel, so I rebooted with old kernel and stripped down the new kernel module to enable smooth reboot with user interface with following commands:
     * ```
        $ cd /lib/modules/5.9.0+/
        $ find . -name *.ko -exec strip --strip-unneeded {} +
        $ update-initramfs -u
* Checked new kernel version
    * ```
        $ uname -a
         5.9.0+ 
* Installed virt manager.
* Downloaded ISO iamge of Ubuntu 18.04 64 bit.
*  Installed inner VM(with 2 VCPU and 20 GB disk space) through virtual machine manager using the ISO image.


#### After seting up the environment:

* Research
  * Analysed linux/arch/x86/kvm/vmx/vmx.c and linux/arch/x86/kvm/cpuid.c 
  *   Analysed the exit handling function, vmx_handle_exit(vmx.c) and exit handler function for cpuid, kvm_emulate_cpuid(cpuid.c).
  * Tried to understand where to place the code for new leaf function(0x4FFFFFFF). 
  * Studied about atomic variables.
  * Analysed their operations like addition  and increment operation of those variables in atomic.h file.
  * Studied about EXPORT_SYMBOL and EXPORT_SYMBOL_GPL to use variables between 2 files (vmx.c and cpuid.c).
* Implementation
  * Created a atomic64_t type variable total_time to record processor cycles for all exits in cpuid.c and exported to be used in vmx.c 
  * Then in vmx.c, I calculated the initial time stamp counter using rdtsc() and assigned it to processing_time_start whenever an exit happen. On completing the exit handler again rdtsc() is used to determine exit handling end time and assigned to processing_time_end and their difference is added to the total_time for all exits. 
  * From the 64 bit total_time, I took the high 32 bits using right shift operator with 32 and low 32 bits with bitwise AND with 0xffffffff and assigned it to EBX and ECX registers if CPUID new leaf function(0x4FFFFFFF) is called.
* Testing
  * I did the testing part for total_time in guest VM and checked its values in EBX and ECX by putting 0x4FFFFFFF in EAX(Calling CPUID leaf function 0x4FFFFFFF. 
  

## Work by Anastasia Zimina
### Google Cloud Set-up
1. Login to Google Cloud Console.
1. Create a VM with enabled nested virtualization
  * Open Gcloud Terminal
  * run `gcloud compute images list --show-deprecate` that will output all possible images 
  * To create a custom image choose the OS from above and run 
  ```
  gcloud compute images create nested-vm-anastasia-2004-focal \
  --source-image=ubuntu-2004-focal-v20201028 \
  --source-image-project=ubuntu-os-cloud \
  --boot-disk-size=200GB \
  --licenses="https://www.googleapis.com/compute/v1/projects/vm-options/global/licenses/enable-vmx"
  ```
  * To create a VM from that image run 
  ``` 
  gcloud compute instances create nested-vm-ubuntu --zone us-central1-b --image nested-vm-anastasia-2004-focal
  ```
  * After creation it will appear in the list of your VMs. Stop it.
  * Update its settings: more CPUs and add extra disk.
  * Connect to it using ssh
  * Check nested virtualization is enabled: `cat /proc/cpuinfo | grep vmx`
3. Mount additional disk to the VM (int the vm terminal) (optional):
```
  sudo lsblk [it'll show info about available disk and the one you need to mount]
  sudo mkfs.ext4 -m 0 -E lazy_itable_init=0,lazy_journal_init=0,discard /dev/sdb [format the disk]
  sudo mkdir -p /mnt/disks/dir [create a directory to serve as a mount point for the new disk]
  sudo mount -o discard,defaults /dev/sdb /mnt/disks/dir [mount the disk]
  sudo chmod a+w /mnt/disks/dir [add read and write permissions]
  sudo cp /etc/fstab /etc/fstab.backup [create a backup of the fstab file]
  sudo blkid /dev/sdb [check the uuid for the disk running this command]
  sudo blkid -s UUID -o value /dev/sdb` /mnt/disks/dir ext4 discard,defaults,nofail 0 2 | sudo tee -a /etc/fstab [add info about the dist]
  ```
  * than check that it's mounted `cat /etc/fstab`
4. Generate and add ssh key for your github account
  ``` 
  ssh-keygen -t rsa -b 4096 -C "your_email@example.com" 
  eval "$(ssh-agent -s)"
  ssh-add ~/.ssh/id_rsa
  cat < ~/.ssh/id_rsa.pub
  ```
  and copy ssh-key and then add it your github account (Settings => SSH and GPG keys => New SSH key)
5. Clone previously forked linux repository: `git clone git@github.com:YOUR_NAME/linux.git`
1. Build the Kernel (in the linux folder!)
  * `sudo bash`
  * `apt-get install build-essential fakeroot libncurses5-dev libssl-dev ccache bison flex libelf-dev dwarves`
  * check your kernel version with `uname -a` \
  (output should look like: `
Linux anastasia-nested-vm 5.8.0-1008-gcp #8-Ubuntu SMP Thu Oct 15 12:48:27 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux`)
  * make a copy of config to the current directory (should be the one created by git clone) `cp /boot/config-YOUR_KERNEL_VERSION` ./.config
  * run `make oldconfig` (press Enter for all questions)
  * build it `make && make modules && make install && make modules_install`
  * reboot
7. Verify that the kernel is updated: `uname -a` \ 
 ( output should  look like: `Linux anastasia-nested-vm 5.10.0-rc2+ #4 SMP Wed Nov 4 01:56:19 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux`)
8. Update the VM instance and install some necessary packages to run nested VM and download Ubuntu image for the nested VM
```
sudo apt-get install virt-manager 
wget http://releases.ubuntu.com/20.04/ubuntu-20.04.1-desktop-amd64.iso
sudo virt-install --name zimavm --ram 1024 --disk path=/var/lib/libvirt/images/zimavm.img,size=8 --vcpus 1 --virt-type kvm --os-type l
inux --os-variant ubuntu18.04 --graphics none --location 'http://archive.ubuntu.com/ubuntu/dists/bionic/main/installer-amd64/' --extra-args "console=tty0 console=ttyS0,115200n8"
```
While installation make sure to choose OpenSSH when it prompts for additional software to install.
9. VMs manipulations:
```
sudo virsh list --all // list all VMs
sudo virsh start [nameOfVM] // start the VM with the specified name
sudo virsh destroy [nameOfVM] //stop the VM with the specified name
sudo virsh undefine [nameOfVm] // delete VM
sudo virsh domifaddr [nameOfVM] // get address/port to connect to the vm
```
10. Check that host can ping nested vm
```
sudo ping -c 2 [nameOfVM]

```

### Research, Implementation and Testing
 - The main goal of the assigment was to calculate exits from the VM and time spent processing them in the VMM. \
To calculate exits we need to assecc some data structure to hold exits in vmx.c , update it everytime when the exit occurs (vmx_handle_exit function) and then put in into %eax register while emulating cpuid (kvm_emulate_cpuid function in cpuid.c ). One of the ways to it is to use atomic variable. 
 - In order to do that `atomic_t total_exits` was added to cpuid.c. To make it visible in vmx.c EXPORT_SYMBOL_GPL(total_exits) was used.
 - On each entry to vmx_handle_exit in vmx.c total_exits were updated `atomic_inc(&total_exits)`
 - Tested using C, total exits in guest VM by calling CPUID leaf function (0x4FFFFFFF).
  
## **Question 2**:

* We put a new CPUID leaf function in
kvm_emulate_cpuid function : 
https://github.com/poojakota17/linux/blob/master/arch/x86/kvm/cpuid.c
  * We have two atomic variables, total_exits and total_time which we exported through EXPORT_SYMBOL_GPL so that vmx.c file can access it while handling exits.
  * If input in eax is 0x4FFFFFFF then we set eax to total_exits, ebx to high 32 bits of total_time and ecx to low 32 bits of total_time.
* We modified the vmx_handle_exit such that whenever this function is called we are incrementing total_exit and we are reading the timestamp counter. On successfull execution of any particular exit handler we are again reading the timestamp counter, and the difference of final and initial counter cycles are added to the total_time to get cycles of all exits. 
https://github.com/poojakota17/linux/blob/master/arch/x86/kvm/vmx/vmx.c
* Recompile the kernel and reboot to see the change:
    * ```
      # sudo bash
      # make -j 4 && make modules -j 4 && make install -j 4 and make modules_install -j 4
      # reboot 
* In our test VM, we created a test file in C in which we mov $0x4FFFFFFF to eax and we are executing CPUID in to get back results of the new leaf function.
    * ``` 
       $ vi testassignment2.c
       $ gcc test2assignment2.c

* Run the executable file.(./a.out)
  
### **Output**:   
``` 
$ ./a.out
CPUID(0x4FFFFFFF)   Total Exits= 4638819	 Total cycles= 19271846126		
```
* Can also test output with printk statements in kernel code and doing:
  ```
  $ dmesg
  [17326.920735] Total time
    [17326.920739] 19271846126
    [17326.920740] Total exits
    [17326.920742] 4638819
    [17326.920743] High 32 bits of total cycles in ebx
    [17326.920745] 4
    [17326.920746] low 32 bits of total cycles in ecx
    [17326.920748] 2091976942
  ```

## **Question 3**:

* Yes the exits increase at a stable rate if nothing is done on the test VM and the test file is executed again and again at fixed intervals. But if we execute different type of instruction or commands in the test VM, the exits are different and change at a different rate. Yes there are more exits for some instruction like for eg: reboot takes a different amount of exits compared to cpuid.
* A full VM reboot takes approximately 10,000 -15,000 exits.

Resources:
  - [How to enable nested virtualization of Google Cloud](https://www.cloudkb.net/how-to-enable-nested-virtualization-on-google-cloud/)
  - [Adding or resizing zonal persistent disks](https://cloud.google.com/compute/docs/disks/add-persistent-disk)
  - [Atomic variables in C](https://www.kernel.org/doc/Documentation/atomic_t.txt)


#  **Assignment 3**
============

## **Team members**:
* *Anastasia Zimina*
* *Pooja Prasannan* 

### **Question 1**: 
## (Work by Pooja Prasannan)
Analysed how to increment total exits for each exit in vmx.c (vmx_handle_exit). Found how to use an atomic integer array and its intitialization to increment for each exit reason individually. Analysed where to place it in the vmx.c and how to access it in cpuid.c using export_smbol_gpl and extern. For implementation added a cpuid leaf function 0x4ffffffe to check for exits supported in kvm and sdm and assignned values to eac,ebx,ecx and edx correspondingly. 

## (Work by Anastasia Zimina)
We both worked separatly in different enviroments untill the first results. So I also updated cpuid.c to add conditions for checking the leaf, and ecx register (input for the exit reason from user), and an array of attomics to store exit results. Updated vmx.c to increment element in the exits array corresponding to the current exit reason.

### **Question 2**: 
Implementaion:

On top of assignment 2, we created a new cpuid leaf function for 0x4ffffffe to get total exits for each exit reason in ecx.
For exit-reason from 0-68(except 35,38,42 and 65) implemented in SDM , if that particular exit is enabled in kvm then eax will have total exit. If its not enabled then, all 4 registers will have 0. If its outside a value not implemented in sdm, then eax, ebx,ecx will have zero and edx will have 0xffffffff. 

We have created an array of size 69 and is incrementing it in vmx_handle_exit in vmx.c. In cpuid exit handler, we are reading this array according to the input in ecx and if its outside the range or amongst exit number 35,38,42 and 65 then edx will have 0xfffffff and other 3 registers will have value 0. If its in the range and exit has occured then values will be reflected in eax else it will be 0 if its not enabled.

**Compilation and build**
Once editing the code :
```
  cd linux
  # sudo bash
  # make -j 4 && make modules -j 4 && make install -j 4 and make modules_install -j 4
  # reboot

```
After reboot in no gui gcloud enviroment
```
/* IN VMM */
 sudo bash 
 sudo virsh list --all //list all awailable inner VMs
 sudo virsh start [nameOfVM] //start inner VM
 sudo ssh [user]@[nameOfVM]
 
/* IN VM */
 gcc test.c // compile test file
 ./a.out > some.txt
 exit // go back to VMM
 
 /* IN VMM */
 sudo bash
 sudo dmesg
 sudo virsh destroy [nameOfVM] // stop inner VM
```



#### **Output**
  
Below is a sample output for exit reasons from 28 to 35. Since 35 is not implemented so it have integer value of 0xffffffff:
  ```
CPUID(0x4FFFFFFE) Exit for exit_reason 35 = 0	            edx= 4294967295	

CPUID(0x4FFFFFFE) Exit for exit_reason 34 = 0	            edx= 0	

CPUID(0x4FFFFFFE) Exit for exit_reason 33 = 0	            edx= 0	

CPUID(0x4FFFFFFE) Exit for exit_reason 32 = 114122	      edx= 0	

CPUID(0x4FFFFFFE) Exit for exit_reason 31 = 7963	        edx= 0	

CPUID(0x4FFFFFFE) Exit for exit_reason 30 = 266998	      edx= 0	

CPUID(0x4FFFFFFE) Exit for exit_reason 29 = 2	            edx= 0

CPUID(0x4FFFFFFE) Exit for exit_reason 28 = 28216	        edx= 0 	
  ```

### **Question 4**
Some exits are more frequent like exit reasons 48, 49, 30, 32, 52, 12.
Some exits are less frequent like exit reasons 54, 55, 47, 46, 44, 29.

In the gcloud enviroment are I/0 and CPUID
 The most common:
  - 30(I/O): 168K
  - 10(CPUID): 71K
  - 28(control-register access): 25K
 
 
 - 0(Exceptions): 16K
 - 49(EPT misconfiguration): 12K
 - 48(EPT violation): 8K
 - 32(WRMSR): 5K
 - 1(External interrupt): 4K
 - 12(HLT): 2K
 - 7(Interrupt window): 1K

 The least:
 - 31(RDMSR): 0.2K 
 - 44(APIC access): 11
 - 29(MOV DR): 1

#  **Assignment 4**
============

## **Team members**:
* *Anastasia Zimina*
* *Pooja Prasannan* 

### **Question 1**: 
## (Work by Pooja Prasannan)
Studied about nested and shadow paging, their exit differences.

## (Work by Anastasia Zimina)
Studied about nested and shadow paging, their exit differences.
Used the same approach in gcloud enviroment. 

Updated documentation

After shutting down inner vm, did 
  ```
    cd /lib/modules/5.9.0+/kernel/arch/x86/kvm
    sudo bash
    rmmod kvm-intel
    insmod kvm-intel.ko ept = 0
  ```
  
  Analysed the changes in exits before and after ept modification.
### **Question 2**
  **Output**

  When Nested Paging is on.
  ```
      dmesg
     [ 1582.452307] Total exits
     [ 1582.452310] 1898228
  ```
  ```
  CPUID(0x4FFFFFFE) Exit for exit_reason 32 = 31776	 ebx= 0	 ecx= 32	 edx= 0	
CPUID(0x4FFFFFFE) Exit for exit_reason 31 = 833	     ebx= 0	 ecx= 31	 edx= 0
CPUID(0x4FFFFFFE) Exit for exit_reason 30 = 1257204	 ebx= 0	 ecx= 30	 edx= 0	
CPUID(0x4FFFFFFE) Exit for exit_reason 29 = 2	     ebx= 0	 ecx= 29	 edx= 0
CPUID(0x4FFFFFFE) Exit for exit_reason 28 = 15928	 ebx= 0	 ecx= 28	 edx= 0	
  ```

  When Shadow Paging is on
  ```
     dmesg

     [  569.454654] Total exits
     [  569.454658] 3154271

  ```
  ```
  CPUID(0x4FFFFFFE) Exit for exit_reason 32 = 119953	     ebx= 0	 ecx= 32	 edx= 0	
  CPUID(0x4FFFFFFE) Exit for exit_reason 31 = 7853	     ebx= 0	 ecx= 31	 edx= 0	
  CPUID(0x4FFFFFFE) Exit for exit_reason 30 = 1515431	     ebx= 0	 ecx= 30	 edx= 0	
  CPUID(0x4FFFFFFE) Exit for exit_reason 29 = 4	         ebx= 0	 ecx= 29	 edx= 0
  CPUID(0x4FFFFFFE) Exit for exit_reason 28 = 31586	     ebx= 0	 ecx= 28	 edx= 0
  ```
  

  ### **Question 3**
     
  Number of exits have been increased when nested paging is turned off. Yes this was an expected output as shadow paging requires more exits for its implementation like #PF, mov to CR3, mov from CR3, TLB flush exit etc.

  ### **Question 4**

  Between the two runs there was a significant increase in number of exits because the number of exits to be handled in shadow paging is more compared to nested paging. In Nested Paging EPT violation is the exit to be handled whereas in shadow paging there are multiple. This is because in shadow paging, hypervisor have to enable #PF exiting so that it can keep the shadow page table empty and do side by side walks with theexit guest vm percieved page table.It also needs to enable exit for mov to and from CR3 so that whenever a guest wants to read or write from/to CR3 , it gets its own managed pagetable. Also there are TLB flush exits so that hypevisor can keep the TLB updated as per guests managed page table. Also mov to CR4, INVLPG etc also cause TLB flushes which in turn cause exits. Thus shadow paging implementation is more complex than nested paging because of more exits.
  
  **Observation in gCloud enviroment:**  \
  While trying to disable nested paging first 5 attempts ended in lost commection to the VMM. 
  ```
  rmmod kvm-intel
  insmod kvm-intel.ko ept = 0
  virsh start [innerVM]
  ssh [user]@[innerVM] => connection is lost
  ```
  During the last try connestion wasn't lost but the number of total exits didn't change. 
  So my guess is that somehow gcloud doesn't allow disabling nested pages.
