#ifndef _MEMORY_POOL_POOL_
#define _MEMORY_POOL_POOL_

#include <exception>
#include <memory>
#include <utility>
#include "allocator.h"
#include "bit-vector-tree.h"

typedef unsigned int uint;

template<class Type>
class Pool{
	public:
		Pool(uint count):m_bvt(count){
			m_data_arr = Allocator::alloc_array<Type>(count);
		}
		~Pool(){
			Allocator::free_array(m_data_arr);
		}
		
		Type *alloc(){
			int i = m_bvt.allocate();
			if(i==-1){
				return nullptr;
			}
			/return m_data_arr + i;
			//return m_data_arr + m_bvt.allocate();
		}

		void free(Type *&p){
			m_bvt.free((int)(p - m_data_arr));
			p = nullptr;
		}
	protected:
	private:
		BitVectorTree m_bvt;
		Type *m_data_arr;
};

#endif
