#ifndef _MEMORY_POOL_ALLOCATOR_
#define _MEMORY_POOL_ALLOCATOR_

//overwriting this class to use your own allocator

#include <stdlib.h>
#include <utility>

class Allocator{
	public:
		//new-delete
		template<class Type,class... Args>
		static Type *alloc(Args&&...args){
			return new Type(std::forward<Args>(args)...);
		}
		template<class Type>
		static void free(Type *&p){
			delete p;
			p = nullptr;
		}
		template<class Type>
		static Type *alloc_array(int count){
			return new Type[count];
		}
		template<class Type>
		static void free_array(Type *&p){
			delete [] p;
			p = nullptr;
		}
		//malloc-free
		/*
		template<class Type,class... Args>
		static Type *alloc(Args&&...args){
			Type *temp = (Type*)malloc(sizeof(Type));
			temp->Type(std::forward<Args>(args)...);
			return temp;
		}
		template<class Type>
		static void free(Type *&p){
			p->~Type();
			free(p);
			p = nullptr;
		}
		template<class Type>
		static Type *alloc_array(int count){
			return (Type*)malloc(sizeof(Type)*count);
		}
		template<class Type>
		static void free_array(Type *&p){
			free(p);
			p = nullptr;
		}*/
};

#endif
