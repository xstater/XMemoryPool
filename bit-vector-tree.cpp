#include "bit-vector-tree.h"

BitVectorTree::BitVectorTree(uint count){
	uint k = 0;//二叉树层数-1
	for(;((1<<k)<count);++k){}
	m_bound = 1<<k;
	m_bits = m_bound + count - 1;
	m_bit_array = Allocator::alloc<BitArray>(m_bits);
	//更新一下不存在的节点的父节点的状态
	for(uint pos = m_bits + 1;pos < (1<<(k+1));++pos){
		for(uint i = pos>>1;i!=0;i>>=1){
			m_bit_array->set(i,m_bit_array->get(i<<1)&&m_bit_array->get((i<<1)|1));
		}
	}
}

BitVectorTree::~BitVectorTree(){
	Allocator::free(m_bit_array);
}

int BitVectorTree::allocate(){
	if(isFull())return -1;
	uint64 pos = 1;
	for(;pos<m_bound;pos = m_bit_array->get(pos<<1)?((pos<<1)|1):(pos<<1)){}
	m_bit_array->set(pos,true);
	uint id = pos-m_bound;
	pos>>=1;
	for(;pos!=0;pos>>=1)
		m_bit_array->set(pos,m_bit_array->get(pos<<1)&&m_bit_array->get((pos<<1)|1));
	return id;
}
void BitVectorTree::free(uint id){
	id += m_bound;
	if(id>m_bits)return;
	m_bit_array->set(id,false);
	for(id>>=1;id!=0;id>>=1){
		m_bit_array->set(id,m_bit_array->get(id<<1)&&m_bit_array->get((id<<1)|1));
	}
}
bool BitVectorTree::isAllocated(uint id){
	return m_bit_array->get(id - m_bound);
}
bool BitVectorTree::isFull(){
	return m_bit_array->get(1);
}
