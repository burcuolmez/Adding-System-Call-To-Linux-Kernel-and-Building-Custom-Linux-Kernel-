#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/fs.h>      
#include <asm/uaccess.h>   
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <asm/siginfo.h>
#include <linux/pid_namespace.h>
#include <linux/pid.h>
#include <linux/module.h>

#define PARAM_LEN 300

SYSCALL_DEFINE3(2017510084, char __user*, usr_param, char __user*, usr_pid, char __user*,dest){
	char param_0[PARAM_LEN];
    char param_1[PARAM_LEN];
    char param_2[PARAM_LEN];
	int returnVal=0;
	if(copy_from_user(param_0, usr_param, PARAM_LEN)==0){
		if(strcmp(param_0,"-p")==0){
		    if(copy_from_user(param_1, usr_pid, PARAM_LEN)==0){
				struct file *f;
				char buf[128];
				mm_segment_t fs;
				int i;
				for(i=0;i<128;i++)
					buf[i] = 0;
				char b[40];
				sprintf(b,"/proc/%s/cmdline",param_1);
				f = filp_open(b, O_RDONLY, 0);
				if(f == NULL)
					printk(KERN_ALERT "filp_open error!!.\n");
				else{
					fs = get_fs();
					set_fs(get_ds());
					f->f_op->read(f, buf, 128, &f->f_pos);
					set_fs(fs);
					sprintf(param_2,"pid:%s\tcmdline:%s\n",param_1,buf);
					returnVal= copy_to_user(dest,param_2, PARAM_LEN);
				}
				filp_close(f,NULL);
			}
		}
		else if(strcmp(param_0,"-k")==0){
		    if(copy_from_user(param_1, usr_pid, PARAM_LEN)==0){
				long pnumber;
				if(kstrtol(param_1, 10, &pnumber)==0){
					if(kill_pid(find_vpid(pnumber),SIGKILL,1) == 0){
						sprintf(param_2,"Process %li killed...\n", pnumber);
						returnVal= copy_to_user(dest,param_2, PARAM_LEN);
					}
				}
			}
		}	
		else if(strcmp(param_0,"-all")==0){
			struct task_struct *task_list;
			for_each_process(task_list) {
				printk(KERN_INFO "UID:%d\t PPID:%d\t PID:%d\t Name: %s\t State:%li\n",task_list->cred->uid,task_list->parent->pid, task_list->pid,task_list->comm,task_list->state);
				sprintf(param_2,"Processler\n");
				returnVal= copy_to_user(dest,param_2, PARAM_LEN);
			}
		}	  			
	}
	return returnVal;
}