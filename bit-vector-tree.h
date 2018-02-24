#ifndef _MEMORY_POOL_BVT_
#define _MEMORY_POOL_BVT_

#include "allocator.h"

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long uint64;

//造了个bit array容器的轮子
//这玩意是定长的
class BitArray{
	public:
		BitArray(uint64 count):m_count(count),m_size((count>>3)+1){
			m_bytes = Allocator::alloc_array<byte>(m_size);
			for(int i=0;i<m_size;++i)m_bytes[i]=0;
		}
		~BitArray(){
			Allocator::free_array(m_bytes);
		}
		
		void set(uint64 index,bool value){
			if(index > m_count)return;
			if(value){
				m_bytes[index>>3] |= 1<<(index%8);
			}else{
				m_bytes[index>>3] &= ~(1<<(index%8));
			}
		}
		bool get(uint64 index){
			if(index>m_count)return true;
			return (m_bytes[index>>3]&(1<<(index%8)))>>(index%8);
		}
	private:
		uint64 m_size,m_count;
		byte *m_bytes;
};

class BitVectorTree{
	public:
		BitVectorTree(uint count);
		~BitVectorTree();
		
		int allocate();
		void free(uint);
		bool isAllocated(uint);
		bool isFull();
	protected:
	private:
		BitArray *m_bit_array;
		uint64 m_bound,m_bits;
};

#endif
