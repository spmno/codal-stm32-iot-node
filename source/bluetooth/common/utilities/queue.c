/**
 ****************************************************************************
 * @file    queue.c
 * @author  MCD Application Team
 * @brief   Circurlar FIFO queue management code 
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other 
 *    contributors to this software may be used to endorse or promote products 
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this 
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under 
 *    this license is void and will automatically terminate your rights under 
 *    this license. 
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/


/* #include "StdAfx.h"  // specific vc++ */
#include "queue.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define MOD(X,Y) (((X) >= (Y)) ? ((X)-(Y)) : (X))
#define MIN(X,Y) (((X) > (Y)) ? (Y) : (X))

//#define MOD(X,Y) (X % Y)

/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief   Initilaiilze queue strcuture .
  * @note   This function is used to initialize the global queue strcuture.  
  * @param  q: pointer on queue strcture to be initialised 
  * @param  queueBuffer: pointer on Queue Buffer
  * @param  queueSize:  Size of Queue Buffer
  * @param  elementSize: Size of an element in the queue. if =0, the queue will manage variable sizze elements
  * @retval   always 0
  */

int CircularQueue_Init(queue_t *q, uint8_t* queueBuffer, uint32_t queueSize, uint16_t elementSize)
{
  q->qBuff = queueBuffer;
  q->first = 0;
  q->last = 0; //queueSize-1;
  q->byteCount = 0;
  q->elementCount = 0;
  q->queueMaxSize = queueSize;
  q->elementSize = elementSize;
  return 0;
}

/**
  * @brief   Add  element to the queue .
  * @note   This function is used to add one or more  element(s) to the Circular Queue .  
  * @param  q: pointer on queue structure   to be handled
  * @param  X; pointer on element(s) to be added 
  * @param  elementSize:  Size of element to be added to the queue. Only used if the queue manage variable size elements
  * @param  nbElements:  number of elements in the in buffer pointed by x
  * //@retval   number of elements in the queue, -1 if the element to be added do not fit in the queue (too big)
  * @retval  pointer on element last element just added to the queue, NULL if the element to be added do not fit in the queue (too big)
  */
uint8_t* CircularQueue_Add(queue_t *q, uint8_t* x, uint16_t elementSize, uint32_t nbElements)
{
  // TODO: Assert sur elementSize
  // TODO: Assert sur x

  uint8_t* ptr = NULL;                   /* fct return ptr to the element freshly added, if no room fct return NULL */
  uint16_t curElementSize = 0;             /* the size of the element currently  stored at q->last position */
  uint8_t  elemSizeStorageRoom  = 0;
  uint32_t curBuffPosition;                /* the current position in the queue buffer */
  uint32_t i;                             /* loop counter */
  uint32_t NbBytesToCopy =0 ;

  elemSizeStorageRoom  = (q->elementSize == 0) ? 2 : 0;

  /* retrieve the size of last element sored: the value stored at the beginning of the queue element if element size is variable otherwise take it from fixed element Size member */
  if (q->byteCount) 
        {
          curElementSize = (q->elementSize == 0) ? q->qBuff[q->last] + ((q->qBuff[MOD((q->last+1), q->queueMaxSize)])<<8) + 2 : q->elementSize;
  }
  /* if queue element have fixed size , reset the elementSize arg with fixed element size value */
  if (q->elementSize > 0)               
  {
           elementSize = q->elementSize;
  }

  /* Store now the elements */
  if (elementSize && (q->byteCount + ((elementSize + elemSizeStorageRoom )*nbElements)) <= q->queueMaxSize) 
  { 
    for (i=0; i < nbElements; i++) 
    {
      q->last = MOD ((q->last + curElementSize),q->queueMaxSize);
      curBuffPosition = q->last;

      /* store the element  */
      /* store fisrt the element size if element size is varaible */
      if (q->elementSize == 0) 
      {
        q->qBuff[curBuffPosition++]= elementSize & 0xFF;
        curBuffPosition = MOD(curBuffPosition, q->queueMaxSize);
         q->qBuff[curBuffPosition++]= (elementSize & 0xFF00) >> 8 ;
        curBuffPosition = MOD(curBuffPosition, q->queueMaxSize);
      }     

      
      /* Copy First Par from current position up to the end  of the buffer queue (or before if enough room) if any) */
      NbBytesToCopy = MIN((q->queueMaxSize-curBuffPosition),elementSize);
      if (NbBytesToCopy)
      {
          memcpy(&q->qBuff[curBuffPosition],&x[i*elementSize],NbBytesToCopy);
      }
      curBuffPosition = MOD((curBuffPosition+NbBytesToCopy),q->queueMaxSize);
        
      /* Copy second Part to beginning of buffer queue */
      if (NbBytesToCopy != elementSize)
      {
          memcpy(&q->qBuff[curBuffPosition],&x[(i*elementSize)+NbBytesToCopy],elementSize-NbBytesToCopy);
      }
      curElementSize = (elementSize) + elemSizeStorageRoom ;
    }
               
    q->byteCount+=((elementSize + elemSizeStorageRoom )*nbElements);
    q->elementCount+=nbElements;
    ptr = q->qBuff + (MOD((q->last+elemSizeStorageRoom ),q->queueMaxSize));
  }

  return ptr;
}


