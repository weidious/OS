/*
 File: ContFramePool.C
 
 Author:
 Date  : 
 
 */

/*--------------------------------------------------------------------------*/
/* 
 POSSIBLE IMPLEMENTATION
 -----------------------

 The class SimpleFramePool in file "simple_frame_pool.H/C" describes an
 incomplete vanilla implementation of a frame pool that allocates 
 *single* frames at a time. Because it does allocate one frame at a time, 
 it does not guarantee that a sequence of frames is allocated contiguously.
 This can cause problems.
 
 The class ContFramePool has the ability to allocate either single frames,
 or sequences of contiguous frames. This affects how we manage the
 free frames. In SimpleFramePool it is sufficient to maintain the free 
 frames.
 In ContFramePool we need to maintain free *sequences* of frames.
 
 This can be done in many ways, ranging from extensions to bitmaps to 
 free-lists of frames etc.
 
 IMPLEMENTATION:
 
 One simple way to manage sequences of free frames is to add a minor
 extension to the bitmap idea of SimpleFramePool: Instead of maintaining
 whether a frame is FREE or ALLOCATED, which requires one bit per frame, 
 we maintain whether the frame is FREE, or ALLOCATED, or HEAD-OF-SEQUENCE.
 The meaning of FREE is the same as in SimpleFramePool. 
 If a frame is marked as HEAD-OF-SEQUENCE, this means that it is allocated
 and that it is the first such frame in a sequence of frames. Allocated
 frames that are not first in a sequence are marked as ALLOCATED.
 
 NOTE: If we use this scheme to allocate only single frames, then all 
 frames are marked as either FREE or HEAD-OF-SEQUENCE.
 
 NOTE: In SimpleFramePool we needed only one bit to store the state of 
 each frame. Now we need two bits. In a first implementation you can choose
 to use one char per frame. This will allow you to check for a given status
 without having to do bit manipulations. Once you get this to work, 
 revisit the implementation and change it to using two bits. You will get 
 an efficiency penalty if you use one char (i.e., 8 bits) per frame when
 two bits do the trick.
 
 DETAILED IMPLEMENTATION:
 
 How can we use the HEAD-OF-SEQUENCE state to implement a contiguous
 allocator? Let's look a the individual functions:
 
 Constructor: Initialize all frames to FREE, except for any frames that you 
 need for the management of the frame pool, if any.
 
 get_frames(_n_frames): Traverse the "bitmap" of states and look for a 
 sequence of at least _n_frames entries that are FREE. If you find one, 
 mark the first one as HEAD-OF-SEQUENCE and the remaining _n_frames-1 as
 ALLOCATED.

 release_frames(_first_frame_no): Check whether the first frame is marked as
 HEAD-OF-SEQUENCE. If not, something went wrong. If it is, mark it as FREE.
 Traverse the subsequent frames until you reach one that is FREE or 
 HEAD-OF-SEQUENCE. Until then, mark the frames that you traverse as FREE.
 
 mark_inaccessible(_base_frame_no, _n_frames): This is no different than
 get_frames, without having to search for the free sequence. You tell the
 allocator exactly which frame to mark as HEAD-OF-SEQUENCE and how many
 frames after that to mark as ALLOCATED.
 
 needed_info_frames(_n_frames): This depends on how many bits you need 
 to store the state of each frame. If you use a char to represent the state
 of a frame, then you need one info frame for each FRAME_SIZE frames.
 
 A WORD ABOUT RELEASE_FRAMES():
 
 When we releae a frame, we only know its frame number. At the time
 of a frame's release, we don't know necessarily which pool it came
 from. Therefore, the function "release_frame" is static, i.e., 
 not associated with a particular frame pool.
 
 This problem is related to the lack of a so-called "placement delete" in
 C++. For a discussion of this see Stroustrup's FAQ:
 http://www.stroustrup.com/bs_faq2.html#placement-delete
 
 */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "cont_frame_pool.H"
#include "console.H"
#include "utils.H"
#include "assert.H"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/
ContFramePool* ContFramePool::pool_list;

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   C o n t F r a m e P o o l */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
ContFramePool* ContFramePool::pool_list;

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   C o n t F r a m e P o o l */
/*--------------------------------------------------------------------------*/

