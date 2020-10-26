## **Question 1**:
  * It is my personal work.

## **Question 2**:
* ### Chose Scenario 2 for assignment.
  * Installed linux distribution Ubuntu 20.04 in dual boot.
    * ```
        $ lsb_release -a
        No LSB modules are available
        Distributor ID:	Ubuntu
        Description:	Ubuntu 20.04.1 LTS
        Release:	20.04
        Codename:	focal
      ```
  * Checked if VMX is supported.
    * ```
      $ cat /proc/cpuinfo
      flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx est
      ```
  * Checked if kvm exists.
    * ```
      $ kvm-ok 
      INFO: /dev/kvm exists
      KVM acceleration can be used
      ```
  * Forked torvalds/linux repository and cloned locally.
    * ```
      $ git clone https://github.com/poojakota17/linux.git
      ```
  * Created a kernel module to read MSRs of procbased,secondary procbased, exit aand entry controls.
     https://github.com/poojakota17/linux/blob/master/kernel/cmpe283-assignment1/cmpe283-1.c  

  * Created a makefile.
     https://github.com/poojakota17/linux/blob/master/kernel/cmpe283-assignment1/Makefile   
  * Installed make and gcc for compilation.
    * ```
      $ sudo apt-get install make
      $ sudo apt install gcc
      ```
  * Compiled the **cmpe283-1.c** file. Run the below command from `linux/kernel/cmpe283-assignment1/` directory.
    * ```
      $ make
        make -C /lib/modules/5.4.0-52-generic/build M=/home/pooja/cmpe283_assignment/linux/kernel/cmpe283-assignment1 modules
        make[1]: Entering directory '/usr/src/linux-headers-5.4.0-52-generic'
          CC [M]  /home/pooja/cmpe283_assignment/linux/kernel/cmpe283-assignment1/cmpe283-1.o
          Building modules, stage 2.
          MODPOST 1 modules
        WARNING: modpost: missing MODULE_LICENSE() in /home/pooja/cmpe283_assignment/linux/kernel/cmpe283-assignment1/cmpe283-1.o
        see include/linux/module.h for more information
          CC [M]  /home/pooja/cmpe283_assignment/linux/kernel/cmpe283-assignment1/cmpe283-1.mod.o
          LD [M]  /home/pooja/cmpe283_assignment/linux/kernel/cmpe283-assignment1/cmpe283-1.ko
        make[1]: Leaving directory '/usr/src/linux-headers-5.4.0-52-generic'
      ```  
  * Inserted the kernel module to kernel
    * ```
      $ sudo insmod cmpe283-1.ko
      ```
  * To view the ouput.
    * ```
      $ dmesg
      [26841.510009] CMPE 283 Assignment 1 Module Start
      [26841.510012] Pinbased Controls MSR: 0x7f00000016
      [26841.510015]   External Interrupt Exiting: Can set=Yes, Can clear=Yes
      [26841.510017]   NMI Exiting: Can set=Yes, Can clear=Yes
      [26841.510019]   Virtual NMIs: Can set=Yes, Can clear=Yes
      [26841.510020]   Activate VMX Preemption Timer: Can set=Yes, Can clear=Yes
      [26841.510022]   Process Posted Interrupts: Can set=No, Can clear=Yes
      [26841.510023] Processbased Controls MSR: 0xfff9fffe0401e172
      [26841.510025]   Interrupt-window exiting: Can set=Yes, Can clear=Yes
      [26841.510026]   Use TSC offsetting: Can set=Yes, Can clear=Yes
      [26841.510028]   HLT exiting: Can set=Yes, Can clear=Yes
      [26841.510029]   INVLPG exiting: Can set=Yes, Can clear=Yes
      [26841.510030]   MWAIT exiting: Can set=Yes, Can clear=Yes
      [26841.510032]   RDPMC exiting: Can set=Yes, Can clear=Yes
      [26841.510033]   RDTSC exiting: Can set=Yes, Can clear=Yes
      [26841.510035]   CR3-load exiting: Can set=Yes, Can clear=No
      [26841.510036]   CR3-store exiting: Can set=Yes, Can clear=No
      [26841.510038]   CR8-load exiting: Can set=Yes, Can clear=Yes
      [26841.510039]   CR8-store exiting: Can set=Yes, Can clear=Yes
      [26841.510041]   Use TPR shadow: Can set=Yes, Can clear=Yes
      [26841.510042]   NMI-window exiting: Can set=Yes, Can clear=Yes
      [26841.510044]   MOV-DR exiting: Can set=Yes, Can clear=Yes
      [26841.510049]   Unconditional I/O exiting: Can set=Yes, Can clear=Yes
      [26841.510051]   Use I/O bitmaps: Can set=Yes, Can clear=Yes
      [26841.510052]   Monitor trap flag: Can set=Yes, Can clear=Yes
      [26841.510054]   Use MSR bitmaps: Can set=Yes, Can clear=Yes
      [26841.510055]   MONITOR exiting: Can set=Yes, Can clear=Yes
      [26841.510056]   PAUSE exiting: Can set=Yes, Can clear=Yes
      [26841.510058]   Activate secondary controls: Can set=Yes, Can clear=Yes
      [26841.510059] Secondary Procbased Controls MSR: 0x8ff00000000
      [26841.510060]   Virtualize APIC accesses: Can set=Yes, Can clear=Yes
      [26841.510062]   Enable EPT: Can set=Yes, Can clear=Yes
      [26841.510063]   Descriptor-table exiting: Can set=Yes, Can clear=Yes
      [26841.510064]   Enable RDTSCP: Can set=Yes, Can clear=Yes
      [26841.510065]   Virtualize x2APIC mode: Can set=Yes, Can clear=Yes
      [26841.510067]   Enable VPID: Can set=Yes, Can clear=Yes
      [26841.510068]   WBINVD exiting: Can set=Yes, Can clear=Yes
      [26841.510069]   Unrestricted guest: Can set=Yes, Can clear=Yes
      [26841.510070]   APIC-register virtualization: Can set=No, Can clear=Yes
      [26841.510072]   Virtual-interrupt delivery: Can set=No, Can clear=Yes
      [26841.510073]   PAUSE-loop exiting: Can set=No, Can clear=Yes
      [26841.510074]   RDRAND exiting: Can set=Yes, Can clear=Yes
      [26841.510076]   Enable INVPCID: Can set=No, Can clear=Yes
      [26841.510077]   Enable VM functions: Can set=No, Can clear=Yes
      [26841.510078]   VMCS shadowing: Can set=No, Can clear=Yes
      [26841.510080]   Enable ENCLS exiting: Can set=No, Can clear=Yes
      [26841.510081]   RDSEED exiting: Can set=No, Can clear=Yes
      [26841.510114]   Enable PML: Can set=No, Can clear=Yes
      [26841.510116]   EPT-violation #VE: Can set=No, Can clear=Yes
      [26841.510118]   Conceal VMX non- root operation from Intel PT: Can set=No, Can clear=Yes
      [26841.510119]   Enable XSAVES/XRSTORS: Can set=No, Can clear=Yes
      [26841.510124]   Mode-based execute control for EPT: Can set=No, Can clear=Yes
      [26841.510129]   Use TSC scaling: Can set=No, Can clear=Yes
      [26841.510134] Exit Controls MSR: 0x7fffff00036dff
      [26841.510138]   Save debug controls: Can set=Yes, Can clear=No
      [26841.510153]   Host address- space size: Can set=Yes, Can clear=Yes
      [26841.510158]   Load IA32_PERF_GLOB AL_CTRL: Can set=Yes, Can clear=Yes
      [26841.510161]   Acknowledge interrupt on exit: Can set=Yes, Can clear=Yes
      [26841.510164]   Save IA32_PAT: Can set=Yes, Can clear=Yes
      [26841.510167]   Load IA32_PAT: Can set=Yes, Can clear=Yes
      [26841.510169]   Save IA32_EFER: Can set=Yes, Can clear=Yes
      [26841.510172]   Load IA32_EFER: Can set=Yes, Can clear=Yes
      [26841.510174]   Save VMX- preemption timer value: Can set=Yes, Can clear=Yes
      [26841.510177]   Clear IA32_BNDCFGS: Can set=No, Can clear=Yes
      [26841.510180]   Conceal VM exits from Intel PT: Can set=No, Can clear=Yes
      [26841.510183] Entry Controls MSR: 0xffff000011ff
      [26841.510185]   Load debug controls: Can set=Yes, Can clear=No
      [26841.510188]   IA-32e mode guest: Can set=Yes, Can clear=Yes
      [26841.510191]   Entry to SMM: Can set=Yes, Can clear=Yes
      [26841.510194]   Deactivate dual- monitor treatment: Can set=Yes, Can clear=Yes
      [26841.510197]   Load IA32_PERF_GLOBA L_CTRL: Can set=Yes, Can clear=Yes
      [26841.510199]   Load IA32_PAT: Can set=Yes, Can clear=Yes
      [26841.510202]   Load IA32_EFER: Can set=Yes, Can clear=Yes
      [26841.510204]   Load IA32_BNDCFGS: Can set=No, Can clear=Yes
      [26841.510207]   Conceal VM entries from Intel PT: Can set=No, Can clear=Yes
      ```
  * To remove the module from kernel.
    * ```
       $ sudo rmmod cmpe283-1.ko    
       $ dmesg
        [27301.981914] CMPE 283 Assignment 1 Module Exits