/**
  * @brief  Remove element from  the queue.
  * @note   This function is used to remove and element from  the Circular Queue .  
  * @param  q: pointer on queue structure  to be handled
  * @param  elementSize: Pointer to return Size of element to be removed  
  * @retval Pointer on removed element. NULL if queue was empty
  */
uint8_t* CircularQueue_Remove(queue_t *q, uint16_t* elementSize)
{
  uint8_t  elemSizeStorageRoom = 0;
  uint8_t* ptr= NULL;
  
  elemSizeStorageRoom = (q->elementSize == 0) ? 2 : 0;
  *elementSize = 0;
  if (q->byteCount > 0) 
  {
    *elementSize = (q->elementSize == 0) ? q->qBuff[q->first]+ ((q->qBuff[MOD((q->first+1), q->queueMaxSize)])<<8) : q->elementSize;
    ptr = q->qBuff + (MOD((q->first+elemSizeStorageRoom ),q->queueMaxSize));
    q->byteCount -= (*elementSize + elemSizeStorageRoom) ;
    if (q->byteCount > 0)
    {
      q->first = MOD((q->first + *elementSize + elemSizeStorageRoom ), q->queueMaxSize);
    }
  }
  return ptr;
}



/**
  * @brief  "Sense" first element of the quque, without removing it.
  * @note   This function is used to return a pointer on the first element of the queue without removing it.  
  * @param  q: pointer on queue structure  to be handled
  * @param  elementSize:  Pointer to return Size of element to be removed  
  * @retval Pointer on sensed element. NULL if queue was empty
  */
uint8_t* CircularQueue_Sense(queue_t *q, uint16_t* elementSize)
{
  //int ret = -1;
  uint8_t  elemSizeStorageRoom = 0;
  uint8_t* x= NULL;
  
  elemSizeStorageRoom = (q->elementSize == 0) ? 2 : 0;
  *elementSize = 0;
  if (q->byteCount > 0) 
  {
    *elementSize = (q->elementSize == 0) ? q->qBuff[q->first]+ ((q->qBuff[MOD((q->first+1), q->queueMaxSize)])<<8) : q->elementSize;
    x = q->qBuff + (MOD((q->first+elemSizeStorageRoom), q->queueMaxSize));
  }
  return x;
}

/**
  * @brief   Check if queue is empty.
  * @note    This function is used to to check if the queue is empty.  
  * @param  q: pointer on queue structure  to be handled
  * @retval   TRUE (1) if the queue is empyu otherwise FALSE (0) 
  */
int CircularQueue_Empty(queue_t *q)
{
  int ret=FALSE;
  if (q->byteCount <= 0) 
  {
    ret=TRUE;
  } 
  return ret;
}

int CircularQueue_NbElement(queue_t *q)
{
  return q->elementCount;
}


