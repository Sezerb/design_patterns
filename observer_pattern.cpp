#include <iostream>
#include <vector>

using namespace std;

class Observer{
public:
	virtual bool update(int key) = 0;
};

class KeyNotifier{
	int m_iKey;
	vector<Observer*> m_vMenus;
public:
	void attach(Observer* pObj){
		m_vMenus.push_back(pObj);
	}

	int setKey(int key){
		m_iKey = key;
		//Notify all observers!
		notify();
	}

	int notify(){
		for(vector<Observer*>::iterator it = m_vMenus.begin(); it!=m_vMenus.end(); it++){
			(*it)->update(m_iKey);
		}
	}
};

class MainMenu : public Observer{
	int m_iCurrMenu;

public:
	MainMenu(KeyNotifier* pKeyNotifier, int iCurrMenu) : m_iCurrMenu(iCurrMenu){
		//Attach main menu to key notifier.
		pKeyNotifier->attach(this);
	}

	virtual bool update(int key){
		if(m_iCurrMenu == 0 && key == 1){
			cout << "menu key: " << "Main Menu is opened" << endl;
			return true;
		}
		else{
			cout << "Main menu, do nothing!" << endl;
			return false;
		}
	}
};

class IdleMenu: public Observer{
	int m_iCurrMenu;

public:
	IdleMenu(KeyNotifier* pKeyNotifier, int iCurrMenu) : m_iCurrMenu(iCurrMenu){
		//Attach idle menu to key notifier.
		pKeyNotifier->attach(this);
	}

	virtual bool update(int key){
		if(m_iCurrMenu == 1 && key == 0){
			cout << "exit key: " << "Main Menu is closed" << endl;
			return true;
		}
		else{
			cout << "Idle menu, do nothing!" << endl;
			return false;
		}
	}	
	
};



int main(){
	KeyNotifier kn;
	MainMenu mm(&kn, 0);
	IdleMenu im(&kn, 0);
	kn.setKey(1);
}