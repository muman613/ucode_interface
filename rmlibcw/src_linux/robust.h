/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   robust.h
  @brief  mutex handling system interruptions

   Blocking system calls under Linux will fail with return code
   EINTR under various circumstances, most important one is when
   code is run under gdb (also when receiving a signal).
   
   To prevent this, all sem_... primitives have a guarded implementation
   called robust_sem_... :
   <pre>
   while (1) {
   rc=sem_wait(...)
   if (rc!=EINTR) break;
   }
   </pre>
   See source code for exact implementation. 

  @author Emmanuel Michon
  @date   2003-02-11
*/

#ifndef __ROBUST_H__
#define __ROBUST_H__

int robust_pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutexattr_t *mutexattr);
int robust_pthread_mutex_lock(pthread_mutex_t *mutex);
int robust_pthread_mutex_unlock(pthread_mutex_t *mutex);
int robust_pthread_mutex_destroy(pthread_mutex_t *mutex);
int robust_pthread_mutexattr_init(pthread_mutexattr_t *attr);
int robust_pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int robust_pthread_mutexattr_settype(pthread_mutexattr_t *attr, int kind);
int robust_pthread_setspecific(pthread_key_t key, void *attr);
void *robust_pthread_getspecific(pthread_key_t key);

int robust_sem_init(sem_t *sem, int pshared, unsigned int value);
int robust_sem_wait(sem_t * sem);
int robust_sem_trywait(sem_t * sem);
int robust_sem_post(sem_t * sem);
int robust_sem_getvalue(sem_t * sem, int * sval);
int robust_sem_destroy(sem_t * sem);

int robust_pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
int robust_pthread_cond_destroy(pthread_cond_t *cond);
int robust_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
int robust_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int robust_pthread_cond_broadcast(pthread_cond_t *cond);

#endif // __ROBUST_H__
