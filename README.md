Linux kernel
============
#  **Assignment 1**
============
https://github.com/poojakota17/linux/tree/master/kernel/cmpe283-assignment1

============
#  **Assignment 2**
============

## **Team members**:
* *Anastasia Zimina*
* *Pooja Prasannan* 

### **Question 1**: 
## (Work by Pooja Prasannan)

* Scenario 2 setup with host OS as linux(Ubuntu 20.04).
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
        $ Linux pooja 5.4.0-52-generic  #57-Ubuntu SMP Thu Oct 15 10:57:00 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
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
  
#### After seting up the environment analysed linux/arch/x86/kvm/vmx/vmx.c and linux/arch/x86/kvm/cpuid.c
*   Analysed the exit handling function, vmx_handle_exit(vmx.c) and exit handler function for cpuid, kvm_emulate_cpuid(cpuid.c).
* Tried to understand where to place the code for new leaf function(0x4FFFFFFF). 
* Studied about atomic variables.
* Analysed their operations like addition  and increment operation of those variables in atomic.h file.
* Studied about EXPORT_SYMBOL and EXPORT_SYMBOL_GPL to use variables between 2 files(vmx.c and cpuid.c).
* Implemented the 

### **Question 2**:

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

### **Question 3**:

* Yes the exits increase at a stable rate if nothing is done on the test VM and the test file is executed again and again at fixed intervals. But if we execute diferent type of instruction or commands in the test VM, the exits are different and change at a different rate. Yes there are more exits for some instruction like for eg: reboot takes a different amount of exits compared to cpuid.
* A full VM reboot takes approximately 10,000 -15,000 exits.


  


