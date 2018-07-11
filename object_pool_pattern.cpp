#include <iostream>
#include <vector>

class Resource{
	int m_iVal;

public:
	Resource() : m_iVal(0) {}

	void setVal(int val){
		m_iVal = val;
	}

	int getVal(){
		return m_iVal;
	}

	void resetVal(){
		m_iVal = 0;
	}		
};

class ObjectPool{
private:	
	static ObjectPool* m_pInstance;	
	std::vector<Resource*> m_vResources;
	ObjectPool(){}

public:
	static ObjectPool* getInstance(){
		if(m_pInstance == NULL){
			m_pInstance = new ObjectPool;
		}
		return m_pInstance;
	}

	Resource* getResource(){
		if(m_vResources.size() > 0){
			std::cout << "Give ready source!" << std::endl;
			Resource* pResource = m_vResources.back();
			m_vResources.pop_back();
			return pResource;
		}
		else{
			std::cout << "No ready source, create new one!" << std::endl;
			return new Resource;
		}
	}

	void returnResource(Resource* pResource){
		pResource->resetVal();
		m_vResources.push_back(pResource);
	}

};

ObjectPool* ObjectPool::m_pInstance = NULL;

int main(){

	ObjectPool* pObjectPool = ObjectPool::getInstance();

	Resource* first = pObjectPool->getResource();
	first->setVal(1);
	std::cout << "First object val: " << first->getVal() << std::endl;

	Resource* second = pObjectPool->getResource();
	second->setVal(2);
	std::cout << "Second object val: " << second->getVal() << std::endl;

	pObjectPool->returnResource(first);
	pObjectPool->returnResource(second);

	Resource* third = pObjectPool->getResource();
	third->setVal(3);
	std::cout << "Third object val: " << third->getVal() << std::endl;

	return 0;
}