ContFramePool::ContFramePool(unsigned long _base_frame_no,
                             unsigned long _n_frames,
                             unsigned long _info_frame_no,
                             unsigned long _n_info_frames){
    // TODO: IMPLEMENTATION NEEEDED!

    /*Constructor: Initialize all frames to FREE, except for any frames that you 
      need for the management of the frame pool, if any.
    */
    assert(_nframes <= FRAME_SIZE * 8);
    
    base_frame_no = _base_frame_no;
    nframes = _n_frames;
    nFreeFrames = _n_frames;
    info_frame_no = _info_frame_no;
    n_info_frames = _n_info_frames;
    
    // If _info_frame_no is zero then we keep management info in the first
    //frame, else we use the provided frame to keep management info
    if(info_frame_no == 0) {
        bitmap = (unsigned char *) (base_frame_no * FRAME_SIZE);
    } else {
        bitmap = (unsigned char *) (info_frame_no * FRAME_SIZE);
    }
     assert ((nframes % 8 ) == 0);
    
    // Everything ok. Proceed to mark all bits in the bitmap huge nut okey for now
    for(int i=0; i*8 < _nframes; i++) {
        bitmap[i] = 0xFFFF;
    }

    if(_info_frame_no == 0) {
        bitmap[0] = 0x3FFF;
        nFreeFrames--;
    }


     if (ContFramePool::pool_list==NULL)
                ContFramePool::pool_list=this;
     else
        pool_list->next = this;
    
     prev = pool_list;
    Console::puts("Frame Pool initialized\n");
}

unsigned long ContFramePool::get_frames(unsigned int _n_frames)
{
    // TODO: IMPLEMENTATION NEEEDED!
     // Any frames left to allocate?
    assert(nFreeFrames > 0);
    Console::puts("In get frames"); 
    // Find a frame that is not being used and return its frame index.
    // Mark that frame as being used in the bitmap.
   /*
    for(int k = 0 ; k < 10 ;++k){
    Console::puti(bitmap[k]); 
   }
   */
    unsigned int frame_no = base_frame_no;
    Console::puti(frame_no); 
    unsigned int i = 0;
    int space = 0;
    while(space != _n_frames){
        for(;i<256;++i){
            bitmap[i]
        }
    }
    
    unsigned char mask = 0x80;
    while ((mask & bitmap[i]) == 0) {
        mask = mask >> 1;
        frame_no++;
    }
    nFreeFrames--;
    
    // Update bitmap
    bitmap[i] = bitmap[i] ^ mask;
    
    return (frame_no);





    while(i<nframes){
        int j = i; 
        if(bitmap[i] == 'F'){
    
    Console::puti(i); 
    
    Console::puts("==F\n"); 
            for (;j-i+1<=_n_frames; j++){
        
    Console::puti(i); 
    Console::puts("and"); 
    Console::puti(j); 
    Console::puts("\n"); 
                if (bitmap[j] != 'F'){
                    break;
                }
            }
        }
        if(j-i == _n_frames)
                break;
        
        i = j+1;
    }

    //if (i == nframes) return 0;

    for(int x = i;x < _n_frames;x++){
        if(x==i)
            bitmap[x]='H';
        else{
            bitmap[x]='A';
        }
    }
        
    Console::puts("\n"); 
    Console::puti(i); 
    frame_no += i;   
    Console::puts("\n"); 
    nFreeFrames -= _n_frames;
    return (frame_no);
}


ContFramePool::ContFramePool(unsigned long _base_frame_no,
                             unsigned long _n_frames,
                             unsigned long _info_frame_no,
                             unsigned long _n_info_frames){
    // TODO: IMPLEMENTATION NEEEDED!

    /*Constructor: Initialize all frames to FREE, except for any frames that you 
      need for the management of the frame pool, if any.
    */
    assert(_n_info_frames<=_n_frames)
    
    base_frame_no = _base_frame_no;
    nframes = _n_frames;
    nFreeFrames = _n_frames;
    info_frame_no = _info_frame_no;
    n_info_frames = _n_info_frames;
    
    // If _info_frame_no is zero then we keep management info in the first
    //frame, else we use the provided frame to keep management info
    if(info_frame_no == 0) {
        bitmap = (unsigned char *) (base_frame_no * FRAME_SIZE);
    } else {
        bitmap = (unsigned char *) (info_frame_no * FRAME_SIZE);
    }
    
    // Everything ok. Proceed to mark all bits in the bitmap huge nut okey for now
    for(int i=0; i < _n_frames; i++) {
        bitmap[i]='F';
    }
    
    // Mark the first frame as being used if it is being used
/* 
   if(_info_frame_no == 0) {
        bitmap[0] = 'H';
        nFreeFrames--;
    }
*/
     if (ContFramePool::pool_list==NULL)
                ContFramePool::pool_list=this;
     else
     	pool_list->next = this;
    
     prev = pool_list;
    Console::puts("Frame Pool initialized\n");
}

unsigned long ContFramePool::get_frames(unsigned int _n_frames)
{
    // TODO: IMPLEMENTATION NEEEDED!
     // Any frames left to allocate?
    assert(nFreeFrames > 0);
    Console::puts("In get frames"); 
    // Find a frame that is not being used and return its frame index.
    // Mark that frame as being used in the bitmap.
    for(int k = 0 ; k < 10 ;++k){
    Console::puti(bitmap[k]); 
   }
    unsigned int frame_no = base_frame_no;
    Console::puti(frame_no); 
    unsigned int i = 0;
    while(i<nframes){
        int j = i; 
        if(bitmap[i] == 'F'){
	
    Console::puti(i); 
    
    Console::puts("==F\n"); 
            for (;j-i+1<=_n_frames; j++){
		
    Console::puti(i); 
    Console::puts("and"); 
    Console::puti(j); 
    Console::puts("\n"); 
                if (bitmap[j] != 'F'){
                    break;
                }
            }
        }
        if(j-i == _n_frames)
                break;
        
        i = j+1;
    }

    //if (i == nframes) return 0;

    for(int x = i;x < _n_frames;x++){
        if(x==i)
            bitmap[x]='H';
        else{
            bitmap[x]='A';
        }
    }
    	
    Console::puts("\n"); 
    Console::puti(i); 
    frame_no += i;   
    Console::puts("\n"); 
    nFreeFrames -= _n_frames;
    return (frame_no);
}

void ContFramePool::mark_inaccessible(unsigned long _base_frame_no,
                                      unsigned long _n_frames)
{
    // TODO: IMPLEMENTATION NEEEDED!
    unsigned long i = 0;
    for(i = _base_frame_no; i < _base_frame_no + _n_frames; i++){
        mark_inaccessible(i);
    }
    nFreeFrames -= _n_frames;
}
void ContFramePool::mark_inaccessible(unsigned long _frame_no)
{
    // Let's first do a range check.
    assert ((_frame_no >= base_frame_no) && (_frame_no < base_frame_no + nframes));
    
    unsigned int bitmap_index = _frame_no - base_frame_no;
    
    // Is the frame being used already?
    assert(bitmap[bitmap_index] != 'A'|| bitmap[bitmap_index]!='H');
    
    // Update bitmap
    bitmap[bitmap_index] = 'X';
    nFreeFrames--;
}
void ContFramePool::release_frames(unsigned long _first_frame_no)
{
 ContFramePool* curr=ContFramePool::pool_list;
 
       //determine if frame is in curr
        if (curr->base_frame_no+ curr->nframes <= _first_frame_no)
        {
            if(curr->next!=NULL)
                curr=curr->next;
            else{
                Console::puts("Error releasing frame, was not contained in any frame pools\n");
                assert(false);
            }
        }
       
        unsigned char* frame_byte = curr->bitmap;//gets byte containing frame
        unsigned char* ava_byte = curr->bitmap;
        if(frame_byte[_first_frame_no/8]==){
            frame_byte[_first_frame_no++] = 'F';
            while(frame_byte[_first_frame_no]!='F'&&frame_byte[_first_frame_no]!='H'){
                frame_byte[_first_frame_no++] = 'F';
            }
        }
}

unsigned long ContFramePool::needed_info_frames(unsigned long _n_frames)
{
    // TODO: IMPLEMENTATION NEEEDED!
    // one char each
    return  _n_frames/8 +(_n_frames % 8 > 0 ? 1 : 0);
}
